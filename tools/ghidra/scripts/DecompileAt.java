// SPDX-License-Identifier: GPL-3.0-or-later

import java.io.File;
import java.io.FileOutputStream;
import java.io.OutputStreamWriter;
import java.nio.charset.StandardCharsets;

import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;

public class DecompileAt extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length < 2 || args[0].isEmpty() || args[1].isEmpty()) {
            throw new IllegalArgumentException("usage: DecompileAt <address> <output>");
        }
        String addrText = args[0];
        if (addrText.startsWith("0x") || addrText.startsWith("0X")) {
            addrText = addrText.substring(2);
        }
        Address addr = currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(addrText);
        Function func = getFunctionAt(addr);
        if (func == null) {
            func = getFunctionContaining(addr);
        }
        if (func == null) {
            throw new IllegalStateException("no function at " + args[0]);
        }
        File outFile = new File(args[1]);
        File parent = outFile.getParentFile();
        if (parent != null) {
            parent.mkdirs();
        }
        DecompInterface decomp = new DecompInterface();
        try {
            if (!decomp.openProgram(currentProgram)) {
                throw new IllegalStateException("could not open program for decompile");
            }
            DecompileResults result = decomp.decompileFunction(func, 60, monitor);
            if (!result.decompileCompleted() || result.getDecompiledFunction() == null) {
                String message = result.getErrorMessage();
                throw new IllegalStateException(message == null ? "decompile failed" : message);
            }
            OutputStreamWriter writer = new OutputStreamWriter(
                    new FileOutputStream(outFile), StandardCharsets.UTF_8);
            try {
                writer.write(result.getDecompiledFunction().getC());
            } finally {
                writer.close();
            }
        } finally {
            decomp.dispose();
        }
    }
}
