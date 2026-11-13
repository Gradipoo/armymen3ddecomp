// SPDX-License-Identifier: GPL-3.0-or-later

import java.io.BufferedWriter;
import java.nio.charset.StandardCharsets;
import java.nio.file.AtomicMoveNotSupportedException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardCopyOption;

import ghidra.app.script.GhidraScript;
import ghidra.framework.Application;
import ghidra.program.model.address.AddressRange;
import ghidra.program.model.address.AddressRangeIterator;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;

/** Export address-set metadata only. Run from the repo root with -noanalysis -readOnly. */
public class ExportFunctionRanges extends GhidraScript {
    private static String quote(String value) {
        if (value == null) {
            return "null";
        }
        StringBuilder out = new StringBuilder("\"");
        for (int i = 0; i < value.length(); i++) {
            char c = value.charAt(i);
            if (c == '"' || c == '\\') {
                out.append('\\').append(c);
            } else if (c < 0x20) {
                out.append(String.format("\\u%04x", (int) c));
            } else {
                out.append(c);
            }
        }
        return out.append('"').toString();
    }

    private static String address(long value) {
        return quote(String.format("0x%08x", value));
    }

    @Override
    public void run() throws Exception {
        Path root = Paths.get(".").toRealPath();
        Path build = root.resolve("build");
        String[] args = getScriptArgs();
        if (args.length > 1) {
            throw new IllegalArgumentException("usage: ExportFunctionRanges.java [build/output.json]");
        }
        Path out = Paths.get(args.length == 0 ? "build/analysis/function-ranges.json" : args[0])
                .toFile().getCanonicalFile().toPath();
        if (!out.startsWith(build) || out.equals(build)) {
            throw new IllegalArgumentException("export must stay inside the repository build directory");
        }
        if (!out.getFileName().toString().endsWith(".json")) {
            throw new IllegalArgumentException("export must use a .json filename");
        }
        String sourceName = currentProgram.getExecutablePath();
        if (sourceName != null && !sourceName.isEmpty()) {
            Path source = Paths.get(sourceName).toFile().getCanonicalFile().toPath();
            if (source.equals(out) || (Files.exists(source) && Files.exists(out)
                    && Files.isSameFile(source, out))) {
                throw new IllegalArgumentException("export must not overwrite the imported image");
            }
        }
        Files.deleteIfExists(out);
        Files.createDirectories(out.getParent());
        Path temporary = Files.createTempFile(out.getParent(), ".function-ranges-", ".json");
        try {
            try (BufferedWriter writer = Files.newBufferedWriter(temporary, StandardCharsets.UTF_8)) {
                writer.write("{\n  \"schema_version\": 1,\n  \"exporter\": \"ExportFunctionRanges.java\",\n");
                writer.write("  \"ghidra_version\": " + quote(Application.getApplicationVersion()) + ",\n");
                writer.write("  \"program_name\": " + quote(currentProgram.getName()) + ",\n");
                writer.write("  \"language_id\": " + quote(currentProgram.getLanguage().getLanguageID().toString()) + ",\n");
                writer.write("  \"default_address_space\": " + quote(currentProgram.getAddressFactory()
                        .getDefaultAddressSpace().getName()) + ",\n");
                writer.write("  \"source_image_sha256\": " + quote(currentProgram.getExecutableSHA256()) + ",\n");
                writer.write("  \"functions\": [\n");
                FunctionIterator functions = currentProgram.getFunctionManager().getFunctions(true);
                boolean firstFunction = true;
                while (functions.hasNext()) {
                    monitor.checkCancelled();
                    Function function = functions.next();
                    if (function.isExternal()) {
                        continue;
                    }
                    if (!firstFunction) {
                        writer.write(",\n");
                    }
                    firstFunction = false;
                    writer.write("    {\"address\": " + address(function.getEntryPoint().getOffset())
                            + ", \"size\": " + function.getBody().getNumAddresses()
                            + ", \"name\": " + quote(function.getName()) + ", \"ranges\": [");
                    AddressRangeIterator ranges = function.getBody().getAddressRanges();
                    boolean firstRange = true;
                    while (ranges.hasNext()) {
                        AddressRange range = ranges.next();
                        if (!firstRange) {
                            writer.write(", ");
                        }
                        firstRange = false;
                        writer.write("{\"space\": " + quote(range.getAddressSpace().getName())
                                + ", \"start\": " + address(range.getMinAddress().getOffset())
                                + ", \"end\": " + address(range.getMaxAddress().getOffset()) + "}");
                    }
                    writer.write("]}");
                }
                writer.write("\n  ]\n}\n");
            }
            try {
                Files.move(temporary, out, StandardCopyOption.ATOMIC_MOVE,
                        StandardCopyOption.REPLACE_EXISTING);
            } catch (AtomicMoveNotSupportedException exception) {
                Files.move(temporary, out, StandardCopyOption.REPLACE_EXISTING);
            }
        } finally {
            Files.deleteIfExists(temporary);
        }
        println("Local function-range metadata: " + out);
    }
}
