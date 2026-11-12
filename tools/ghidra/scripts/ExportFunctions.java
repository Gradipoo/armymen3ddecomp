// SPDX-License-Identifier: GPL-3.0-or-later

import java.io.File;
import java.io.FileOutputStream;
import java.io.OutputStreamWriter;
import java.nio.charset.StandardCharsets;

import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;

public class ExportFunctions extends GhidraScript {
    @Override
    public void run() throws Exception {
        String outPath = "docs/research/re/game-functions.tsv";
        String[] args = getScriptArgs();
        if (args.length > 0 && args[0].length() > 0) {
            outPath = args[0];
        }
        File outFile = new File(outPath);
        File parent = outFile.getParentFile();
        if (parent != null) {
            parent.mkdirs();
        }
        OutputStreamWriter writer = new OutputStreamWriter(
                new FileOutputStream(outFile), StandardCharsets.UTF_8);
        try {
            writer.write("address\tsize\tname\n");
            FunctionIterator functions = currentProgram.getFunctionManager().getFunctions(true);
            while (functions.hasNext() && !monitor.isCancelled()) {
                Function func = functions.next();
                // External symbols are not functions in this image.
                if (func.isExternal()) {
                    continue;
                }
                long addr = func.getEntryPoint().getOffset() & 0xffffffffL;
                long size = func.getBody().getNumAddresses();
                String name = func.getName().replace('\t', ' ').replace('\n', ' ').replace('\r', ' ');
                writer.write(String.format("%08x\t%d\t%s\n", addr, size, name));
            }
        } finally {
            writer.close();
        }
    }
}
