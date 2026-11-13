// SPDX-License-Identifier: GPL-3.0-or-later

import java.io.Reader;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardCopyOption;
import java.util.ArrayList;
import java.util.HexFormat;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;

import ghidra.app.script.GhidraScript;
import ghidra.framework.Application;
import ghidra.pcode.emu.PcodeEmulationCallbacks;
import ghidra.pcode.emu.PcodeEmulator;
import ghidra.pcode.emu.PcodeThread;
import ghidra.pcode.exec.PcodeExecutorStatePiece.Reason;
import ghidra.pcode.utils.Utils;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressSpace;
import ghidra.program.model.lang.Language;
import ghidra.program.model.lang.LanguageID;
import ghidra.program.model.lang.Register;
import ghidra.program.model.lang.RegisterValue;
import ghidra.program.model.pcode.PcodeOp;

/**
 * Fixed synthetic MIPS trial. Uses a blank PcodeEmulator, never program memory.
 * API references: Ghidra 12.2 StandAloneEmuExampleScript and PcodeThread.
 * Those upstream API examples are Apache-2.0. No upstream implementation is copied.
 */
public class ResearchMipsEmulation extends GhidraScript {
    private static final String LANGUAGE = "MIPS:LE:32:default";
    private static final long STATE = 0x3000;
    private static final long STACK = 0x3fc0;
    private static final long FINISH = 0x5000;
    private static final long ALPHA = 0x2000;
    private static final long BETA = 0x2100;
    private Language language;
    private AddressSpace ram;

    private static Map<String, Object> row(Object... pairs) {
        Map<String, Object> result = new LinkedHashMap<>();
        for (int i = 0; i < pairs.length; i += 2) {
            result.put((String) pairs[i], pairs[i + 1]);
        }
        return result;
    }

    private static byte[] bytes(long value) {
        return new byte[] {(byte) value, (byte) (value >>> 8),
                (byte) (value >>> 16), (byte) (value >>> 24)};
    }

    private static long unsigned(byte[] value) {
        return Utils.bytesToLong(value, value.length, false) & 0xffffffffL;
    }

    private Register register(String name) {
        Register register = language.getRegister(name);
        if (register == null || register.getMinimumByteSize() != 4) {
            throw new IllegalArgumentException("not a 32-bit register: " + name);
        }
        return register;
    }

    private long read(PcodeThread<byte[]> thread, String name) {
        return unsigned(thread.getState().getVar(register(name), Reason.INSPECT));
    }

    private void write(PcodeThread<byte[]> thread, String name, long value) {
        thread.getState().setVar(register(name), bytes(value));
    }

    private static boolean in(long address, int size, long start, int length) {
        return address >= start && size > 0 && address + size <= start + length;
    }

    private static void dataRange(long address, int size) {
        if (!in(address, size, STATE, 32) && !in(address, size, STACK, 128)) {
            throw new IllegalStateException("data access outside synthetic state/stack: "
                    + String.format("0x%08x", address) + "/" + size);
        }
    }

    private Map<String, Object> execute(JsonObject input) throws Exception {
        long entry = input.get("entry").getAsLong();
        byte[] code = HexFormat.of().parseHex(input.get("code_hex").getAsString());
        byte[] state = HexFormat.of().parseHex(input.get("state_initial_hex").getAsString());
        byte[] stack = HexFormat.of().parseHex(input.get("stack_initial_hex").getAsString());
        int limit = input.get("step_limit").getAsInt();
        if ((entry != 0x1000 && entry != 0x7000) || code.length == 0
                || code.length > 256 || code.length % 4 != 0 || state.length != 32
                || stack.length != 128 || limit < 1 || limit > 128) {
            throw new IllegalArgumentException("invalid fixed synthetic case bounds");
        }
        List<Long> decoded = new ArrayList<>();
        List<Map<String, Object>> stores = new ArrayList<>();
        List<Map<String, Object>> trace = new ArrayList<>();
        List<Map<String, Object>> callbacks = new ArrayList<>();
        PcodeEmulationCallbacks<byte[]> observer = new PcodeEmulationCallbacks<>() {
            @Override
            public void beforeDecodeInstruction(PcodeThread<byte[]> thread, Address pc,
                    RegisterValue context) {
                decoded.add(pc.getOffset());
            }

            @Override
            public void beforeLoad(PcodeThread<byte[]> thread, PcodeOp op, AddressSpace space,
                    byte[] offset, int size) {
                if (!space.equals(ram)) {
                    throw new IllegalStateException("unexpected load address space");
                }
                dataRange(unsigned(offset), size);
            }

            @Override
            public void beforeStore(PcodeThread<byte[]> thread, PcodeOp op, AddressSpace space,
                    byte[] offset, int size, byte[] value) {
                if (!space.equals(ram)) {
                    throw new IllegalStateException("unexpected store address space");
                }
                dataRange(unsigned(offset), size);
            }

            @Override
            public void afterStore(PcodeThread<byte[]> thread, PcodeOp op, AddressSpace space,
                    byte[] offset, int size, byte[] value) {
                stores.add(row("address", unsigned(offset), "size", size,
                        "value_hex", HexFormat.of().formatHex(value),
                        "pc", thread.getCounter().getOffset()));
            }
        };
        // No EmulatorUtilities.loadProgram and no access to currentProgram memory.
        PcodeEmulator emulator = new PcodeEmulator(language, observer);
        emulator.getSharedState().setVar(ram, entry, code.length, true, code);
        emulator.getSharedState().setVar(ram, STATE, state.length, true, state);
        emulator.getSharedState().setVar(ram, STACK, stack.length, true, stack);
        // BREAK guards followed by a synthetic store that must never execute.
        byte[] guard = HexFormat.of().parseHex("0d000000140080ac");
        emulator.getSharedState().setVar(ram, ALPHA, guard.length, true, guard);
        emulator.getSharedState().setVar(ram, BETA, guard.length, true, guard);
        PcodeThread<byte[]> thread = emulator.newThread();
        JsonObject initial = input.getAsJsonObject("initial_registers");
        for (Map.Entry<String, JsonElement> item : initial.entrySet()) {
            write(thread, item.getKey(), item.getValue().getAsLong());
        }
        thread.overrideContextWithDefault();
        thread.overrideCounter(ram.getAddress(entry));
        int steps = 0;
        String exit = "unstarted";
        String diagnostic = "";
        boolean intercept = input.get("intercept_callbacks").getAsBoolean();
        boolean trapControl = input.get("trap_control").getAsBoolean();
        try {
            while (true) {
                monitor.checkCancelled();
                long pc = thread.getCounter().getOffset();
                if (pc == FINISH) {
                    exit = "return";
                    break;
                }
                if (thread.getFrame() != null) {
                    throw new IllegalStateException("instruction group remains in flight");
                }
                if (pc == ALPHA || pc == BETA) {
                    if (!intercept) {
                        if (!trapControl) {
                            exit = "unintercepted_callback";
                            break;
                        }
                        try {
                            thread.stepInstruction();
                            steps++;
                            exit = "trap_did_not_fire";
                        } catch (Exception e) {
                            exit = "callback_trap";
                            diagnostic = e.getClass().getName() + ": " + e.getMessage();
                        }
                        break;
                    }
                    long[] args = {read(thread, "a0"), read(thread, "a1"),
                            read(thread, "a2"), read(thread, "a3")};
                    long ra = read(thread, "ra");
                    if (!in(ra, 4, entry, code.length) || ra % 4 != 0) {
                        throw new IllegalStateException("callback return outside synthetic function");
                    }
                    long result = pc == ALPHA ? (args[1] * 5 + args[2]) & 0xffffffffL
                            : (args[1] ^ args[3]) & 0xffffffffL;
                    callbacks.add(row("name", pc == ALPHA ? "alpha" : "beta", "pc", pc,
                            "a0", args[0], "a1", args[1], "a2", args[2], "a3", args[3],
                            "ra", ra, "return_value", result, "frame_complete", true));
                    write(thread, "v0", result);
                    write(thread, "v1", pc == ALPHA ? 0xaaaaaaaaL : 0xbbbbbbbbL);
                    write(thread, pc == ALPHA ? "t0" : "t1",
                            pc == ALPHA ? 0x11110001L : 0x22220002L);
                    thread.overrideCounter(ram.getAddress(ra));
                    continue;
                }
                if (!in(pc, 4, entry, code.length) || pc % 4 != 0) {
                    exit = "unknown_pc";
                    diagnostic = String.format("PC 0x%08x is outside the synthetic allow-list", pc);
                    break;
                }
                if (steps >= limit) {
                    exit = "step_limit";
                    diagnostic = "instruction-group limit " + limit + " reached";
                    break;
                }
                long beforeA2 = read(thread, "a2");
                long beforeA3 = read(thread, "a3");
                thread.stepInstruction();
                steps++;
                trace.add(row("pc", pc, "next_pc", thread.getCounter().getOffset(),
                        "a2_before", beforeA2, "a2_after", read(thread, "a2"),
                        "a3_before", beforeA3, "a3_after", read(thread, "a3"),
                        "ra_after", read(thread, "ra"), "frame_complete", thread.getFrame() == null));
            }
        } catch (Exception e) {
            exit = "engine_error";
            diagnostic = e.getClass().getName() + ": " + e.getMessage();
        }
        Map<String, Long> registers = new LinkedHashMap<>();
        for (String name : initial.keySet()) {
            registers.put(name, read(thread, name));
        }
        return row("id", input.get("id").getAsString(), "exit_reason", exit,
                "diagnostic", diagnostic, "steps", steps, "pc", thread.getCounter().getOffset(),
                "initial_registers", initial, "registers", registers,
                "state_hex", HexFormat.of().formatHex(emulator.getSharedState()
                        .getVar(ram, STATE, 32, true, Reason.INSPECT)),
                "stack_hex", HexFormat.of().formatHex(emulator.getSharedState()
                        .getVar(ram, STACK, 128, true, Reason.INSPECT)),
                "callbacks", callbacks, "stores", stores, "decoded_pcs", decoded, "trace", trace,
                "frame_active_at_exit", thread.getFrame() != null);
    }

    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length != 2) {
            throw new IllegalArgumentException("usage: ResearchMipsEmulation.java INPUT_JSON OUTPUT_JSON");
        }
        Path root = Paths.get(".").toRealPath();
        Path build = root.resolve("build");
        Path input = Paths.get(args[0]).toFile().getCanonicalFile().toPath();
        Path out = Paths.get(args[1]).toFile().getCanonicalFile().toPath();
        if (!input.startsWith(build) || !out.startsWith(build) || out.equals(build)
                || !out.getFileName().toString().endsWith(".json") || input.equals(out)
                || (Files.exists(out) && Files.isSameFile(input, out))) {
            throw new IllegalArgumentException("distinct input and JSON output must stay under build/");
        }
        Files.deleteIfExists(out);
        JsonObject request;
        try (Reader reader = Files.newBufferedReader(input, StandardCharsets.UTF_8)) {
            request = new Gson().fromJson(reader, JsonObject.class);
        }
        if (!"am3d-original-synthetic-mips-v1".equals(request.get("fixture").getAsString())
                || request.getAsJsonArray("cases").size() > 32) {
            throw new IllegalArgumentException("not the fixed synthetic trial");
        }
        language = getLanguage(new LanguageID(LANGUAGE));
        ram = language.getDefaultSpace();
        List<Map<String, Object>> results = new ArrayList<>();
        for (JsonElement element : request.getAsJsonArray("cases")) {
            results.add(execute(element.getAsJsonObject()));
        }
        Files.createDirectories(out.getParent());
        Path temporary = Files.createTempFile(out.getParent(), ".emulation-", ".json");
        try {
            Files.writeString(temporary, new GsonBuilder().setPrettyPrinting().create().toJson(
                    row("schema_version", 1, "fixture", request.get("fixture").getAsString(),
                            "ghidra_version", Application.getApplicationVersion(),
                            "language", LANGUAGE, "program_memory_loaded", false, "cases", results))
                    + "\n", StandardCharsets.UTF_8);
            Files.move(temporary, out, StandardCopyOption.REPLACE_EXISTING);
        } finally {
            Files.deleteIfExists(temporary);
        }
        println("Synthetic P-code cases written: " + results.size());
    }
}
