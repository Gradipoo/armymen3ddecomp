-- Preset for the beq at 0x800883c4.
-- Reads the two words the branch compares, then hands off to capture_at_pc.lua.
--
-- The instruction branches to 0x80088394 when v0 equals v1. At this PC, v0 is
-- the low 6 bits of the word at 0x800b76f0 plus 1, and v1 is the word at
-- 0x800b76f4. When both words are 0, v0 is 1 and v1 is 0, so the branch falls
-- through to 0x800883cc. That is the side a DuckStation fast boot recorded.
-- This script does not enter SetIntrMask.

CAPTURE = {
    pc = 0x800883c4,
    hits = 1,
    ram = { 0x800b76f0, 0x800b76f4 },
    out = "build/research/behavior/gpu-beq-800883c4.jsonl",
    note = "Expected fall-through when both words are 0.",
}

-- Run from the repository root so this relative path resolves.
dofile("tools/pcsx/capture_at_pc.lua")
