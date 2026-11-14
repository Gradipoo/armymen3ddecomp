cmake_minimum_required(VERSION 3.16)

project(am3d LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(am3d_exe STATIC components/exe/load.cpp components/exe/display_fill.cpp
    components/exe/display_buffers.cpp components/exe/display_clear.cpp
    components/exe/after_display_clear.cpp components/exe/call_80010c90.cpp
    components/exe/call_80010e00.cpp components/exe/pack_tagged_word.cpp
    components/exe/call_80010ce4.cpp components/exe/call_8001b298.cpp
    components/exe/call_80010cc4.cpp
    components/exe/call_8002fc2c.cpp
    components/exe/call_800302a4.cpp
    components/exe/call_8002fe4c.cpp
    components/exe/call_8002ff4c.cpp
    components/exe/call_8007a384.cpp
    components/exe/call_80010d38.cpp components/exe/call_80076234.cpp
    components/exe/call_80025398.cpp
    components/exe/call_8007c03c.cpp
    components/exe/call_800253a4.cpp
    components/exe/call_800253b0.cpp
    components/exe/call_8007e130.cpp
    components/exe/call_800253f4.cpp
    components/exe/call_8007e150.cpp
    components/exe/call_800253fc.cpp
    components/exe/call_8007e17c.cpp
    components/exe/call_80025408.cpp
    components/exe/call_8007e1c8.cpp
    components/exe/call_8007fbbc.cpp
    components/exe/call_8007e1f8.cpp
    components/exe/call_80025410.cpp
    components/exe/call_8007e118.cpp
    components/exe/call_8002541c.cpp
    components/exe/call_80025470.cpp
    components/exe/call_80060aac.cpp
    components/exe/call_80060b58.cpp
    components/exe/call_80060b10.cpp
    components/exe/call_8007abf8.cpp
    components/exe/call_80060b2c.cpp
    components/exe/call_80060b4c.cpp
    components/exe/call_80060b3c.cpp
    components/exe/call_80025478.cpp
    components/exe/call_8007d3f8.cpp
    components/exe/call_80025488.cpp
    components/exe/call_80064588.cpp
    components/exe/call_80094f54.cpp
    components/exe/call_80095744.cpp
    components/exe/call_800957c8.cpp
    components/exe/call_800957e4.cpp
    components/exe/call_80094f64.cpp
    components/exe/call_80064598.cpp
    components/exe/call_80025490.cpp
    components/exe/call_800621dc.cpp
    components/exe/call_80075198.cpp
    components/exe/call_80062238.cpp
    components/exe/call_800254f0.cpp
    components/exe/call_800636b8.cpp
    components/exe/call_800254fc.cpp
    components/exe/call_800621dc_2.cpp
    components/exe/call_8005b3d4.cpp
    components/exe/call_80062238_2.cpp
    components/exe/call_80025514.cpp
    components/exe/call_80077fdc.cpp
    components/exe/call_8002552c.cpp
    components/exe/call_8007d12c.cpp
    components/exe/call_80025534.cpp
    components/exe/call_8007d12c_2.cpp
    components/exe/call_8002553c.cpp
    components/exe/call_80063668.cpp
    components/exe/call_80062434.cpp
    components/exe/call_80061f80.cpp
    components/exe/call_80061ff0.cpp
    components/exe/call_800620a4.cpp
    components/exe/call_80062474.cpp
    components/exe/call_80075198_2.cpp
    components/exe/call_800624cc.cpp
    components/exe/call_8003852c.cpp
    components/exe/call_8007a250.cpp
    components/exe/call_8007a3b0.cpp
    components/exe/call_800381b0.cpp
    components/exe/call_8007a2b0.cpp
    components/exe/pack_stack_tagged_word.cpp
    components/exe/call_8007a3bc.cpp
    components/exe/call_8001d434.cpp
    components/exe/call_80010f5c.cpp
    components/exe/call_80010fbc.cpp
    components/exe/call_80010f00.cpp
    components/exe/call_8002fb9c.cpp)
target_include_directories(am3d_exe PUBLIC components/exe)

add_library(am3d_platform_core STATIC components/platform/fill_vram.cpp)
target_include_directories(am3d_platform_core PUBLIC components/platform)
target_link_libraries(am3d_platform_core PUBLIC am3d_exe)

option(AM3D_WITH_SDL2 "Build the optional SDL2 platform test" OFF)
if(AM3D_WITH_SDL2)
    find_package(SDL2 2.0.14 CONFIG REQUIRED)
    add_library(am3d_platform_sdl2 STATIC components/platform/sdl_platform.cpp)
    target_compile_definitions(am3d_platform_sdl2 PUBLIC SDL_MAIN_HANDLED)
    target_link_libraries(am3d_platform_sdl2 PUBLIC am3d_platform_core SDL2::SDL2)
    add_executable(am3d_platform_smoke src/platform_smoke.cpp)
    target_link_libraries(am3d_platform_smoke PRIVATE am3d_platform_sdl2)
endif()

add_library(am3d_input STATIC components/input/keyboard.cpp)
target_include_directories(am3d_input PUBLIC components/input)

add_library(am3d_net STATIC components/net/browser.cpp)
target_include_directories(am3d_net PUBLIC components/net)

add_library(am3d_mods STATIC components/mods/overlay.cpp)
target_include_directories(am3d_mods PUBLIC components/mods)

add_executable(am3d src/main.cpp)
target_link_libraries(am3d PRIVATE am3d_exe am3d_input am3d_net am3d_mods)

include(CTest)
if(BUILD_TESTING)
    add_executable(test_display_fill tests/test_display_fill.cpp)
    target_link_libraries(test_display_fill PRIVATE am3d_exe)
    add_test(NAME display_fill COMMAND test_display_fill)
    add_executable(test_display_buffers tests/test_display_buffers.cpp)
    target_link_libraries(test_display_buffers PRIVATE am3d_exe)
    add_test(NAME display_buffers COMMAND test_display_buffers)
    add_executable(test_display_clear tests/test_display_clear.cpp)
    target_link_libraries(test_display_clear PRIVATE am3d_exe)
    add_test(NAME display_clear COMMAND test_display_clear)
    add_executable(test_after_display_clear tests/test_after_display_clear.cpp)
    target_link_libraries(test_after_display_clear PRIVATE am3d_exe)
    add_test(NAME after_display_clear COMMAND test_after_display_clear)
    add_executable(test_call_80010e00 tests/test_call_80010e00.cpp)
    target_link_libraries(test_call_80010e00 PRIVATE am3d_exe)
    add_test(NAME call_80010e00 COMMAND test_call_80010e00)
    add_executable(test_call_80010c90 tests/test_call_80010c90.cpp)
    target_link_libraries(test_call_80010c90 PRIVATE am3d_exe)
    add_test(NAME call_80010c90 COMMAND test_call_80010c90)
    add_executable(test_call_8001b298 tests/test_call_8001b298.cpp)
    target_link_libraries(test_call_8001b298 PRIVATE am3d_exe)
    add_test(NAME call_8001b298 COMMAND test_call_8001b298)
    add_executable(test_call_80010cc4 tests/test_call_80010cc4.cpp)
    target_link_libraries(test_call_80010cc4 PRIVATE am3d_exe)
    add_test(NAME call_80010cc4 COMMAND test_call_80010cc4)
    add_executable(test_call_8002fc2c tests/test_call_8002fc2c.cpp)
    target_link_libraries(test_call_8002fc2c PRIVATE am3d_exe)
    add_test(NAME call_8002fc2c COMMAND test_call_8002fc2c)
    add_executable(test_call_800302a4 tests/test_call_800302a4.cpp)
    target_link_libraries(test_call_800302a4 PRIVATE am3d_exe)
    add_test(NAME call_800302a4 COMMAND test_call_800302a4)
    add_executable(test_call_8002fe4c tests/test_call_8002fe4c.cpp)
    target_link_libraries(test_call_8002fe4c PRIVATE am3d_exe)
    add_test(NAME call_8002fe4c COMMAND test_call_8002fe4c)
    add_executable(test_call_8002ff4c tests/test_call_8002ff4c.cpp)
    target_link_libraries(test_call_8002ff4c PRIVATE am3d_exe)
    add_test(NAME call_8002ff4c COMMAND test_call_8002ff4c)
    add_executable(test_pack_tagged_word tests/test_pack_tagged_word.cpp)
    target_link_libraries(test_pack_tagged_word PRIVATE am3d_exe)
    add_test(NAME pack_tagged_word COMMAND test_pack_tagged_word)
    add_executable(test_call_80010ce4 tests/test_call_80010ce4.cpp)
    target_link_libraries(test_call_80010ce4 PRIVATE am3d_exe)
    add_test(NAME call_80010ce4 COMMAND test_call_80010ce4)
    add_executable(test_call_8007a384 tests/test_call_8007a384.cpp)
    target_link_libraries(test_call_8007a384 PRIVATE am3d_exe)
    add_test(NAME call_8007a384 COMMAND test_call_8007a384)
    add_executable(test_call_80010d38 tests/test_call_80010d38.cpp)
    target_link_libraries(test_call_80010d38 PRIVATE am3d_exe)
    add_test(NAME call_80010d38 COMMAND test_call_80010d38)
    add_executable(test_call_80076234 tests/test_call_80076234.cpp)
    target_link_libraries(test_call_80076234 PRIVATE am3d_exe)
    add_test(NAME call_80076234 COMMAND test_call_80076234)
    add_executable(test_call_80025398 tests/test_call_80025398.cpp)
    target_link_libraries(test_call_80025398 PRIVATE am3d_exe)
    add_test(NAME call_80025398 COMMAND test_call_80025398)
    add_executable(test_call_8007c03c tests/test_call_8007c03c.cpp)
    target_link_libraries(test_call_8007c03c PRIVATE am3d_exe)
    add_test(NAME call_8007c03c COMMAND test_call_8007c03c)
    add_executable(test_call_800253a4 tests/test_call_800253a4.cpp)
    target_link_libraries(test_call_800253a4 PRIVATE am3d_exe)
    add_test(NAME call_800253a4 COMMAND test_call_800253a4)
    add_executable(test_call_800253b0 tests/test_call_800253b0.cpp)
    target_link_libraries(test_call_800253b0 PRIVATE am3d_exe)
    add_test(NAME call_800253b0 COMMAND test_call_800253b0)
    add_executable(test_call_8007e130 tests/test_call_8007e130.cpp)
    target_link_libraries(test_call_8007e130 PRIVATE am3d_exe)
    add_test(NAME call_8007e130 COMMAND test_call_8007e130)
    add_executable(test_call_800253f4 tests/test_call_800253f4.cpp)
    target_link_libraries(test_call_800253f4 PRIVATE am3d_exe)
    add_test(NAME call_800253f4 COMMAND test_call_800253f4)
    add_executable(test_call_8007e150 tests/test_call_8007e150.cpp)
    target_link_libraries(test_call_8007e150 PRIVATE am3d_exe)
    add_test(NAME call_8007e150 COMMAND test_call_8007e150)
    add_executable(test_call_800253fc tests/test_call_800253fc.cpp)
    target_link_libraries(test_call_800253fc PRIVATE am3d_exe)
    add_test(NAME call_800253fc COMMAND test_call_800253fc)
    add_executable(test_call_8007e17c tests/test_call_8007e17c.cpp)
    target_link_libraries(test_call_8007e17c PRIVATE am3d_exe)
    add_test(NAME call_8007e17c COMMAND test_call_8007e17c)
    add_executable(test_call_80025408 tests/test_call_80025408.cpp)
    target_link_libraries(test_call_80025408 PRIVATE am3d_exe)
    add_test(NAME call_80025408 COMMAND test_call_80025408)
    add_executable(test_call_8007e1c8 tests/test_call_8007e1c8.cpp)
    target_link_libraries(test_call_8007e1c8 PRIVATE am3d_exe)
    add_test(NAME call_8007e1c8 COMMAND test_call_8007e1c8)
    add_executable(test_call_8007fbbc tests/test_call_8007fbbc.cpp)
    target_link_libraries(test_call_8007fbbc PRIVATE am3d_exe)
    add_test(NAME call_8007fbbc COMMAND test_call_8007fbbc)
    add_executable(test_call_8007e1f8 tests/test_call_8007e1f8.cpp)
    target_link_libraries(test_call_8007e1f8 PRIVATE am3d_exe)
    add_test(NAME call_8007e1f8 COMMAND test_call_8007e1f8)
    add_executable(test_call_80025410 tests/test_call_80025410.cpp)
    target_link_libraries(test_call_80025410 PRIVATE am3d_exe)
    add_test(NAME call_80025410 COMMAND test_call_80025410)
    add_executable(test_call_8007e118 tests/test_call_8007e118.cpp)
    target_link_libraries(test_call_8007e118 PRIVATE am3d_exe)
    add_test(NAME call_8007e118 COMMAND test_call_8007e118)
    add_executable(test_call_8002541c tests/test_call_8002541c.cpp)
    target_link_libraries(test_call_8002541c PRIVATE am3d_exe)
    add_test(NAME call_8002541c COMMAND test_call_8002541c)
    add_executable(test_call_80025470 tests/test_call_80025470.cpp)
    target_link_libraries(test_call_80025470 PRIVATE am3d_exe)
    add_test(NAME call_80025470 COMMAND test_call_80025470)
    add_executable(test_call_80060aac tests/test_call_80060aac.cpp)
    target_link_libraries(test_call_80060aac PRIVATE am3d_exe)
    add_test(NAME call_80060aac COMMAND test_call_80060aac)
    add_executable(test_call_80060b58 tests/test_call_80060b58.cpp)
    target_link_libraries(test_call_80060b58 PRIVATE am3d_exe)
    add_test(NAME call_80060b58 COMMAND test_call_80060b58)
    add_executable(test_call_80060b10 tests/test_call_80060b10.cpp)
    target_link_libraries(test_call_80060b10 PRIVATE am3d_exe)
    add_test(NAME call_80060b10 COMMAND test_call_80060b10)
    add_executable(test_call_8007abf8 tests/test_call_8007abf8.cpp)
    target_link_libraries(test_call_8007abf8 PRIVATE am3d_exe)
    add_test(NAME call_8007abf8 COMMAND test_call_8007abf8)
    add_executable(test_call_80060b2c tests/test_call_80060b2c.cpp)
    target_link_libraries(test_call_80060b2c PRIVATE am3d_exe)
    add_test(NAME call_80060b2c COMMAND test_call_80060b2c)
    add_executable(test_call_80060b4c tests/test_call_80060b4c.cpp)
    target_link_libraries(test_call_80060b4c PRIVATE am3d_exe)
    add_test(NAME call_80060b4c COMMAND test_call_80060b4c)
    add_executable(test_call_80060b3c tests/test_call_80060b3c.cpp)
    target_link_libraries(test_call_80060b3c PRIVATE am3d_exe)
    add_test(NAME call_80060b3c COMMAND test_call_80060b3c)
    add_executable(test_call_80025478 tests/test_call_80025478.cpp)
    target_link_libraries(test_call_80025478 PRIVATE am3d_exe)
    add_test(NAME call_80025478 COMMAND test_call_80025478)
    add_executable(test_call_8007d3f8 tests/test_call_8007d3f8.cpp)
    target_link_libraries(test_call_8007d3f8 PRIVATE am3d_exe)
    add_test(NAME call_8007d3f8 COMMAND test_call_8007d3f8)
    add_executable(test_call_80025488 tests/test_call_80025488.cpp)
    target_link_libraries(test_call_80025488 PRIVATE am3d_exe)
    add_test(NAME call_80025488 COMMAND test_call_80025488)
    add_executable(test_call_80064588 tests/test_call_80064588.cpp)
    target_link_libraries(test_call_80064588 PRIVATE am3d_exe)
    add_test(NAME call_80064588 COMMAND test_call_80064588)
    add_executable(test_call_80094f54 tests/test_call_80094f54.cpp)
    target_link_libraries(test_call_80094f54 PRIVATE am3d_exe)
    add_test(NAME call_80094f54 COMMAND test_call_80094f54)
    add_executable(test_call_80095744 tests/test_call_80095744.cpp)
    target_link_libraries(test_call_80095744 PRIVATE am3d_exe)
    add_test(NAME call_80095744 COMMAND test_call_80095744)
    add_executable(test_call_800957c8 tests/test_call_800957c8.cpp)
    target_link_libraries(test_call_800957c8 PRIVATE am3d_exe)
    add_test(NAME call_800957c8 COMMAND test_call_800957c8)
    add_executable(test_call_800957e4 tests/test_call_800957e4.cpp)
    target_link_libraries(test_call_800957e4 PRIVATE am3d_exe)
    add_test(NAME call_800957e4 COMMAND test_call_800957e4)
    add_executable(test_call_80094f64 tests/test_call_80094f64.cpp)
    target_link_libraries(test_call_80094f64 PRIVATE am3d_exe)
    add_test(NAME call_80094f64 COMMAND test_call_80094f64)
    add_executable(test_call_80064598 tests/test_call_80064598.cpp)
    target_link_libraries(test_call_80064598 PRIVATE am3d_exe)
    add_test(NAME call_80064598 COMMAND test_call_80064598)
    add_executable(test_call_80025490 tests/test_call_80025490.cpp)
    target_link_libraries(test_call_80025490 PRIVATE am3d_exe)
    add_test(NAME call_80025490 COMMAND test_call_80025490)
    add_executable(test_call_800621dc tests/test_call_800621dc.cpp)
    target_link_libraries(test_call_800621dc PRIVATE am3d_exe)
    add_test(NAME call_800621dc COMMAND test_call_800621dc)
    add_executable(test_call_80075198 tests/test_call_80075198.cpp)
    target_link_libraries(test_call_80075198 PRIVATE am3d_exe)
    add_test(NAME call_80075198 COMMAND test_call_80075198)
    add_executable(test_call_80062238 tests/test_call_80062238.cpp)
    target_link_libraries(test_call_80062238 PRIVATE am3d_exe)
    add_test(NAME call_80062238 COMMAND test_call_80062238)
    add_executable(test_call_800254f0 tests/test_call_800254f0.cpp)
    target_link_libraries(test_call_800254f0 PRIVATE am3d_exe)
    add_test(NAME call_800254f0 COMMAND test_call_800254f0)
    add_executable(test_call_800636b8 tests/test_call_800636b8.cpp)
    target_link_libraries(test_call_800636b8 PRIVATE am3d_exe)
    add_test(NAME call_800636b8 COMMAND test_call_800636b8)
    add_executable(test_call_800254fc tests/test_call_800254fc.cpp)
    target_link_libraries(test_call_800254fc PRIVATE am3d_exe)
    add_test(NAME call_800254fc COMMAND test_call_800254fc)
    add_executable(test_call_800621dc_2 tests/test_call_800621dc_2.cpp)
    target_link_libraries(test_call_800621dc_2 PRIVATE am3d_exe)
    add_test(NAME call_800621dc_2 COMMAND test_call_800621dc_2)
    add_executable(test_call_8005b3d4 tests/test_call_8005b3d4.cpp)
    target_link_libraries(test_call_8005b3d4 PRIVATE am3d_exe)
    add_test(NAME call_8005b3d4 COMMAND test_call_8005b3d4)
    add_executable(test_call_80062238_2 tests/test_call_80062238_2.cpp)
    target_link_libraries(test_call_80062238_2 PRIVATE am3d_exe)
    add_test(NAME call_80062238_2 COMMAND test_call_80062238_2)
    add_executable(test_call_80025514 tests/test_call_80025514.cpp)
    target_link_libraries(test_call_80025514 PRIVATE am3d_exe)
    add_test(NAME call_80025514 COMMAND test_call_80025514)
    add_executable(test_call_80077fdc tests/test_call_80077fdc.cpp)
    target_link_libraries(test_call_80077fdc PRIVATE am3d_exe)
    add_test(NAME call_80077fdc COMMAND test_call_80077fdc)
    add_executable(test_call_8002552c tests/test_call_8002552c.cpp)
    target_link_libraries(test_call_8002552c PRIVATE am3d_exe)
    add_test(NAME call_8002552c COMMAND test_call_8002552c)
    add_executable(test_call_8007d12c tests/test_call_8007d12c.cpp)
    target_link_libraries(test_call_8007d12c PRIVATE am3d_exe)
    add_test(NAME call_8007d12c COMMAND test_call_8007d12c)
    add_executable(test_call_80025534 tests/test_call_80025534.cpp)
    target_link_libraries(test_call_80025534 PRIVATE am3d_exe)
    add_test(NAME call_80025534 COMMAND test_call_80025534)
    add_executable(test_call_8007d12c_2 tests/test_call_8007d12c_2.cpp)
    target_link_libraries(test_call_8007d12c_2 PRIVATE am3d_exe)
    add_test(NAME call_8007d12c_2 COMMAND test_call_8007d12c_2)
    add_executable(test_call_8002553c tests/test_call_8002553c.cpp)
    target_link_libraries(test_call_8002553c PRIVATE am3d_exe)
    add_test(NAME call_8002553c COMMAND test_call_8002553c)
    add_executable(test_call_80063668 tests/test_call_80063668.cpp)
    target_link_libraries(test_call_80063668 PRIVATE am3d_exe)
    add_test(NAME call_80063668 COMMAND test_call_80063668)
    add_executable(test_call_80062434 tests/test_call_80062434.cpp)
    target_link_libraries(test_call_80062434 PRIVATE am3d_exe)
    add_test(NAME call_80062434 COMMAND test_call_80062434)

    add_executable(test_call_80061f80 tests/test_call_80061f80.cpp)
    target_link_libraries(test_call_80061f80 PRIVATE am3d_exe)
    add_test(NAME call_80061f80 COMMAND test_call_80061f80)

    add_executable(test_call_80061ff0 tests/test_call_80061ff0.cpp)
    target_link_libraries(test_call_80061ff0 PRIVATE am3d_exe)
    add_test(NAME call_80061ff0 COMMAND test_call_80061ff0)

    add_executable(test_call_800620a4 tests/test_call_800620a4.cpp)
    target_link_libraries(test_call_800620a4 PRIVATE am3d_exe)
    add_test(NAME call_800620a4 COMMAND test_call_800620a4)

    add_executable(test_call_80062474 tests/test_call_80062474.cpp)
    target_link_libraries(test_call_80062474 PRIVATE am3d_exe)
    add_test(NAME call_80062474 COMMAND test_call_80062474)

    add_executable(test_call_80075198_2 tests/test_call_80075198_2.cpp)
    target_link_libraries(test_call_80075198_2 PRIVATE am3d_exe)
    add_test(NAME call_80075198_2 COMMAND test_call_80075198_2)

    add_executable(test_call_800624cc tests/test_call_800624cc.cpp)
    target_link_libraries(test_call_800624cc PRIVATE am3d_exe)
    add_test(NAME call_800624cc COMMAND test_call_800624cc)
    add_executable(test_call_8003852c tests/test_call_8003852c.cpp)
    target_link_libraries(test_call_8003852c PRIVATE am3d_exe)
    add_test(NAME call_8003852c COMMAND test_call_8003852c)
    add_executable(test_call_8007a250 tests/test_call_8007a250.cpp)
    target_link_libraries(test_call_8007a250 PRIVATE am3d_exe)
    add_test(NAME call_8007a250 COMMAND test_call_8007a250)
    add_executable(test_call_8007a3b0 tests/test_call_8007a3b0.cpp)
    target_link_libraries(test_call_8007a3b0 PRIVATE am3d_exe)
    add_test(NAME call_8007a3b0 COMMAND test_call_8007a3b0)
    add_executable(test_call_800381b0 tests/test_call_800381b0.cpp)
    target_link_libraries(test_call_800381b0 PRIVATE am3d_exe)
    add_test(NAME call_800381b0 COMMAND test_call_800381b0)
    add_executable(test_call_8007a2b0 tests/test_call_8007a2b0.cpp)
    target_link_libraries(test_call_8007a2b0 PRIVATE am3d_exe)
    add_test(NAME call_8007a2b0 COMMAND test_call_8007a2b0)
    add_executable(test_pack_stack_tagged_word tests/test_pack_stack_tagged_word.cpp)
    target_link_libraries(test_pack_stack_tagged_word PRIVATE am3d_exe)
    add_test(NAME pack_stack_tagged_word COMMAND test_pack_stack_tagged_word)
    add_executable(test_call_8007a3bc tests/test_call_8007a3bc.cpp)
    target_link_libraries(test_call_8007a3bc PRIVATE am3d_exe)
    add_test(NAME call_8007a3bc COMMAND test_call_8007a3bc)
    add_executable(test_call_8001d434 tests/test_call_8001d434.cpp)
    target_link_libraries(test_call_8001d434 PRIVATE am3d_exe)
    add_test(NAME call_8001d434 COMMAND test_call_8001d434)
    add_executable(test_call_80010f5c tests/test_call_80010f5c.cpp)
    target_link_libraries(test_call_80010f5c PRIVATE am3d_exe)
    add_test(NAME call_80010f5c COMMAND test_call_80010f5c)
    add_executable(test_call_80010fbc tests/test_call_80010fbc.cpp)
    target_link_libraries(test_call_80010fbc PRIVATE am3d_exe)
    add_test(NAME call_80010fbc COMMAND test_call_80010fbc)
    add_executable(test_call_80010f00 tests/test_call_80010f00.cpp)
    target_link_libraries(test_call_80010f00 PRIVATE am3d_exe)
    add_test(NAME call_80010f00 COMMAND test_call_80010f00)
    add_executable(test_call_8002fb9c tests/test_call_8002fb9c.cpp)
    target_link_libraries(test_call_8002fb9c PRIVATE am3d_exe)
    add_test(NAME call_8002fb9c COMMAND test_call_8002fb9c)
    add_executable(test_fill_vram tests/test_fill_vram.cpp)
    target_link_libraries(test_fill_vram PRIVATE am3d_platform_core)
    add_test(NAME fill_vram COMMAND test_fill_vram)
    if(AM3D_WITH_SDL2)
        add_executable(test_sdl_platform tests/test_sdl_platform.cpp)
        target_link_libraries(test_sdl_platform PRIVATE am3d_platform_sdl2)
        add_test(NAME sdl_platform COMMAND test_sdl_platform)
        set_tests_properties(sdl_platform PROPERTIES
            ENVIRONMENT "SDL_VIDEODRIVER=dummy;SDL_AUDIODRIVER=dummy;SDL_RENDER_DRIVER=software")
    endif()
endif()
