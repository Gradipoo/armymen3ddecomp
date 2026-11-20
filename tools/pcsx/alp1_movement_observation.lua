-- Save the display every N guest vsyncs as a binary PPM.
-- PCSX-Redux Lua. Vsync: https://pcsx-redux.consoledev.net/Lua/events/
-- takeScreenShot: https://pcsx-redux.consoledev.net/Lua/redux-basics/
-- 16 bpp layout matches the scripted-session playbook (red in the low bits).
-- This file does not use a proprietary SDK.
--
-- Override the table with environment variables when they are set:
--   PCSX_ALP1_OUT    directory for frame-NNNNNN.ppm
--   PCSX_ALP1_EVERY  save every this many vsyncs (default 60)
-- A caller can also set the global ALP1_CAPTURE table before dofile.
-- PCSX-Redux -exec runs a Lua string, not a file path. -dofile loads a file.
-- Neither flag forwards script arguments, so the output directory is
-- PCSX_ALP1_OUT or the path in the table. The default directory is
-- build/coordination/alp1-movement-observation/frames, relative to cwd.
-- Keep the listener in a global. If it is collected, it stops firing.

local ffi = require("ffi")

ALP1_CAPTURE = ALP1_CAPTURE or {
    out = "build/coordination/alp1-movement-observation/frames",
    every = 60,
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

local function apply_env()
    local out = env_string("PCSX_ALP1_OUT")
    if out then
        ALP1_CAPTURE.out = out
    end
    local every = env_string("PCSX_ALP1_EVERY")
    if every then
        ALP1_CAPTURE.every = tonumber(every)
    end
end

apply_env()

if not ALP1_CAPTURE.every or ALP1_CAPTURE.every < 1 then
    error("PCSX_ALP1_EVERY must be a positive integer")
end

local function ensure_dir(path)
    if os.execute then
        os.execute("mkdir -p " .. string.format("%q", path))
    end
end

local function write_ppm(path, ss)
    local w = ss.width
    local h = ss.height
    local pixels = w * h
    local file = io.open(path, "wb")
    if not file then
        error("cannot open " .. path)
    end
    file:write(string.format("P6\n%d %d\n255\n", w, h))
    if ss.data.size == pixels * 2 then
        local src = ffi.cast("const uint16_t*", ss.data.data)
        local px = {}
        for i = 0, pixels - 1 do
            local c = src[i]
            px[#px + 1] = string.char(
                bit.band(c, 31) * 8,
                bit.band(bit.rshift(c, 5), 31) * 8,
                bit.band(bit.rshift(c, 10), 31) * 8
            )
        end
        file:write(table.concat(px))
    elseif ss.data.size == pixels * 3 then
        local src = ffi.cast("const uint8_t*", ss.data.data)
        local px = {}
        for i = 0, pixels * 3 - 1 do
            px[#px + 1] = string.char(src[i])
        end
        file:write(table.concat(px))
    else
        file:close()
        error("unsupported screenshot size " .. tostring(ss.data.size))
    end
    file:close()
end

local frame = 0

local function on_vsync()
    frame = frame + 1
    if frame % ALP1_CAPTURE.every ~= 0 then
        return
    end
    local ss = PCSX.GPU.takeScreenShot()
    ensure_dir(ALP1_CAPTURE.out)
    local path = string.format("%s/frame-%06d.ppm", ALP1_CAPTURE.out, frame)
    write_ppm(path, ss)
    print(string.format("alp1 frame %d %dx%d -> %s", frame, ss.width, ss.height, path))
end

ensure_dir(ALP1_CAPTURE.out)
am3d_alp1_vsync = PCSX.Events.createEventListener("GPU::Vsync", function()
    local ok, err = pcall(on_vsync)
    if not ok then
        print("alp1 movement capture error: " .. tostring(err))
    end
end)
