-- Stop at one PC and append one JSON line per hit.
-- PCSX-Redux Lua. Docs: https://pcsx-redux.consoledev.net/Lua/breakpoints/
--
-- Override the table with environment variables when they are set:
--   PCSX_PC    execution address, decimal or 0x hex
--   PCSX_HITS  stop after this many hits (omit to keep running)
--   PCSX_RAM   comma-separated RAM addresses to read as words
--   PCSX_OUT   host path for the JSON lines
-- A caller can also set the global CAPTURE table before dofile.
-- PCSX-Redux -exec runs a Lua string, not a file path. -dofile loads a file.
-- Neither flag forwards script arguments, so the output path is PCSX_OUT
-- or the path in the table. The default file is
-- build/research/behavior/pcsx-capture.jsonl, relative to the working directory.

CAPTURE = CAPTURE or {
    pc = 0x80010000,
    hits = nil,
    ram = {},
    out = "build/research/behavior/pcsx-capture.jsonl",
}

local function env_string(name)
    if not os or not os.getenv then
        return nil
    end
    local value = os.getenv(name)
    if value == nil or value == "" then
        return nil
    end
    return value
end

local function parse_number(text)
    return tonumber(text)
end

local function apply_env()
    local pc = env_string("PCSX_PC")
    if pc then
        CAPTURE.pc = parse_number(pc)
    end
    local hits = env_string("PCSX_HITS")
    if hits then
        CAPTURE.hits = parse_number(hits)
    end
    local ram = env_string("PCSX_RAM")
    if ram then
        CAPTURE.ram = {}
        for part in string.gmatch(ram, "[^,]+") do
            local trimmed = string.match(part, "^%s*(.-)%s*$")
            CAPTURE.ram[#CAPTURE.ram + 1] = parse_number(trimmed)
        end
    end
    local out = env_string("PCSX_OUT")
    if out then
        CAPTURE.out = out
    end
end

apply_env()

local function hex32(value)
    return string.format("0x%08x", tonumber(value) % 4294967296)
end

local function json_escape(text)
    text = string.gsub(text, "\\", "\\\\")
    text = string.gsub(text, "\"", "\\\"")
    text = string.gsub(text, "\n", "\\n")
    return text
end

local function ensure_parent(path)
    local parent = string.match(path, "^(.*)/[^/]+$")
    if parent and parent ~= "" and os.execute then
        os.execute("mkdir -p " .. string.format("%q", parent))
    end
end

local function read_word(mem, address)
    return tonumber(mem:readU32At(address))
end

local hit_count = 0

local function on_hit()
    hit_count = hit_count + 1
    local regs = PCSX.getRegisters()
    local gpr = regs.GPR.n
    local mem = PCSX.getMemoryAsFile()
    local words = {}
    for _, address in ipairs(CAPTURE.ram) do
        words[#words + 1] = { address = address, value = read_word(mem, address) }
    end
    local v0 = tonumber(gpr.v0)
    local v1 = tonumber(gpr.v1)
    local side = "fall-through"
    if v0 == v1 then
        side = "taken"
    end
    local parts = {
        '"hit":' .. tostring(hit_count),
        '"pc":"' .. hex32(regs.pc) .. '"',
        '"ra":"' .. hex32(gpr.ra) .. '"',
        '"v0":"' .. hex32(v0) .. '"',
        '"v1":"' .. hex32(v1) .. '"',
        '"a0":"' .. hex32(gpr.a0) .. '"',
        '"side":"' .. side .. '"',
    }
    local word_parts = {}
    for _, word in ipairs(words) do
        word_parts[#word_parts + 1] =
            '"' .. hex32(word.address) .. '":"' .. hex32(word.value) .. '"'
    end
    parts[#parts + 1] = '"words":{' .. table.concat(word_parts, ",") .. "}"
    if CAPTURE.note then
        parts[#parts + 1] = '"note":"' .. json_escape(CAPTURE.note) .. '"'
    end
    local line = "{" .. table.concat(parts, ",") .. "}\n"
    ensure_parent(CAPTURE.out)
    local file = io.open(CAPTURE.out, "a")
    if not file then
        error("cannot open " .. CAPTURE.out)
    end
    file:write(line)
    file:close()
    print(line)
    if CAPTURE.hits and hit_count >= CAPTURE.hits then
        PCSX.quit(0)
        return false
    end
    return true
end

if not CAPTURE.pc then
    error("CAPTURE.pc is missing")
end

am3d_capture_bp = PCSX.addBreakpoint(
    CAPTURE.pc,
    "Exec",
    4,
    "am3d capture",
    function()
        local ok, err = pcall(on_hit)
        if not ok then
            print("am3d capture error: " .. tostring(err))
            return true
        end
        return err
    end
)
