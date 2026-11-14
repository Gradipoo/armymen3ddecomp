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
    components/exe/call_80075198_3.cpp
    components/exe/call_80062514.cpp
    components/exe/call_80075198_4.cpp
    components/exe/call_80062548.cpp
    components/exe/call_80063684.cpp
    components/exe/call_8002554c.cpp
    components/exe/call_8001d590.cpp
    components/exe/call_80025564.cpp
    components/exe/call_80023848_2.cpp
    components/exe/call_80023794_2.cpp
    components/exe/call_80063b34.cpp
    components/exe/call_80062434_2.cpp
    components/exe/call_80061f80_2.cpp
    components/exe/call_80061ff0_2.cpp
    components/exe/call_80062000.cpp
    components/exe/call_80062474_2.cpp
    components/exe/call_80075198_5.cpp
    components/exe/call_800624cc_2.cpp
    components/exe/call_80075198_6.cpp
    components/exe/call_80062514_2.cpp
    components/exe/call_80075198_7.cpp
    components/exe/call_80062548_2.cpp
    components/exe/call_80063b78.cpp
    components/exe/call_800237d0.cpp
    components/exe/call_80063b34_2.cpp
    components/exe/call_80062434_3.cpp
    components/exe/call_80061f80_3.cpp
    components/exe/call_80061ff0_3.cpp
    components/exe/call_80062000_2.cpp
    components/exe/call_80062474_3.cpp
    components/exe/call_80075198_8.cpp
    components/exe/call_800624cc_3.cpp
    components/exe/call_80075198_9.cpp
    components/exe/call_80062514_3.cpp
    components/exe/call_80075198_10.cpp
    components/exe/call_80062548_3.cpp
    components/exe/call_80063b78_2.cpp
    components/exe/call_800237d0_2.cpp
    components/exe/call_80063b34_3.cpp
    components/exe/call_80062434_4.cpp
    components/exe/call_80023828.cpp
    components/exe/call_8002390c.cpp
    components/exe/call_8007f920_2.cpp
    components/exe/call_8007f928_2.cpp
    components/exe/call_8007f930_2.cpp
    components/exe/call_8007f93c_2.cpp
    components/exe/call_8007f95c_2.cpp
    components/exe/call_8007f988_2.cpp
    components/exe/call_8007f9a0_2.cpp
    components/exe/call_80022f60.cpp
    components/exe/call_8007f920_3.cpp
    components/exe/call_8007f928_3.cpp
    components/exe/call_8007f930_3.cpp
    components/exe/call_8007f93c_3.cpp
    components/exe/call_8007f95c_3.cpp
    components/exe/call_8007f988_3.cpp
    components/exe/call_8007f9a0_3.cpp
    components/exe/call_80022f70.cpp
    components/exe/call_8007f920_4.cpp
    components/exe/call_8007f928_4.cpp
    components/exe/call_8007f930_4.cpp
    components/exe/call_8007f93c_4.cpp
    components/exe/call_8007f95c_4.cpp
    components/exe/call_8007f988_4.cpp
    components/exe/call_8007f9a0_4.cpp
    components/exe/call_80022f80.cpp
    components/exe/call_8007f920_5.cpp
    components/exe/call_8007f928_5.cpp
    components/exe/call_8007f930_5.cpp
    components/exe/call_8007f93c_5.cpp
    components/exe/call_8007f95c_5.cpp
    components/exe/call_8007f988_5.cpp
    components/exe/call_8007f9a0_5.cpp
    components/exe/call_80022f90.cpp
    components/exe/call_8007f920_6.cpp
    components/exe/call_8007f928_6.cpp
    components/exe/call_8007f930_6.cpp
    components/exe/call_8007f93c_6.cpp
    components/exe/call_8007f95c_6.cpp
    components/exe/call_8007f988_6.cpp
    components/exe/call_8007f9a0_6.cpp
    components/exe/call_80022fa0.cpp
    components/exe/call_8007f920_7.cpp
    components/exe/call_8007f928_7.cpp
    components/exe/call_8007f930_7.cpp
    components/exe/call_8007f93c_7.cpp
    components/exe/call_8007f95c_7.cpp
    components/exe/call_8007f988_7.cpp
    components/exe/call_8007f9a0_7.cpp
    components/exe/call_80022fb4.cpp
    components/exe/call_8007f920_8.cpp
    components/exe/call_8007f928_8.cpp
    components/exe/call_8007f930_8.cpp
    components/exe/call_8007f93c_8.cpp
    components/exe/call_8007f95c_8.cpp
    components/exe/call_8007f988_8.cpp
    components/exe/call_8007f9a0_8.cpp
    components/exe/call_80022fc4.cpp
    components/exe/call_8007f920_9.cpp
    components/exe/call_8007f928_9.cpp
    components/exe/call_8007f930_9.cpp
    components/exe/call_8007f93c_9.cpp
    components/exe/call_8007f95c_9.cpp
    components/exe/call_8007f988_9.cpp
    components/exe/call_8007f9a0_9.cpp
    components/exe/call_80022fd4.cpp
    components/exe/call_8007f920_10.cpp
    components/exe/call_80022fe4.cpp
    components/exe/call_80023030.cpp
    components/exe/call_80063ed8.cpp
    components/exe/call_80076508.cpp
    components/exe/call_80076548.cpp
    components/exe/call_80076540.cpp
    components/exe/call_80063f18.cpp
    components/exe/call_8002303c.cpp
    components/exe/call_80023054.cpp
    components/exe/call_80063ed8_2.cpp
    components/exe/call_80076508_2.cpp
    components/exe/call_80063f18_2.cpp
    components/exe/call_8002305c.cpp
    components/exe/call_80063ed8_3.cpp
    components/exe/call_80076508_3.cpp
    components/exe/call_80063f18_3.cpp
    components/exe/call_800231e0.cpp
    components/exe/call_80063ed8_4.cpp
    components/exe/call_80076508_4.cpp
    components/exe/call_80063f18_4.cpp
    components/exe/call_800231f0.cpp
    components/exe/call_80063ed8_5.cpp
    components/exe/call_80076508_5.cpp
    components/exe/call_80063f18_5.cpp
    components/exe/call_80023200.cpp
    components/exe/call_80063ed8_6.cpp
    components/exe/call_80076508_6.cpp
    components/exe/call_80063f18_6.cpp
    components/exe/call_80023218.cpp
    components/exe/call_80063ed8_7.cpp
    components/exe/call_80076508_7.cpp
    components/exe/call_80063f18_7.cpp
    components/exe/call_80023234.cpp
    components/exe/call_80063ed8_8.cpp
    components/exe/call_80076508_8.cpp
    components/exe/call_80063f18_8.cpp
    components/exe/call_80023244.cpp
    components/exe/call_80063ed8_9.cpp
    components/exe/call_80076508_9.cpp
    components/exe/call_80063f18_9.cpp
    components/exe/call_80023254.cpp
    components/exe/call_80063ed8_10.cpp
    components/exe/call_80076508_10.cpp
    components/exe/call_80063f18_10.cpp
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

    add_executable(test_call_80075198_3 tests/test_call_80075198_3.cpp)
    target_link_libraries(test_call_80075198_3 PRIVATE am3d_exe)
    add_test(NAME call_80075198_3 COMMAND test_call_80075198_3)

    add_executable(test_call_80062514 tests/test_call_80062514.cpp)
    target_link_libraries(test_call_80062514 PRIVATE am3d_exe)
    add_test(NAME call_80062514 COMMAND test_call_80062514)

    add_executable(test_call_80075198_4 tests/test_call_80075198_4.cpp)
    target_link_libraries(test_call_80075198_4 PRIVATE am3d_exe)
    add_test(NAME call_80075198_4 COMMAND test_call_80075198_4)

    add_executable(test_call_80062548 tests/test_call_80062548.cpp)
    target_link_libraries(test_call_80062548 PRIVATE am3d_exe)
    add_test(NAME call_80062548 COMMAND test_call_80062548)

    add_executable(test_call_80063684 tests/test_call_80063684.cpp)
    target_link_libraries(test_call_80063684 PRIVATE am3d_exe)
    add_test(NAME call_80063684 COMMAND test_call_80063684)

    add_executable(test_call_8002554c tests/test_call_8002554c.cpp)
    target_link_libraries(test_call_8002554c PRIVATE am3d_exe)
    add_test(NAME call_8002554c COMMAND test_call_8002554c)

    add_executable(test_call_8001d590 tests/test_call_8001d590.cpp)
    target_link_libraries(test_call_8001d590 PRIVATE am3d_exe)
    add_test(NAME call_8001d590 COMMAND test_call_8001d590)

    add_executable(test_call_80025564 tests/test_call_80025564.cpp)
    target_link_libraries(test_call_80025564 PRIVATE am3d_exe)
    add_test(NAME call_80025564 COMMAND test_call_80025564)

    add_executable(test_call_80023848_2 tests/test_call_80023848_2.cpp)
    target_link_libraries(test_call_80023848_2 PRIVATE am3d_exe)
    add_test(NAME call_80023848_2 COMMAND test_call_80023848_2)

    add_executable(test_call_80023794_2 tests/test_call_80023794_2.cpp)
    target_link_libraries(test_call_80023794_2 PRIVATE am3d_exe)
    add_test(NAME call_80023794_2 COMMAND test_call_80023794_2)

    add_executable(test_call_80063b34 tests/test_call_80063b34.cpp)
    target_link_libraries(test_call_80063b34 PRIVATE am3d_exe)
    add_test(NAME call_80063b34 COMMAND test_call_80063b34)

    add_executable(test_call_80062434_2 tests/test_call_80062434_2.cpp)
    target_link_libraries(test_call_80062434_2 PRIVATE am3d_exe)
    add_test(NAME call_80062434_2 COMMAND test_call_80062434_2)

    add_executable(test_call_80061f80_2 tests/test_call_80061f80_2.cpp)
    target_link_libraries(test_call_80061f80_2 PRIVATE am3d_exe)
    add_test(NAME call_80061f80_2 COMMAND test_call_80061f80_2)

    add_executable(test_call_80061ff0_2 tests/test_call_80061ff0_2.cpp)
    target_link_libraries(test_call_80061ff0_2 PRIVATE am3d_exe)
    add_test(NAME call_80061ff0_2 COMMAND test_call_80061ff0_2)

    add_executable(test_call_80062000 tests/test_call_80062000.cpp)
    target_link_libraries(test_call_80062000 PRIVATE am3d_exe)
    add_test(NAME call_80062000 COMMAND test_call_80062000)

    add_executable(test_call_80062474_2 tests/test_call_80062474_2.cpp)
    target_link_libraries(test_call_80062474_2 PRIVATE am3d_exe)
    add_test(NAME call_80062474_2 COMMAND test_call_80062474_2)

    add_executable(test_call_80075198_5 tests/test_call_80075198_5.cpp)
    target_link_libraries(test_call_80075198_5 PRIVATE am3d_exe)
    add_test(NAME call_80075198_5 COMMAND test_call_80075198_5)

    add_executable(test_call_800624cc_2 tests/test_call_800624cc_2.cpp)
    target_link_libraries(test_call_800624cc_2 PRIVATE am3d_exe)
    add_test(NAME call_800624cc_2 COMMAND test_call_800624cc_2)

    add_executable(test_call_80075198_6 tests/test_call_80075198_6.cpp)
    target_link_libraries(test_call_80075198_6 PRIVATE am3d_exe)
    add_test(NAME call_80075198_6 COMMAND test_call_80075198_6)

    add_executable(test_call_80062514_2 tests/test_call_80062514_2.cpp)
    target_link_libraries(test_call_80062514_2 PRIVATE am3d_exe)
    add_test(NAME call_80062514_2 COMMAND test_call_80062514_2)

    add_executable(test_call_80075198_7 tests/test_call_80075198_7.cpp)
    target_link_libraries(test_call_80075198_7 PRIVATE am3d_exe)
    add_test(NAME call_80075198_7 COMMAND test_call_80075198_7)

    add_executable(test_call_80062548_2 tests/test_call_80062548_2.cpp)
    target_link_libraries(test_call_80062548_2 PRIVATE am3d_exe)
    add_test(NAME call_80062548_2 COMMAND test_call_80062548_2)

    add_executable(test_call_80063b78 tests/test_call_80063b78.cpp)
    target_link_libraries(test_call_80063b78 PRIVATE am3d_exe)
    add_test(NAME call_80063b78 COMMAND test_call_80063b78)

    add_executable(test_call_800237d0 tests/test_call_800237d0.cpp)
    target_link_libraries(test_call_800237d0 PRIVATE am3d_exe)
    add_test(NAME call_800237d0 COMMAND test_call_800237d0)

    add_executable(test_call_80063b34_2 tests/test_call_80063b34_2.cpp)
    target_link_libraries(test_call_80063b34_2 PRIVATE am3d_exe)
    add_test(NAME call_80063b34_2 COMMAND test_call_80063b34_2)

    add_executable(test_call_80062434_3 tests/test_call_80062434_3.cpp)
    target_link_libraries(test_call_80062434_3 PRIVATE am3d_exe)
    add_test(NAME call_80062434_3 COMMAND test_call_80062434_3)

    add_executable(test_call_80061f80_3 tests/test_call_80061f80_3.cpp)
    target_link_libraries(test_call_80061f80_3 PRIVATE am3d_exe)
    add_test(NAME call_80061f80_3 COMMAND test_call_80061f80_3)

    add_executable(test_call_80061ff0_3 tests/test_call_80061ff0_3.cpp)
    target_link_libraries(test_call_80061ff0_3 PRIVATE am3d_exe)
    add_test(NAME call_80061ff0_3 COMMAND test_call_80061ff0_3)

    add_executable(test_call_80062000_2 tests/test_call_80062000_2.cpp)
    target_link_libraries(test_call_80062000_2 PRIVATE am3d_exe)
    add_test(NAME call_80062000_2 COMMAND test_call_80062000_2)

    add_executable(test_call_80062474_3 tests/test_call_80062474_3.cpp)
    target_link_libraries(test_call_80062474_3 PRIVATE am3d_exe)
    add_test(NAME call_80062474_3 COMMAND test_call_80062474_3)

    add_executable(test_call_80075198_8 tests/test_call_80075198_8.cpp)
    target_link_libraries(test_call_80075198_8 PRIVATE am3d_exe)
    add_test(NAME call_80075198_8 COMMAND test_call_80075198_8)

    add_executable(test_call_800624cc_3 tests/test_call_800624cc_3.cpp)
    target_link_libraries(test_call_800624cc_3 PRIVATE am3d_exe)
    add_test(NAME call_800624cc_3 COMMAND test_call_800624cc_3)

    add_executable(test_call_80075198_9 tests/test_call_80075198_9.cpp)
    target_link_libraries(test_call_80075198_9 PRIVATE am3d_exe)
    add_test(NAME call_80075198_9 COMMAND test_call_80075198_9)

    add_executable(test_call_80062514_3 tests/test_call_80062514_3.cpp)
    target_link_libraries(test_call_80062514_3 PRIVATE am3d_exe)
    add_test(NAME call_80062514_3 COMMAND test_call_80062514_3)

    add_executable(test_call_80075198_10 tests/test_call_80075198_10.cpp)
    target_link_libraries(test_call_80075198_10 PRIVATE am3d_exe)
    add_test(NAME call_80075198_10 COMMAND test_call_80075198_10)

    add_executable(test_call_80062548_3 tests/test_call_80062548_3.cpp)
    target_link_libraries(test_call_80062548_3 PRIVATE am3d_exe)
    add_test(NAME call_80062548_3 COMMAND test_call_80062548_3)

    add_executable(test_call_80063b78_2 tests/test_call_80063b78_2.cpp)
    target_link_libraries(test_call_80063b78_2 PRIVATE am3d_exe)
    add_test(NAME call_80063b78_2 COMMAND test_call_80063b78_2)

    add_executable(test_call_800237d0_2 tests/test_call_800237d0_2.cpp)
    target_link_libraries(test_call_800237d0_2 PRIVATE am3d_exe)
    add_test(NAME call_800237d0_2 COMMAND test_call_800237d0_2)

    add_executable(test_call_80063b34_3 tests/test_call_80063b34_3.cpp)
    target_link_libraries(test_call_80063b34_3 PRIVATE am3d_exe)
    add_test(NAME call_80063b34_3 COMMAND test_call_80063b34_3)

    add_executable(test_call_80062434_4 tests/test_call_80062434_4.cpp)
    target_link_libraries(test_call_80062434_4 PRIVATE am3d_exe)
    add_test(NAME call_80062434_4 COMMAND test_call_80062434_4)

    add_executable(test_call_80023828 tests/test_call_80023828.cpp)
    target_link_libraries(test_call_80023828 PRIVATE am3d_exe)
    add_test(NAME call_80023828 COMMAND test_call_80023828)

    add_executable(test_call_8002390c tests/test_call_8002390c.cpp)
    target_link_libraries(test_call_8002390c PRIVATE am3d_exe)
    add_test(NAME call_8002390c COMMAND test_call_8002390c)

    add_executable(test_call_8007f920_2 tests/test_call_8007f920_2.cpp)
    target_link_libraries(test_call_8007f920_2 PRIVATE am3d_exe)
    add_test(NAME call_8007f920_2 COMMAND test_call_8007f920_2)

    add_executable(test_call_8007f928_2 tests/test_call_8007f928_2.cpp)
    target_link_libraries(test_call_8007f928_2 PRIVATE am3d_exe)
    add_test(NAME call_8007f928_2 COMMAND test_call_8007f928_2)

    add_executable(test_call_8007f930_2 tests/test_call_8007f930_2.cpp)
    target_link_libraries(test_call_8007f930_2 PRIVATE am3d_exe)
    add_test(NAME call_8007f930_2 COMMAND test_call_8007f930_2)

    add_executable(test_call_8007f93c_2 tests/test_call_8007f93c_2.cpp)
    target_link_libraries(test_call_8007f93c_2 PRIVATE am3d_exe)
    add_test(NAME call_8007f93c_2 COMMAND test_call_8007f93c_2)

    add_executable(test_call_8007f95c_2 tests/test_call_8007f95c_2.cpp)
    target_link_libraries(test_call_8007f95c_2 PRIVATE am3d_exe)
    add_test(NAME call_8007f95c_2 COMMAND test_call_8007f95c_2)

    add_executable(test_call_8007f988_2 tests/test_call_8007f988_2.cpp)
    target_link_libraries(test_call_8007f988_2 PRIVATE am3d_exe)
    add_test(NAME call_8007f988_2 COMMAND test_call_8007f988_2)

    add_executable(test_call_8007f9a0_2 tests/test_call_8007f9a0_2.cpp)
    target_link_libraries(test_call_8007f9a0_2 PRIVATE am3d_exe)
    add_test(NAME call_8007f9a0_2 COMMAND test_call_8007f9a0_2)

    add_executable(test_call_80022f60 tests/test_call_80022f60.cpp)
    target_link_libraries(test_call_80022f60 PRIVATE am3d_exe)
    add_test(NAME call_80022f60 COMMAND test_call_80022f60)

    add_executable(test_call_8007f920_3 tests/test_call_8007f920_3.cpp)
    target_link_libraries(test_call_8007f920_3 PRIVATE am3d_exe)
    add_test(NAME call_8007f920_3 COMMAND test_call_8007f920_3)

    add_executable(test_call_8007f928_3 tests/test_call_8007f928_3.cpp)
    target_link_libraries(test_call_8007f928_3 PRIVATE am3d_exe)
    add_test(NAME call_8007f928_3 COMMAND test_call_8007f928_3)

    add_executable(test_call_8007f930_3 tests/test_call_8007f930_3.cpp)
    target_link_libraries(test_call_8007f930_3 PRIVATE am3d_exe)
    add_test(NAME call_8007f930_3 COMMAND test_call_8007f930_3)

    add_executable(test_call_8007f93c_3 tests/test_call_8007f93c_3.cpp)
    target_link_libraries(test_call_8007f93c_3 PRIVATE am3d_exe)
    add_test(NAME call_8007f93c_3 COMMAND test_call_8007f93c_3)

    add_executable(test_call_8007f95c_3 tests/test_call_8007f95c_3.cpp)
    target_link_libraries(test_call_8007f95c_3 PRIVATE am3d_exe)
    add_test(NAME call_8007f95c_3 COMMAND test_call_8007f95c_3)

    add_executable(test_call_8007f988_3 tests/test_call_8007f988_3.cpp)
    target_link_libraries(test_call_8007f988_3 PRIVATE am3d_exe)
    add_test(NAME call_8007f988_3 COMMAND test_call_8007f988_3)

    add_executable(test_call_8007f9a0_3 tests/test_call_8007f9a0_3.cpp)
    target_link_libraries(test_call_8007f9a0_3 PRIVATE am3d_exe)
    add_test(NAME call_8007f9a0_3 COMMAND test_call_8007f9a0_3)

    add_executable(test_call_80022f70 tests/test_call_80022f70.cpp)
    target_link_libraries(test_call_80022f70 PRIVATE am3d_exe)
    add_test(NAME call_80022f70 COMMAND test_call_80022f70)

    add_executable(test_call_8007f920_4 tests/test_call_8007f920_4.cpp)
    target_link_libraries(test_call_8007f920_4 PRIVATE am3d_exe)
    add_test(NAME call_8007f920_4 COMMAND test_call_8007f920_4)

    add_executable(test_call_8007f928_4 tests/test_call_8007f928_4.cpp)
    target_link_libraries(test_call_8007f928_4 PRIVATE am3d_exe)
    add_test(NAME call_8007f928_4 COMMAND test_call_8007f928_4)

    add_executable(test_call_8007f930_4 tests/test_call_8007f930_4.cpp)
    target_link_libraries(test_call_8007f930_4 PRIVATE am3d_exe)
    add_test(NAME call_8007f930_4 COMMAND test_call_8007f930_4)

    add_executable(test_call_8007f93c_4 tests/test_call_8007f93c_4.cpp)
    target_link_libraries(test_call_8007f93c_4 PRIVATE am3d_exe)
    add_test(NAME call_8007f93c_4 COMMAND test_call_8007f93c_4)

    add_executable(test_call_8007f95c_4 tests/test_call_8007f95c_4.cpp)
    target_link_libraries(test_call_8007f95c_4 PRIVATE am3d_exe)
    add_test(NAME call_8007f95c_4 COMMAND test_call_8007f95c_4)

    add_executable(test_call_8007f988_4 tests/test_call_8007f988_4.cpp)
    target_link_libraries(test_call_8007f988_4 PRIVATE am3d_exe)
    add_test(NAME call_8007f988_4 COMMAND test_call_8007f988_4)

    add_executable(test_call_8007f9a0_4 tests/test_call_8007f9a0_4.cpp)
    target_link_libraries(test_call_8007f9a0_4 PRIVATE am3d_exe)
    add_test(NAME call_8007f9a0_4 COMMAND test_call_8007f9a0_4)

    add_executable(test_call_80022f80 tests/test_call_80022f80.cpp)
    target_link_libraries(test_call_80022f80 PRIVATE am3d_exe)
    add_test(NAME call_80022f80 COMMAND test_call_80022f80)

    add_executable(test_call_8007f920_5 tests/test_call_8007f920_5.cpp)
    target_link_libraries(test_call_8007f920_5 PRIVATE am3d_exe)
    add_test(NAME call_8007f920_5 COMMAND test_call_8007f920_5)

    add_executable(test_call_8007f928_5 tests/test_call_8007f928_5.cpp)
    target_link_libraries(test_call_8007f928_5 PRIVATE am3d_exe)
    add_test(NAME call_8007f928_5 COMMAND test_call_8007f928_5)

    add_executable(test_call_8007f930_5 tests/test_call_8007f930_5.cpp)
    target_link_libraries(test_call_8007f930_5 PRIVATE am3d_exe)
    add_test(NAME call_8007f930_5 COMMAND test_call_8007f930_5)

    add_executable(test_call_8007f93c_5 tests/test_call_8007f93c_5.cpp)
    target_link_libraries(test_call_8007f93c_5 PRIVATE am3d_exe)
    add_test(NAME call_8007f93c_5 COMMAND test_call_8007f93c_5)

    add_executable(test_call_8007f95c_5 tests/test_call_8007f95c_5.cpp)
    target_link_libraries(test_call_8007f95c_5 PRIVATE am3d_exe)
    add_test(NAME call_8007f95c_5 COMMAND test_call_8007f95c_5)

    add_executable(test_call_8007f988_5 tests/test_call_8007f988_5.cpp)
    target_link_libraries(test_call_8007f988_5 PRIVATE am3d_exe)
    add_test(NAME call_8007f988_5 COMMAND test_call_8007f988_5)

    add_executable(test_call_8007f9a0_5 tests/test_call_8007f9a0_5.cpp)
    target_link_libraries(test_call_8007f9a0_5 PRIVATE am3d_exe)
    add_test(NAME call_8007f9a0_5 COMMAND test_call_8007f9a0_5)

    add_executable(test_call_80022f90 tests/test_call_80022f90.cpp)
    target_link_libraries(test_call_80022f90 PRIVATE am3d_exe)
    add_test(NAME call_80022f90 COMMAND test_call_80022f90)

    add_executable(test_call_8007f920_6 tests/test_call_8007f920_6.cpp)
    target_link_libraries(test_call_8007f920_6 PRIVATE am3d_exe)
    add_test(NAME call_8007f920_6 COMMAND test_call_8007f920_6)

    add_executable(test_call_8007f928_6 tests/test_call_8007f928_6.cpp)
    target_link_libraries(test_call_8007f928_6 PRIVATE am3d_exe)
    add_test(NAME call_8007f928_6 COMMAND test_call_8007f928_6)

    add_executable(test_call_8007f930_6 tests/test_call_8007f930_6.cpp)
    target_link_libraries(test_call_8007f930_6 PRIVATE am3d_exe)
    add_test(NAME call_8007f930_6 COMMAND test_call_8007f930_6)

    add_executable(test_call_8007f93c_6 tests/test_call_8007f93c_6.cpp)
    target_link_libraries(test_call_8007f93c_6 PRIVATE am3d_exe)
    add_test(NAME call_8007f93c_6 COMMAND test_call_8007f93c_6)

    add_executable(test_call_8007f95c_6 tests/test_call_8007f95c_6.cpp)
    target_link_libraries(test_call_8007f95c_6 PRIVATE am3d_exe)
    add_test(NAME call_8007f95c_6 COMMAND test_call_8007f95c_6)

    add_executable(test_call_8007f988_6 tests/test_call_8007f988_6.cpp)
    target_link_libraries(test_call_8007f988_6 PRIVATE am3d_exe)
    add_test(NAME call_8007f988_6 COMMAND test_call_8007f988_6)

    add_executable(test_call_8007f9a0_6 tests/test_call_8007f9a0_6.cpp)
    target_link_libraries(test_call_8007f9a0_6 PRIVATE am3d_exe)
    add_test(NAME call_8007f9a0_6 COMMAND test_call_8007f9a0_6)

    add_executable(test_call_80022fa0 tests/test_call_80022fa0.cpp)
    target_link_libraries(test_call_80022fa0 PRIVATE am3d_exe)
    add_test(NAME call_80022fa0 COMMAND test_call_80022fa0)

    add_executable(test_call_8007f920_7 tests/test_call_8007f920_7.cpp)
    target_link_libraries(test_call_8007f920_7 PRIVATE am3d_exe)
    add_test(NAME call_8007f920_7 COMMAND test_call_8007f920_7)

    add_executable(test_call_8007f928_7 tests/test_call_8007f928_7.cpp)
    target_link_libraries(test_call_8007f928_7 PRIVATE am3d_exe)
    add_test(NAME call_8007f928_7 COMMAND test_call_8007f928_7)

    add_executable(test_call_8007f930_7 tests/test_call_8007f930_7.cpp)
    target_link_libraries(test_call_8007f930_7 PRIVATE am3d_exe)
    add_test(NAME call_8007f930_7 COMMAND test_call_8007f930_7)

    add_executable(test_call_8007f93c_7 tests/test_call_8007f93c_7.cpp)
    target_link_libraries(test_call_8007f93c_7 PRIVATE am3d_exe)
    add_test(NAME call_8007f93c_7 COMMAND test_call_8007f93c_7)

    add_executable(test_call_8007f95c_7 tests/test_call_8007f95c_7.cpp)
    target_link_libraries(test_call_8007f95c_7 PRIVATE am3d_exe)
    add_test(NAME call_8007f95c_7 COMMAND test_call_8007f95c_7)

    add_executable(test_call_8007f988_7 tests/test_call_8007f988_7.cpp)
    target_link_libraries(test_call_8007f988_7 PRIVATE am3d_exe)
    add_test(NAME call_8007f988_7 COMMAND test_call_8007f988_7)

    add_executable(test_call_8007f9a0_7 tests/test_call_8007f9a0_7.cpp)
    target_link_libraries(test_call_8007f9a0_7 PRIVATE am3d_exe)
    add_test(NAME call_8007f9a0_7 COMMAND test_call_8007f9a0_7)

    add_executable(test_call_80022fb4 tests/test_call_80022fb4.cpp)
    target_link_libraries(test_call_80022fb4 PRIVATE am3d_exe)
    add_test(NAME call_80022fb4 COMMAND test_call_80022fb4)

    add_executable(test_call_8007f920_8 tests/test_call_8007f920_8.cpp)
    target_link_libraries(test_call_8007f920_8 PRIVATE am3d_exe)
    add_test(NAME call_8007f920_8 COMMAND test_call_8007f920_8)

    add_executable(test_call_8007f928_8 tests/test_call_8007f928_8.cpp)
    target_link_libraries(test_call_8007f928_8 PRIVATE am3d_exe)
    add_test(NAME call_8007f928_8 COMMAND test_call_8007f928_8)

    add_executable(test_call_8007f930_8 tests/test_call_8007f930_8.cpp)
    target_link_libraries(test_call_8007f930_8 PRIVATE am3d_exe)
    add_test(NAME call_8007f930_8 COMMAND test_call_8007f930_8)

    add_executable(test_call_8007f93c_8 tests/test_call_8007f93c_8.cpp)
    target_link_libraries(test_call_8007f93c_8 PRIVATE am3d_exe)
    add_test(NAME call_8007f93c_8 COMMAND test_call_8007f93c_8)

    add_executable(test_call_8007f95c_8 tests/test_call_8007f95c_8.cpp)
    target_link_libraries(test_call_8007f95c_8 PRIVATE am3d_exe)
    add_test(NAME call_8007f95c_8 COMMAND test_call_8007f95c_8)

    add_executable(test_call_8007f988_8 tests/test_call_8007f988_8.cpp)
    target_link_libraries(test_call_8007f988_8 PRIVATE am3d_exe)
    add_test(NAME call_8007f988_8 COMMAND test_call_8007f988_8)

    add_executable(test_call_8007f9a0_8 tests/test_call_8007f9a0_8.cpp)
    target_link_libraries(test_call_8007f9a0_8 PRIVATE am3d_exe)
    add_test(NAME call_8007f9a0_8 COMMAND test_call_8007f9a0_8)

    add_executable(test_call_80022fc4 tests/test_call_80022fc4.cpp)
    target_link_libraries(test_call_80022fc4 PRIVATE am3d_exe)
    add_test(NAME call_80022fc4 COMMAND test_call_80022fc4)

    add_executable(test_call_8007f920_9 tests/test_call_8007f920_9.cpp)
    target_link_libraries(test_call_8007f920_9 PRIVATE am3d_exe)
    add_test(NAME call_8007f920_9 COMMAND test_call_8007f920_9)

    add_executable(test_call_8007f928_9 tests/test_call_8007f928_9.cpp)
    target_link_libraries(test_call_8007f928_9 PRIVATE am3d_exe)
    add_test(NAME call_8007f928_9 COMMAND test_call_8007f928_9)

    add_executable(test_call_8007f930_9 tests/test_call_8007f930_9.cpp)
    target_link_libraries(test_call_8007f930_9 PRIVATE am3d_exe)
    add_test(NAME call_8007f930_9 COMMAND test_call_8007f930_9)

    add_executable(test_call_8007f93c_9 tests/test_call_8007f93c_9.cpp)
    target_link_libraries(test_call_8007f93c_9 PRIVATE am3d_exe)
    add_test(NAME call_8007f93c_9 COMMAND test_call_8007f93c_9)

    add_executable(test_call_8007f95c_9 tests/test_call_8007f95c_9.cpp)
    target_link_libraries(test_call_8007f95c_9 PRIVATE am3d_exe)
    add_test(NAME call_8007f95c_9 COMMAND test_call_8007f95c_9)

    add_executable(test_call_8007f988_9 tests/test_call_8007f988_9.cpp)
    target_link_libraries(test_call_8007f988_9 PRIVATE am3d_exe)
    add_test(NAME call_8007f988_9 COMMAND test_call_8007f988_9)

    add_executable(test_call_8007f9a0_9 tests/test_call_8007f9a0_9.cpp)
    target_link_libraries(test_call_8007f9a0_9 PRIVATE am3d_exe)
    add_test(NAME call_8007f9a0_9 COMMAND test_call_8007f9a0_9)

    add_executable(test_call_80022fd4 tests/test_call_80022fd4.cpp)
    target_link_libraries(test_call_80022fd4 PRIVATE am3d_exe)
    add_test(NAME call_80022fd4 COMMAND test_call_80022fd4)

    add_executable(test_call_8007f920_10 tests/test_call_8007f920_10.cpp)
    target_link_libraries(test_call_8007f920_10 PRIVATE am3d_exe)
    add_test(NAME call_8007f920_10 COMMAND test_call_8007f920_10)

    add_executable(test_call_80022fe4 tests/test_call_80022fe4.cpp)
    target_link_libraries(test_call_80022fe4 PRIVATE am3d_exe)
    add_test(NAME call_80022fe4 COMMAND test_call_80022fe4)

    add_executable(test_call_80023030 tests/test_call_80023030.cpp)
    target_link_libraries(test_call_80023030 PRIVATE am3d_exe)
    add_test(NAME call_80023030 COMMAND test_call_80023030)

    add_executable(test_call_80063ed8 tests/test_call_80063ed8.cpp)
    target_link_libraries(test_call_80063ed8 PRIVATE am3d_exe)
    add_test(NAME call_80063ed8 COMMAND test_call_80063ed8)

    add_executable(test_call_80076508 tests/test_call_80076508.cpp)
    target_link_libraries(test_call_80076508 PRIVATE am3d_exe)
    add_test(NAME call_80076508 COMMAND test_call_80076508)

    add_executable(test_call_80076548 tests/test_call_80076548.cpp)
    target_link_libraries(test_call_80076548 PRIVATE am3d_exe)
    add_test(NAME call_80076548 COMMAND test_call_80076548)

    add_executable(test_call_80076540 tests/test_call_80076540.cpp)
    target_link_libraries(test_call_80076540 PRIVATE am3d_exe)
    add_test(NAME call_80076540 COMMAND test_call_80076540)

    add_executable(test_call_80063f18 tests/test_call_80063f18.cpp)
    target_link_libraries(test_call_80063f18 PRIVATE am3d_exe)
    add_test(NAME call_80063f18 COMMAND test_call_80063f18)

    add_executable(test_call_8002303c tests/test_call_8002303c.cpp)
    target_link_libraries(test_call_8002303c PRIVATE am3d_exe)
    add_test(NAME call_8002303c COMMAND test_call_8002303c)

    add_executable(test_call_80023054 tests/test_call_80023054.cpp)
    target_link_libraries(test_call_80023054 PRIVATE am3d_exe)
    add_test(NAME call_80023054 COMMAND test_call_80023054)

    add_executable(test_call_80063ed8_2 tests/test_call_80063ed8_2.cpp)
    target_link_libraries(test_call_80063ed8_2 PRIVATE am3d_exe)
    add_test(NAME call_80063ed8_2 COMMAND test_call_80063ed8_2)

    add_executable(test_call_80076508_2 tests/test_call_80076508_2.cpp)
    target_link_libraries(test_call_80076508_2 PRIVATE am3d_exe)
    add_test(NAME call_80076508_2 COMMAND test_call_80076508_2)

    add_executable(test_call_80063f18_2 tests/test_call_80063f18_2.cpp)
    target_link_libraries(test_call_80063f18_2 PRIVATE am3d_exe)
    add_test(NAME call_80063f18_2 COMMAND test_call_80063f18_2)

    add_executable(test_call_8002305c tests/test_call_8002305c.cpp)
    target_link_libraries(test_call_8002305c PRIVATE am3d_exe)
    add_test(NAME call_8002305c COMMAND test_call_8002305c)

    add_executable(test_call_80063ed8_3 tests/test_call_80063ed8_3.cpp)
    target_link_libraries(test_call_80063ed8_3 PRIVATE am3d_exe)
    add_test(NAME call_80063ed8_3 COMMAND test_call_80063ed8_3)

    add_executable(test_call_80076508_3 tests/test_call_80076508_3.cpp)
    target_link_libraries(test_call_80076508_3 PRIVATE am3d_exe)
    add_test(NAME call_80076508_3 COMMAND test_call_80076508_3)

    add_executable(test_call_80063f18_3 tests/test_call_80063f18_3.cpp)
    target_link_libraries(test_call_80063f18_3 PRIVATE am3d_exe)
    add_test(NAME call_80063f18_3 COMMAND test_call_80063f18_3)

    add_executable(test_call_800231e0 tests/test_call_800231e0.cpp)
    target_link_libraries(test_call_800231e0 PRIVATE am3d_exe)
    add_test(NAME call_800231e0 COMMAND test_call_800231e0)

    add_executable(test_call_80063ed8_4 tests/test_call_80063ed8_4.cpp)
    target_link_libraries(test_call_80063ed8_4 PRIVATE am3d_exe)
    add_test(NAME call_80063ed8_4 COMMAND test_call_80063ed8_4)

    add_executable(test_call_80076508_4 tests/test_call_80076508_4.cpp)
    target_link_libraries(test_call_80076508_4 PRIVATE am3d_exe)
    add_test(NAME call_80076508_4 COMMAND test_call_80076508_4)

    add_executable(test_call_80063f18_4 tests/test_call_80063f18_4.cpp)
    target_link_libraries(test_call_80063f18_4 PRIVATE am3d_exe)
    add_test(NAME call_80063f18_4 COMMAND test_call_80063f18_4)

    add_executable(test_call_800231f0 tests/test_call_800231f0.cpp)
    target_link_libraries(test_call_800231f0 PRIVATE am3d_exe)
    add_test(NAME call_800231f0 COMMAND test_call_800231f0)

    add_executable(test_call_80063ed8_5 tests/test_call_80063ed8_5.cpp)
    target_link_libraries(test_call_80063ed8_5 PRIVATE am3d_exe)
    add_test(NAME call_80063ed8_5 COMMAND test_call_80063ed8_5)

    add_executable(test_call_80076508_5 tests/test_call_80076508_5.cpp)
    target_link_libraries(test_call_80076508_5 PRIVATE am3d_exe)
    add_test(NAME call_80076508_5 COMMAND test_call_80076508_5)

    add_executable(test_call_80063f18_5 tests/test_call_80063f18_5.cpp)
    target_link_libraries(test_call_80063f18_5 PRIVATE am3d_exe)
    add_test(NAME call_80063f18_5 COMMAND test_call_80063f18_5)

    add_executable(test_call_80023200 tests/test_call_80023200.cpp)
    target_link_libraries(test_call_80023200 PRIVATE am3d_exe)
    add_test(NAME call_80023200 COMMAND test_call_80023200)

    add_executable(test_call_80063ed8_6 tests/test_call_80063ed8_6.cpp)
    target_link_libraries(test_call_80063ed8_6 PRIVATE am3d_exe)
    add_test(NAME call_80063ed8_6 COMMAND test_call_80063ed8_6)

    add_executable(test_call_80076508_6 tests/test_call_80076508_6.cpp)
    target_link_libraries(test_call_80076508_6 PRIVATE am3d_exe)
    add_test(NAME call_80076508_6 COMMAND test_call_80076508_6)

    add_executable(test_call_80063f18_6 tests/test_call_80063f18_6.cpp)
    target_link_libraries(test_call_80063f18_6 PRIVATE am3d_exe)
    add_test(NAME call_80063f18_6 COMMAND test_call_80063f18_6)

    add_executable(test_call_80023218 tests/test_call_80023218.cpp)
    target_link_libraries(test_call_80023218 PRIVATE am3d_exe)
    add_test(NAME call_80023218 COMMAND test_call_80023218)

    add_executable(test_call_80063ed8_7 tests/test_call_80063ed8_7.cpp)
    target_link_libraries(test_call_80063ed8_7 PRIVATE am3d_exe)
    add_test(NAME call_80063ed8_7 COMMAND test_call_80063ed8_7)

    add_executable(test_call_80076508_7 tests/test_call_80076508_7.cpp)
    target_link_libraries(test_call_80076508_7 PRIVATE am3d_exe)
    add_test(NAME call_80076508_7 COMMAND test_call_80076508_7)

    add_executable(test_call_80063f18_7 tests/test_call_80063f18_7.cpp)
    target_link_libraries(test_call_80063f18_7 PRIVATE am3d_exe)
    add_test(NAME call_80063f18_7 COMMAND test_call_80063f18_7)

    add_executable(test_call_80023234 tests/test_call_80023234.cpp)
    target_link_libraries(test_call_80023234 PRIVATE am3d_exe)
    add_test(NAME call_80023234 COMMAND test_call_80023234)

    add_executable(test_call_80063ed8_8 tests/test_call_80063ed8_8.cpp)
    target_link_libraries(test_call_80063ed8_8 PRIVATE am3d_exe)
    add_test(NAME call_80063ed8_8 COMMAND test_call_80063ed8_8)

    add_executable(test_call_80076508_8 tests/test_call_80076508_8.cpp)
    target_link_libraries(test_call_80076508_8 PRIVATE am3d_exe)
    add_test(NAME call_80076508_8 COMMAND test_call_80076508_8)

    add_executable(test_call_80063f18_8 tests/test_call_80063f18_8.cpp)
    target_link_libraries(test_call_80063f18_8 PRIVATE am3d_exe)
    add_test(NAME call_80063f18_8 COMMAND test_call_80063f18_8)

    add_executable(test_call_80023244 tests/test_call_80023244.cpp)
    target_link_libraries(test_call_80023244 PRIVATE am3d_exe)
    add_test(NAME call_80023244 COMMAND test_call_80023244)

    add_executable(test_call_80063ed8_9 tests/test_call_80063ed8_9.cpp)
    target_link_libraries(test_call_80063ed8_9 PRIVATE am3d_exe)
    add_test(NAME call_80063ed8_9 COMMAND test_call_80063ed8_9)

    add_executable(test_call_80076508_9 tests/test_call_80076508_9.cpp)
    target_link_libraries(test_call_80076508_9 PRIVATE am3d_exe)
    add_test(NAME call_80076508_9 COMMAND test_call_80076508_9)

    add_executable(test_call_80063f18_9 tests/test_call_80063f18_9.cpp)
    target_link_libraries(test_call_80063f18_9 PRIVATE am3d_exe)
    add_test(NAME call_80063f18_9 COMMAND test_call_80063f18_9)

    add_executable(test_call_80023254 tests/test_call_80023254.cpp)
    target_link_libraries(test_call_80023254 PRIVATE am3d_exe)
    add_test(NAME call_80023254 COMMAND test_call_80023254)

    add_executable(test_call_80063ed8_10 tests/test_call_80063ed8_10.cpp)
    target_link_libraries(test_call_80063ed8_10 PRIVATE am3d_exe)
    add_test(NAME call_80063ed8_10 COMMAND test_call_80063ed8_10)

    add_executable(test_call_80076508_10 tests/test_call_80076508_10.cpp)
    target_link_libraries(test_call_80076508_10 PRIVATE am3d_exe)
    add_test(NAME call_80076508_10 COMMAND test_call_80076508_10)

    add_executable(test_call_80063f18_10 tests/test_call_80063f18_10.cpp)
    target_link_libraries(test_call_80063f18_10 PRIVATE am3d_exe)
    add_test(NAME call_80063f18_10 COMMAND test_call_80063f18_10)
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
