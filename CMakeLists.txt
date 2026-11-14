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
    components/exe/call_8001b238.cpp components/exe/call_8001b17c.cpp
    components/exe/call_80076b50.cpp
    components/exe/call_80076938.cpp
    components/exe/call_800768d8.cpp
    components/exe/call_800767d8.cpp
    components/exe/call_8007a4e4.cpp
    components/exe/call_800621bc.cpp
    components/exe/call_80063b08.cpp
    components/exe/call_8006f12c.cpp
    components/exe/call_80070fb0.cpp
    components/exe/call_800644a8.cpp
    components/exe/call_80010cc4.cpp
    components/exe/call_8002fc2c.cpp
    components/exe/call_800302a4.cpp
    components/exe/call_80079270.cpp
    components/exe/call_80079b24.cpp
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
    components/exe/call_8002542c.cpp
    components/exe/call_8007d52c.cpp
    components/exe/call_80025434.cpp
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
    components/exe/call_800751d8.cpp
    components/exe/call_800753fc.cpp
    components/exe/call_800752d0.cpp
    components/exe/call_8005cc50.cpp
    components/exe/call_8005c9b0.cpp
    components/exe/call_8005cc80.cpp
    components/exe/call_8005ca00.cpp
    components/exe/call_8005ca30.cpp
    components/exe/call_8005cc88.cpp
    components/exe/call_800752e8.cpp
    components/exe/call_8007522c.cpp
    components/exe/call_800752a0.cpp
    components/exe/call_8005c014.cpp
    components/exe/call_80075370.cpp
    components/exe/call_800753bc.cpp
    components/exe/call_80074360.cpp
    components/exe/call_8007424c.cpp
    components/exe/call_8005be50.cpp
    components/exe/call_8005be3c.cpp
    components/exe/call_8005be9c.cpp
    components/exe/call_80074144.cpp
    components/exe/call_8005be28.cpp
    components/exe/call_80075318.cpp
    components/exe/call_800744f0.cpp
    components/exe/call_8007533c.cpp
    components/exe/call_80074da8.cpp
    components/exe/call_80073eec.cpp
    components/exe/call_8007466c.cpp
    components/exe/call_80073e70.cpp
    components/exe/call_80073e8c.cpp
    components/exe/call_8007560c.cpp
    components/exe/call_80075440.cpp
    components/exe/call_80073910.cpp
    components/exe/call_80073c2c.cpp
    components/exe/call_80074434.cpp
    components/exe/call_8007571c.cpp
    components/exe/call_80075758.cpp
    components/exe/call_80075c64.cpp
    components/exe/call_80075ba8.cpp
    components/exe/call_80010e24.cpp
    components/exe/call_80075f1c.cpp
    components/exe/call_800757a4.cpp
    components/exe/call_8007562c.cpp
    components/exe/call_8007569c.cpp
    components/exe/call_80074b4c.cpp
    components/exe/call_80075554.cpp
    components/exe/call_80075f3c.cpp
    components/exe/call_8007f750.cpp
    components/exe/call_800759c8.cpp
    components/exe/call_80075d38.cpp
    components/exe/call_8007490c.cpp
    components/exe/call_800757c4.cpp
    components/exe/call_80075e10.cpp
    components/exe/call_80074bd4.cpp
    components/exe/call_8005be64.cpp
    components/exe/call_8005bef8.cpp
    components/exe/call_8005bda4.cpp
    components/exe/call_8005bdd0.cpp
    components/exe/call_8005bdfc.cpp
    components/exe/call_8005bf80.cpp
    components/exe/call_8005c058.cpp
    components/exe/call_8005c0fc.cpp
    components/exe/call_8005c11c.cpp
    components/exe/call_8005c13c.cpp
    components/exe/call_8005c1a0.cpp
    components/exe/call_8005c7d8.cpp
    components/exe/call_800818cc.cpp
    components/exe/call_800818bc.cpp
    components/exe/call_800818dc.cpp
    components/exe/call_80081838.cpp
    components/exe/call_80081860.cpp
    components/exe/call_80082f84.cpp
    components/exe/call_80081964.cpp
    components/exe/call_800825a8.cpp
    components/exe/call_80081a00.cpp
    components/exe/call_80082828.cpp
    components/exe/call_80081a20.cpp
    components/exe/call_800818f8.cpp
    components/exe/call_80011cc0.cpp
    components/exe/call_8001299c.cpp
    components/exe/call_800285b8.cpp
    components/exe/call_8002884c.cpp
    components/exe/call_80028db8.cpp
    components/exe/call_80028dc4.cpp
    components/exe/call_8002a2f0.cpp
    components/exe/call_80028cf8.cpp
    components/exe/call_80028da4.cpp
    components/exe/call_80030ba4.cpp
    components/exe/call_80030dac.cpp
    components/exe/call_8002657c.cpp
    components/exe/call_80011cd4.cpp
    components/exe/call_80037cf8.cpp
    components/exe/call_80039c24.cpp
    components/exe/call_8003cd44.cpp
    components/exe/call_8003ec04.cpp
    components/exe/call_8003f590.cpp
    components/exe/call_8003f770.cpp
    components/exe/call_800445f4.cpp
    components/exe/call_80060c24.cpp
    components/exe/call_800644bc.cpp
    components/exe/call_800644d4.cpp
    components/exe/call_800644e4.cpp
    components/exe/call_80042180.cpp
    components/exe/call_800436b4.cpp
    components/exe/call_8004b68c.cpp
    components/exe/call_800644f0.cpp
    components/exe/call_80064500.cpp
    components/exe/call_80064518.cpp
    components/exe/call_80065304.cpp
    components/exe/call_800655e4.cpp
    components/exe/call_800655fc.cpp
    components/exe/call_80065624.cpp
    components/exe/call_80065638.cpp
    components/exe/call_80065b08.cpp
    components/exe/call_80011da0.cpp
    components/exe/call_8006658c.cpp
    components/exe/call_800710cc.cpp
    components/exe/call_800710dc.cpp
    components/exe/call_800710ec.cpp
    components/exe/call_800710fc.cpp
    components/exe/call_8007110c.cpp
    components/exe/call_80071134.cpp
    components/exe/call_8007115c.cpp
    components/exe/call_80071184.cpp
    components/exe/call_80071fe4.cpp
    components/exe/call_800793d4.cpp
    components/exe/call_800124cc.cpp
    components/exe/call_8007b118.cpp
    components/exe/call_8007b128.cpp
    components/exe/call_8007c2a8.cpp
    components/exe/call_8007c2b8.cpp
    components/exe/call_8007c2c4.cpp
    components/exe/call_8007ca78.cpp
    components/exe/call_8007e198.cpp
    components/exe/call_8007e1a8.cpp
    components/exe/call_8007e2c4.cpp
    components/exe/call_8007f040.cpp
    components/exe/call_8007fbdc.cpp
    components/exe/call_800125ac.cpp
    components/exe/call_8007fc1c.cpp
    components/exe/call_8007fc3c.cpp
    components/exe/call_80084610.cpp
    components/exe/call_8008498c.cpp
    components/exe/call_80085820.cpp
    components/exe/call_800864c0.cpp
    components/exe/call_8007fbec.cpp
    components/exe/call_80080c5c.cpp
    components/exe/call_800856ac.cpp
    components/exe/call_80085d94.cpp
    components/exe/call_80085dac.cpp
    components/exe/call_80012a3c.cpp
    components/exe/call_8008918c.cpp
    components/exe/call_8008ac3c.cpp
    components/exe/call_8008ac5c.cpp
    components/exe/call_8008ef18.cpp
    components/exe/call_8008f9dc.cpp
    components/exe/call_8008fad4.cpp
    components/exe/call_80090318.cpp
    components/exe/call_80095730.cpp
    components/exe/call_800961c4.cpp
    components/exe/call_80096d38.cpp
    components/exe/call_80096dac.cpp
    components/exe/call_80010c7c.cpp
    components/exe/call_800793ec.cpp
    components/exe/call_80012e94.cpp
    components/exe/call_80012f94.cpp
    components/exe/call_800656ec.cpp
    components/exe/call_80076480.cpp
    components/exe/call_80076490.cpp
    components/exe/call_800764a0.cpp
    components/exe/call_80085dbc.cpp
    components/exe/call_80085dcc.cpp
    components/exe/call_8008917c.cpp
    components/exe/call_8008c29c.cpp
    components/exe/call_80012fe8.cpp
    components/exe/call_80076450.cpp
    components/exe/call_80076468.cpp
    components/exe/call_80096d18.cpp
    components/exe/call_80096d4c.cpp
    components/exe/call_80096d6c.cpp
    components/exe/call_80096d8c.cpp
    components/exe/call_80013318.cpp
    components/exe/call_800132dc.cpp
    components/exe/call_80014b7c.cpp
    components/exe/call_80015a50.cpp
    components/exe/call_80015cfc.cpp
    components/exe/call_8003741c.cpp
    components/exe/call_80022dc0.cpp
    components/exe/call_8002134c.cpp
    components/exe/call_80017484.cpp
    components/exe/call_80036258.cpp
    components/exe/call_80036278.cpp
    components/exe/call_800265a4.cpp
    components/exe/call_800268e4.cpp
    components/exe/call_800278b8.cpp
    components/exe/call_800329d0.cpp
    components/exe/call_80036774.cpp
    components/exe/call_800367ac.cpp
    components/exe/call_80018b64.cpp
    components/exe/call_80057714.cpp
    components/exe/call_8005775c.cpp
    components/exe/call_800265b8.cpp
    components/exe/call_8003c514.cpp
    components/exe/call_8003b774.cpp
    components/exe/call_80038728.cpp
    components/exe/call_80038798.cpp
    components/exe/call_80038808.cpp
    components/exe/call_800450d4.cpp
    components/exe/call_8003ff08.cpp
    components/exe/call_80042ae4.cpp
    components/exe/call_80044f94.cpp
    components/exe/call_8003d874.cpp
    components/exe/call_80049330.cpp
    components/exe/call_8005eeb4.cpp
    components/exe/call_8004c4e8.cpp
    components/exe/call_8005e5a0.cpp
    components/exe/call_8005e5c0.cpp
    components/exe/call_800608dc.cpp
    components/exe/call_80076b78.cpp
    components/exe/call_80076ba0.cpp
    components/exe/call_80077038.cpp
    components/exe/call_80078260.cpp
    components/exe/call_80075bc8.cpp
    components/exe/call_80076e98.cpp
    components/exe/call_8007ec74.cpp
    components/exe/call_8004dbdc.cpp
    components/exe/call_8004dee8.cpp
    components/exe/call_8007941c.cpp
    components/exe/call_8007b150.cpp
    components/exe/call_8007b170.cpp
    components/exe/call_80081e44.cpp
    components/exe/call_80081e64.cpp
    components/exe/call_80081ea8.cpp
    components/exe/call_80084260.cpp
    components/exe/call_8004974c.cpp
    components/exe/call_8004dbfc.cpp
    components/exe/call_80079e1c.cpp
    components/exe/call_8007f3c8.cpp
    components/exe/call_80083374.cpp
    components/exe/call_800834dc.cpp
    components/exe/call_800835dc.cpp
    components/exe/call_800849ac.cpp
    components/exe/call_8008dabc.cpp
    components/exe/call_8008f6cc.cpp
    components/exe/call_8008f6dc.cpp
    components/exe/call_8008f6ec.cpp
    components/exe/call_8004ff84.cpp
    components/exe/call_80066b7c.cpp
    components/exe/call_8007c17c.cpp
    components/exe/call_8007c1a8.cpp
    components/exe/call_8007c1c8.cpp
    components/exe/call_8007cf60.cpp
    components/exe/call_8008f6fc.cpp
    components/exe/call_8008f70c.cpp
    components/exe/call_8008f71c.cpp
    components/exe/call_8008f9cc.cpp
    components/exe/call_80075404.cpp
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
    components/exe/call_80023264.cpp
    components/exe/call_8007f920_11.cpp
    components/exe/call_80023274.cpp
    components/exe/call_80063ed8_11.cpp
    components/exe/call_80076508_11.cpp
    components/exe/call_80063f18_11.cpp
    components/exe/call_80023288.cpp
    components/exe/call_800235a4.cpp
    components/exe/call_800235b0.cpp
    components/exe/call_80063ed4.cpp
    components/exe/call_80063ed8_12.cpp
    components/exe/call_80076508_12.cpp
    components/exe/call_80063f18_12.cpp
    components/exe/call_800235bc.cpp
    components/exe/call_800235a4_2.cpp
    components/exe/call_800235b0_2.cpp
    components/exe/call_80063ed8_13.cpp
    components/exe/call_80076508_13.cpp
    components/exe/call_80063f18_13.cpp
    components/exe/call_800235ec.cpp
    components/exe/call_80023674.cpp
    components/exe/call_80023914.cpp
    components/exe/call_800255d8.cpp
    components/exe/call_80045374.cpp
    components/exe/call_8007d234.cpp
    components/exe/call_800453a8.cpp
    components/exe/call_80062434_5.cpp
    components/exe/call_80061f80_5.cpp
    components/exe/call_80062474_4.cpp
    components/exe/call_80075198_11.cpp
    components/exe/call_800624cc_4.cpp
    components/exe/call_80045418.cpp
    components/exe/call_8007e290.cpp
    components/exe/call_80045524.cpp
    components/exe/call_8007e248.cpp
    components/exe/call_8007e280.cpp
    components/exe/call_8004552c.cpp
    components/exe/call_8007eac8.cpp
    components/exe/call_8007f920_12.cpp
    components/exe/call_8007eafc.cpp
    components/exe/call_8007f920_13.cpp
    components/exe/call_8007f920_14.cpp
    components/exe/call_8007eb10.cpp
    components/exe/call_80045540.cpp
    components/exe/call_80045aa8.cpp
    components/exe/call_80045548.cpp
    components/exe/call_800452ac.cpp
    components/exe/call_80045570.cpp
    components/exe/call_800255e4.cpp
    components/exe/call_80065894.cpp
    components/exe/call_80063ed8_14.cpp
    components/exe/call_80076508_14.cpp
    components/exe/call_80063f18_14.cpp
    components/exe/call_800658bc.cpp
    components/exe/call_80063ed8_15.cpp
    components/exe/call_80076508_15.cpp
    components/exe/call_80063f18_15.cpp
    components/exe/call_800658ec.cpp
    components/exe/call_80063ed8_16.cpp
    components/exe/call_80076508_16.cpp
    components/exe/call_80063f18_16.cpp
    components/exe/call_80065904.cpp
    components/exe/call_80063ed8_17.cpp
    components/exe/call_80076508_17.cpp
    components/exe/call_80063f18_17.cpp
    components/exe/call_8006591c.cpp
    components/exe/call_80063ed8_18.cpp
    components/exe/call_80076508_18.cpp
    components/exe/call_80063f18_18.cpp
    components/exe/call_80065954.cpp
    components/exe/call_8005b6dc.cpp
    components/exe/call_8006596c.cpp
    components/exe/call_80062e0c.cpp
    components/exe/call_80062434_6.cpp
    components/exe/call_80061f80_6.cpp
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

add_library(am3d_platform_core STATIC
    components/platform/fill_vram.cpp
    components/platform/front_tim.cpp)
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
    add_executable(test_call_800644a8 tests/test_call_800644a8.cpp)
    target_link_libraries(test_call_800644a8 PRIVATE am3d_exe)
    add_test(NAME call_800644a8 COMMAND test_call_800644a8)
    add_executable(test_call_80070fb0 tests/test_call_80070fb0.cpp)
    target_link_libraries(test_call_80070fb0 PRIVATE am3d_exe)
    add_test(NAME call_80070fb0 COMMAND test_call_80070fb0)
    add_executable(test_call_8006f12c tests/test_call_8006f12c.cpp)
    target_link_libraries(test_call_8006f12c PRIVATE am3d_exe)
    add_test(NAME call_8006f12c COMMAND test_call_8006f12c)
    add_executable(test_call_80063b08 tests/test_call_80063b08.cpp)
    target_link_libraries(test_call_80063b08 PRIVATE am3d_exe)
    add_test(NAME call_80063b08 COMMAND test_call_80063b08)
    add_executable(test_call_800621bc tests/test_call_800621bc.cpp)
    target_link_libraries(test_call_800621bc PRIVATE am3d_exe)
    add_test(NAME call_800621bc COMMAND test_call_800621bc)
    add_executable(test_call_8007a4e4 tests/test_call_8007a4e4.cpp)
    target_link_libraries(test_call_8007a4e4 PRIVATE am3d_exe)
    add_test(NAME call_8007a4e4 COMMAND test_call_8007a4e4)
    add_executable(test_call_8001b238 tests/test_call_8001b238.cpp)
    target_link_libraries(test_call_8001b238 PRIVATE am3d_exe)
    add_test(NAME call_8001b238 COMMAND test_call_8001b238)
    add_executable(test_call_80010cc4 tests/test_call_80010cc4.cpp)
    target_link_libraries(test_call_80010cc4 PRIVATE am3d_exe)
    add_test(NAME call_80010cc4 COMMAND test_call_80010cc4)
    add_executable(test_call_8002fc2c tests/test_call_8002fc2c.cpp)
    target_link_libraries(test_call_8002fc2c PRIVATE am3d_exe)
    add_test(NAME call_8002fc2c COMMAND test_call_8002fc2c)
    add_executable(test_call_800302a4 tests/test_call_800302a4.cpp)
    target_link_libraries(test_call_800302a4 PRIVATE am3d_exe)
    add_test(NAME call_800302a4 COMMAND test_call_800302a4)
    add_executable(test_call_80079b24 tests/test_call_80079b24.cpp)
    target_link_libraries(test_call_80079b24 PRIVATE am3d_exe)
    add_test(NAME call_80079b24 COMMAND test_call_80079b24)
    add_executable(test_call_80079270 tests/test_call_80079270.cpp)
    target_link_libraries(test_call_80079270 PRIVATE am3d_exe)
    add_test(NAME call_80079270 COMMAND test_call_80079270)
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
    add_executable(test_call_8002542c tests/test_call_8002542c.cpp)
    target_link_libraries(test_call_8002542c PRIVATE am3d_exe)
    add_test(NAME call_8002542c COMMAND test_call_8002542c)
    add_executable(test_call_8007d52c tests/test_call_8007d52c.cpp)
    target_link_libraries(test_call_8007d52c PRIVATE am3d_exe)
    add_test(NAME call_8007d52c COMMAND test_call_8007d52c)
    add_executable(test_call_80025434 tests/test_call_80025434.cpp)
    target_link_libraries(test_call_80025434 PRIVATE am3d_exe)
    add_test(NAME call_80025434 COMMAND test_call_80025434)
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
    add_executable(test_call_800751d8 tests/test_call_800751d8.cpp)
    target_link_libraries(test_call_800751d8 PRIVATE am3d_exe)
    add_test(NAME call_800751d8 COMMAND test_call_800751d8)
    add_executable(test_call_800753fc tests/test_call_800753fc.cpp)
    target_link_libraries(test_call_800753fc PRIVATE am3d_exe)
    add_test(NAME call_800753fc COMMAND test_call_800753fc)
    add_executable(test_call_800752d0 tests/test_call_800752d0.cpp)
    target_link_libraries(test_call_800752d0 PRIVATE am3d_exe)
    add_test(NAME call_800752d0 COMMAND test_call_800752d0)
    add_executable(test_call_8005cc50 tests/test_call_8005cc50.cpp)
    target_link_libraries(test_call_8005cc50 PRIVATE am3d_exe)
    add_test(NAME call_8005cc50 COMMAND test_call_8005cc50)
    add_executable(test_call_8005c9b0 tests/test_call_8005c9b0.cpp)
    target_link_libraries(test_call_8005c9b0 PRIVATE am3d_exe)
    add_test(NAME call_8005c9b0 COMMAND test_call_8005c9b0)
    add_executable(test_call_8005cc80 tests/test_call_8005cc80.cpp)
    target_link_libraries(test_call_8005cc80 PRIVATE am3d_exe)
    add_test(NAME call_8005cc80 COMMAND test_call_8005cc80)
    add_executable(test_call_8005ca00 tests/test_call_8005ca00.cpp)
    target_link_libraries(test_call_8005ca00 PRIVATE am3d_exe)
    add_test(NAME call_8005ca00 COMMAND test_call_8005ca00)
    add_executable(test_call_8005ca30 tests/test_call_8005ca30.cpp)
    target_link_libraries(test_call_8005ca30 PRIVATE am3d_exe)
    add_test(NAME call_8005ca30 COMMAND test_call_8005ca30)
    add_executable(test_call_8005cc88 tests/test_call_8005cc88.cpp)
    target_link_libraries(test_call_8005cc88 PRIVATE am3d_exe)
    add_test(NAME call_8005cc88 COMMAND test_call_8005cc88)
    add_executable(test_call_800752e8 tests/test_call_800752e8.cpp)
    target_link_libraries(test_call_800752e8 PRIVATE am3d_exe)
    add_test(NAME call_800752e8 COMMAND test_call_800752e8)
    add_executable(test_call_8007522c tests/test_call_8007522c.cpp)
    target_link_libraries(test_call_8007522c PRIVATE am3d_exe)
    add_test(NAME call_8007522c COMMAND test_call_8007522c)
    add_executable(test_call_800752a0 tests/test_call_800752a0.cpp)
    target_link_libraries(test_call_800752a0 PRIVATE am3d_exe)
    add_test(NAME call_800752a0 COMMAND test_call_800752a0)
    add_executable(test_call_8005c014 tests/test_call_8005c014.cpp)
    target_link_libraries(test_call_8005c014 PRIVATE am3d_exe)
    add_test(NAME call_8005c014 COMMAND test_call_8005c014)
    add_executable(test_call_80073eec tests/test_call_80073eec.cpp)
    target_link_libraries(test_call_80073eec PRIVATE am3d_exe)
    add_test(NAME call_80073eec COMMAND test_call_80073eec)
    add_executable(test_call_80073fb0 tests/test_call_80073fb0.cpp)
    target_link_libraries(test_call_80073fb0 PRIVATE am3d_exe)
    add_test(NAME call_80073fb0 COMMAND test_call_80073fb0)
    add_executable(test_call_800741b8 tests/test_call_800741b8.cpp)
    target_link_libraries(test_call_800741b8 PRIVATE am3d_exe)
    add_test(NAME call_800741b8 COMMAND test_call_800741b8)
    add_executable(test_call_8007466c tests/test_call_8007466c.cpp)
    target_link_libraries(test_call_8007466c PRIVATE am3d_exe)
    add_test(NAME call_8007466c COMMAND test_call_8007466c)
    add_executable(test_call_80073e8c tests/test_call_80073e8c.cpp)
    target_link_libraries(test_call_80073e8c PRIVATE am3d_exe)
    add_test(NAME call_80073e8c COMMAND test_call_80073e8c)
    add_executable(test_call_8007560c tests/test_call_8007560c.cpp)
    target_link_libraries(test_call_8007560c PRIVATE am3d_exe)
    add_test(NAME call_8007560c COMMAND test_call_8007560c)
    add_executable(test_call_80075440 tests/test_call_80075440.cpp)
    target_link_libraries(test_call_80075440 PRIVATE am3d_exe)
    add_test(NAME call_80075440 COMMAND test_call_80075440)
    add_executable(test_call_80073910 tests/test_call_80073910.cpp)
    target_link_libraries(test_call_80073910 PRIVATE am3d_exe)
    add_test(NAME call_80073910 COMMAND test_call_80073910)
    add_executable(test_call_80073c2c tests/test_call_80073c2c.cpp)
    target_link_libraries(test_call_80073c2c PRIVATE am3d_exe)
    add_test(NAME call_80073c2c COMMAND test_call_80073c2c)
    add_executable(test_call_80074434 tests/test_call_80074434.cpp)
    target_link_libraries(test_call_80074434 PRIVATE am3d_exe)
    add_test(NAME call_80074434 COMMAND test_call_80074434)
    add_executable(test_call_8007571c tests/test_call_8007571c.cpp)
    target_link_libraries(test_call_8007571c PRIVATE am3d_exe)
    add_test(NAME call_8007571c COMMAND test_call_8007571c)
    add_executable(test_call_80075758 tests/test_call_80075758.cpp)
    target_link_libraries(test_call_80075758 PRIVATE am3d_exe)
    add_test(NAME call_80075758 COMMAND test_call_80075758)
    add_executable(test_call_80075c64 tests/test_call_80075c64.cpp)
    target_link_libraries(test_call_80075c64 PRIVATE am3d_exe)
    add_test(NAME call_80075c64 COMMAND test_call_80075c64)
    add_executable(test_call_80075ba8 tests/test_call_80075ba8.cpp)
    target_link_libraries(test_call_80075ba8 PRIVATE am3d_exe)
    add_test(NAME call_80075ba8 COMMAND test_call_80075ba8)
    add_executable(test_call_80010e24 tests/test_call_80010e24.cpp)
    target_link_libraries(test_call_80010e24 PRIVATE am3d_exe)
    add_test(NAME call_80010e24 COMMAND test_call_80010e24)
    add_executable(test_call_80075f1c tests/test_call_80075f1c.cpp)
    target_link_libraries(test_call_80075f1c PRIVATE am3d_exe)
    add_test(NAME call_80075f1c COMMAND test_call_80075f1c)
    add_executable(test_call_800757a4 tests/test_call_800757a4.cpp)
    target_link_libraries(test_call_800757a4 PRIVATE am3d_exe)
    add_test(NAME call_800757a4 COMMAND test_call_800757a4)
    add_executable(test_call_8007562c tests/test_call_8007562c.cpp)
    target_link_libraries(test_call_8007562c PRIVATE am3d_exe)
    add_test(NAME call_8007562c COMMAND test_call_8007562c)
    add_executable(test_call_8007569c tests/test_call_8007569c.cpp)
    target_link_libraries(test_call_8007569c PRIVATE am3d_exe)
    add_test(NAME call_8007569c COMMAND test_call_8007569c)
    add_executable(test_call_80074b4c tests/test_call_80074b4c.cpp)
    target_link_libraries(test_call_80074b4c PRIVATE am3d_exe)
    add_test(NAME call_80074b4c COMMAND test_call_80074b4c)
    add_executable(test_call_80075554 tests/test_call_80075554.cpp)
    target_link_libraries(test_call_80075554 PRIVATE am3d_exe)
    add_test(NAME call_80075554 COMMAND test_call_80075554)
    add_executable(test_call_80075f3c tests/test_call_80075f3c.cpp)
    target_link_libraries(test_call_80075f3c PRIVATE am3d_exe)
    add_test(NAME call_80075f3c COMMAND test_call_80075f3c)
    add_executable(test_call_8007f750 tests/test_call_8007f750.cpp)
    target_link_libraries(test_call_8007f750 PRIVATE am3d_exe)
    add_test(NAME call_8007f750 COMMAND test_call_8007f750)
    add_executable(test_call_800759c8 tests/test_call_800759c8.cpp)
    target_link_libraries(test_call_800759c8 PRIVATE am3d_exe)
    add_test(NAME call_800759c8 COMMAND test_call_800759c8)
    add_executable(test_call_80075d38 tests/test_call_80075d38.cpp)
    target_link_libraries(test_call_80075d38 PRIVATE am3d_exe)
    add_test(NAME call_80075d38 COMMAND test_call_80075d38)
    add_executable(test_call_8007490c tests/test_call_8007490c.cpp)
    target_link_libraries(test_call_8007490c PRIVATE am3d_exe)
    add_test(NAME call_8007490c COMMAND test_call_8007490c)
    add_executable(test_call_800757c4 tests/test_call_800757c4.cpp)
    target_link_libraries(test_call_800757c4 PRIVATE am3d_exe)
    add_test(NAME call_800757c4 COMMAND test_call_800757c4)
    add_executable(test_call_80075e10 tests/test_call_80075e10.cpp)
    target_link_libraries(test_call_80075e10 PRIVATE am3d_exe)
    add_test(NAME call_80075e10 COMMAND test_call_80075e10)
    add_executable(test_call_80074bd4 tests/test_call_80074bd4.cpp)
    target_link_libraries(test_call_80074bd4 PRIVATE am3d_exe)
    add_test(NAME call_80074bd4 COMMAND test_call_80074bd4)
    add_executable(test_call_8005be64 tests/test_call_8005be64.cpp)
    target_link_libraries(test_call_8005be64 PRIVATE am3d_exe)
    add_test(NAME call_8005be64 COMMAND test_call_8005be64)
    add_executable(test_call_8005bef8 tests/test_call_8005bef8.cpp)
    target_link_libraries(test_call_8005bef8 PRIVATE am3d_exe)
    add_test(NAME call_8005bef8 COMMAND test_call_8005bef8)
    add_executable(test_call_8005bda4 tests/test_call_8005bda4.cpp)
    target_link_libraries(test_call_8005bda4 PRIVATE am3d_exe)
    add_test(NAME call_8005bda4 COMMAND test_call_8005bda4)
    add_executable(test_call_8005bdd0 tests/test_call_8005bdd0.cpp)
    target_link_libraries(test_call_8005bdd0 PRIVATE am3d_exe)
    add_test(NAME call_8005bdd0 COMMAND test_call_8005bdd0)
    add_executable(test_call_8005bdfc tests/test_call_8005bdfc.cpp)
    target_link_libraries(test_call_8005bdfc PRIVATE am3d_exe)
    add_test(NAME call_8005bdfc COMMAND test_call_8005bdfc)
    add_executable(test_call_8005bf80 tests/test_call_8005bf80.cpp)
    target_link_libraries(test_call_8005bf80 PRIVATE am3d_exe)
    add_test(NAME call_8005bf80 COMMAND test_call_8005bf80)
    add_executable(test_call_8005c058 tests/test_call_8005c058.cpp)
    target_link_libraries(test_call_8005c058 PRIVATE am3d_exe)
    add_test(NAME call_8005c058 COMMAND test_call_8005c058)
    add_executable(test_call_8005c0fc tests/test_call_8005c0fc.cpp)
    target_link_libraries(test_call_8005c0fc PRIVATE am3d_exe)
    add_test(NAME call_8005c0fc COMMAND test_call_8005c0fc)
    add_executable(test_call_8005c11c tests/test_call_8005c11c.cpp)
    target_link_libraries(test_call_8005c11c PRIVATE am3d_exe)
    add_test(NAME call_8005c11c COMMAND test_call_8005c11c)
    add_executable(test_call_8005c13c tests/test_call_8005c13c.cpp)
    target_link_libraries(test_call_8005c13c PRIVATE am3d_exe)
    add_test(NAME call_8005c13c COMMAND test_call_8005c13c)
    add_executable(test_call_8005c1a0 tests/test_call_8005c1a0.cpp)
    target_link_libraries(test_call_8005c1a0 PRIVATE am3d_exe)
    add_test(NAME call_8005c1a0 COMMAND test_call_8005c1a0)
    add_executable(test_call_8005c7d8 tests/test_call_8005c7d8.cpp)
    target_link_libraries(test_call_8005c7d8 PRIVATE am3d_exe)
    add_test(NAME call_8005c7d8 COMMAND test_call_8005c7d8)
    add_executable(test_call_800818cc tests/test_call_800818cc.cpp)
    target_link_libraries(test_call_800818cc PRIVATE am3d_exe)
    add_test(NAME call_800818cc COMMAND test_call_800818cc)
    add_executable(test_call_800818bc tests/test_call_800818bc.cpp)
    target_link_libraries(test_call_800818bc PRIVATE am3d_exe)
    add_test(NAME call_800818bc COMMAND test_call_800818bc)
    add_executable(test_call_800818dc tests/test_call_800818dc.cpp)
    target_link_libraries(test_call_800818dc PRIVATE am3d_exe)
    add_test(NAME call_800818dc COMMAND test_call_800818dc)
    add_executable(test_call_80081838 tests/test_call_80081838.cpp)
    target_link_libraries(test_call_80081838 PRIVATE am3d_exe)
    add_test(NAME call_80081838 COMMAND test_call_80081838)
    add_executable(test_call_80081860 tests/test_call_80081860.cpp)
    target_link_libraries(test_call_80081860 PRIVATE am3d_exe)
    add_test(NAME call_80081860 COMMAND test_call_80081860)
    add_executable(test_call_80082f84 tests/test_call_80082f84.cpp)
    target_link_libraries(test_call_80082f84 PRIVATE am3d_exe)
    add_test(NAME call_80082f84 COMMAND test_call_80082f84)
    add_executable(test_call_80081964 tests/test_call_80081964.cpp)
    target_link_libraries(test_call_80081964 PRIVATE am3d_exe)
    add_test(NAME call_80081964 COMMAND test_call_80081964)
    add_executable(test_call_800825a8 tests/test_call_800825a8.cpp)
    target_link_libraries(test_call_800825a8 PRIVATE am3d_exe)
    add_test(NAME call_800825a8 COMMAND test_call_800825a8)
    add_executable(test_call_80081a00 tests/test_call_80081a00.cpp)
    target_link_libraries(test_call_80081a00 PRIVATE am3d_exe)
    add_test(NAME call_80081a00 COMMAND test_call_80081a00)
    add_executable(test_call_80082828 tests/test_call_80082828.cpp)
    target_link_libraries(test_call_80082828 PRIVATE am3d_exe)
    add_test(NAME call_80082828 COMMAND test_call_80082828)
    add_executable(test_call_80081a20 tests/test_call_80081a20.cpp)
    target_link_libraries(test_call_80081a20 PRIVATE am3d_exe)
    add_test(NAME call_80081a20 COMMAND test_call_80081a20)
    add_executable(test_call_800818f8 tests/test_call_800818f8.cpp)
    target_link_libraries(test_call_800818f8 PRIVATE am3d_exe)
    add_test(NAME call_800818f8 COMMAND test_call_800818f8)
    add_executable(test_call_80011cc0 tests/test_call_80011cc0.cpp)
    target_link_libraries(test_call_80011cc0 PRIVATE am3d_exe)
    add_test(NAME call_80011cc0 COMMAND test_call_80011cc0)
    add_executable(test_call_8001299c tests/test_call_8001299c.cpp)
    target_link_libraries(test_call_8001299c PRIVATE am3d_exe)
    add_test(NAME call_8001299c COMMAND test_call_8001299c)
    add_executable(test_call_800285b8 tests/test_call_800285b8.cpp)
    target_link_libraries(test_call_800285b8 PRIVATE am3d_exe)
    add_test(NAME call_800285b8 COMMAND test_call_800285b8)
    add_executable(test_call_8002884c tests/test_call_8002884c.cpp)
    target_link_libraries(test_call_8002884c PRIVATE am3d_exe)
    add_test(NAME call_8002884c COMMAND test_call_8002884c)
    add_executable(test_call_80028db8 tests/test_call_80028db8.cpp)
    target_link_libraries(test_call_80028db8 PRIVATE am3d_exe)
    add_test(NAME call_80028db8 COMMAND test_call_80028db8)
    add_executable(test_call_80028dc4 tests/test_call_80028dc4.cpp)
    target_link_libraries(test_call_80028dc4 PRIVATE am3d_exe)
    add_test(NAME call_80028dc4 COMMAND test_call_80028dc4)
    add_executable(test_call_8002a2f0 tests/test_call_8002a2f0.cpp)
    target_link_libraries(test_call_8002a2f0 PRIVATE am3d_exe)
    add_test(NAME call_8002a2f0 COMMAND test_call_8002a2f0)
    add_executable(test_call_80028cf8 tests/test_call_80028cf8.cpp)
    target_link_libraries(test_call_80028cf8 PRIVATE am3d_exe)
    add_test(NAME call_80028cf8 COMMAND test_call_80028cf8)
    add_executable(test_call_80028da4 tests/test_call_80028da4.cpp)
    target_link_libraries(test_call_80028da4 PRIVATE am3d_exe)
    add_test(NAME call_80028da4 COMMAND test_call_80028da4)
    add_executable(test_call_80030ba4 tests/test_call_80030ba4.cpp)
    target_link_libraries(test_call_80030ba4 PRIVATE am3d_exe)
    add_test(NAME call_80030ba4 COMMAND test_call_80030ba4)
    add_executable(test_call_80030dac tests/test_call_80030dac.cpp)
    target_link_libraries(test_call_80030dac PRIVATE am3d_exe)
    add_test(NAME call_80030dac COMMAND test_call_80030dac)
    add_executable(test_call_8002657c tests/test_call_8002657c.cpp)
    target_link_libraries(test_call_8002657c PRIVATE am3d_exe)
    add_test(NAME call_8002657c COMMAND test_call_8002657c)
    add_executable(test_call_80011cd4 tests/test_call_80011cd4.cpp)
    target_link_libraries(test_call_80011cd4 PRIVATE am3d_exe)
    add_test(NAME call_80011cd4 COMMAND test_call_80011cd4)
    add_executable(test_call_80037cf8 tests/test_call_80037cf8.cpp)
    target_link_libraries(test_call_80037cf8 PRIVATE am3d_exe)
    add_test(NAME call_80037cf8 COMMAND test_call_80037cf8)
    add_executable(test_call_80039c24 tests/test_call_80039c24.cpp)
    target_link_libraries(test_call_80039c24 PRIVATE am3d_exe)
    add_test(NAME call_80039c24 COMMAND test_call_80039c24)
    add_executable(test_call_8003cd44 tests/test_call_8003cd44.cpp)
    target_link_libraries(test_call_8003cd44 PRIVATE am3d_exe)
    add_test(NAME call_8003cd44 COMMAND test_call_8003cd44)
    add_executable(test_call_8003ec04 tests/test_call_8003ec04.cpp)
    target_link_libraries(test_call_8003ec04 PRIVATE am3d_exe)
    add_test(NAME call_8003ec04 COMMAND test_call_8003ec04)
    add_executable(test_call_8003f590 tests/test_call_8003f590.cpp)
    target_link_libraries(test_call_8003f590 PRIVATE am3d_exe)
    add_test(NAME call_8003f590 COMMAND test_call_8003f590)
    add_executable(test_call_8003f770 tests/test_call_8003f770.cpp)
    target_link_libraries(test_call_8003f770 PRIVATE am3d_exe)
    add_test(NAME call_8003f770 COMMAND test_call_8003f770)
    add_executable(test_call_800445f4 tests/test_call_800445f4.cpp)
    target_link_libraries(test_call_800445f4 PRIVATE am3d_exe)
    add_test(NAME call_800445f4 COMMAND test_call_800445f4)
    add_executable(test_call_80060c24 tests/test_call_80060c24.cpp)
    target_link_libraries(test_call_80060c24 PRIVATE am3d_exe)
    add_test(NAME call_80060c24 COMMAND test_call_80060c24)
    add_executable(test_call_800644bc tests/test_call_800644bc.cpp)
    target_link_libraries(test_call_800644bc PRIVATE am3d_exe)
    add_test(NAME call_800644bc COMMAND test_call_800644bc)
    add_executable(test_call_800644d4 tests/test_call_800644d4.cpp)
    target_link_libraries(test_call_800644d4 PRIVATE am3d_exe)
    add_test(NAME call_800644d4 COMMAND test_call_800644d4)
    add_executable(test_call_800644e4 tests/test_call_800644e4.cpp)
    target_link_libraries(test_call_800644e4 PRIVATE am3d_exe)
    add_test(NAME call_800644e4 COMMAND test_call_800644e4)
    add_executable(test_call_80042180 tests/test_call_80042180.cpp)
    target_link_libraries(test_call_80042180 PRIVATE am3d_exe)
    add_test(NAME call_80042180 COMMAND test_call_80042180)
    add_executable(test_call_800436b4 tests/test_call_800436b4.cpp)
    target_link_libraries(test_call_800436b4 PRIVATE am3d_exe)
    add_test(NAME call_800436b4 COMMAND test_call_800436b4)
    add_executable(test_call_8004b68c tests/test_call_8004b68c.cpp)
    target_link_libraries(test_call_8004b68c PRIVATE am3d_exe)
    add_test(NAME call_8004b68c COMMAND test_call_8004b68c)
    add_executable(test_call_800644f0 tests/test_call_800644f0.cpp)
    target_link_libraries(test_call_800644f0 PRIVATE am3d_exe)
    add_test(NAME call_800644f0 COMMAND test_call_800644f0)
    add_executable(test_call_80064500 tests/test_call_80064500.cpp)
    target_link_libraries(test_call_80064500 PRIVATE am3d_exe)
    add_test(NAME call_80064500 COMMAND test_call_80064500)
    add_executable(test_call_80064518 tests/test_call_80064518.cpp)
    target_link_libraries(test_call_80064518 PRIVATE am3d_exe)
    add_test(NAME call_80064518 COMMAND test_call_80064518)
    add_executable(test_call_80065304 tests/test_call_80065304.cpp)
    target_link_libraries(test_call_80065304 PRIVATE am3d_exe)
    add_test(NAME call_80065304 COMMAND test_call_80065304)
    add_executable(test_call_800655e4 tests/test_call_800655e4.cpp)
    target_link_libraries(test_call_800655e4 PRIVATE am3d_exe)
    add_test(NAME call_800655e4 COMMAND test_call_800655e4)
    add_executable(test_call_800655fc tests/test_call_800655fc.cpp)
    target_link_libraries(test_call_800655fc PRIVATE am3d_exe)
    add_test(NAME call_800655fc COMMAND test_call_800655fc)
    add_executable(test_call_80065624 tests/test_call_80065624.cpp)
    target_link_libraries(test_call_80065624 PRIVATE am3d_exe)
    add_test(NAME call_80065624 COMMAND test_call_80065624)
    add_executable(test_call_80065638 tests/test_call_80065638.cpp)
    target_link_libraries(test_call_80065638 PRIVATE am3d_exe)
    add_test(NAME call_80065638 COMMAND test_call_80065638)
    add_executable(test_call_80065b08 tests/test_call_80065b08.cpp)
    target_link_libraries(test_call_80065b08 PRIVATE am3d_exe)
    add_test(NAME call_80065b08 COMMAND test_call_80065b08)
    add_executable(test_call_80011da0 tests/test_call_80011da0.cpp)
    target_link_libraries(test_call_80011da0 PRIVATE am3d_exe)
    add_test(NAME call_80011da0 COMMAND test_call_80011da0)
    add_executable(test_call_8006658c tests/test_call_8006658c.cpp)
    target_link_libraries(test_call_8006658c PRIVATE am3d_exe)
    add_test(NAME call_8006658c COMMAND test_call_8006658c)
    add_executable(test_call_800710cc tests/test_call_800710cc.cpp)
    target_link_libraries(test_call_800710cc PRIVATE am3d_exe)
    add_test(NAME call_800710cc COMMAND test_call_800710cc)
    add_executable(test_call_800710dc tests/test_call_800710dc.cpp)
    target_link_libraries(test_call_800710dc PRIVATE am3d_exe)
    add_test(NAME call_800710dc COMMAND test_call_800710dc)
    add_executable(test_call_800710ec tests/test_call_800710ec.cpp)
    target_link_libraries(test_call_800710ec PRIVATE am3d_exe)
    add_test(NAME call_800710ec COMMAND test_call_800710ec)
    add_executable(test_call_800710fc tests/test_call_800710fc.cpp)
    target_link_libraries(test_call_800710fc PRIVATE am3d_exe)
    add_test(NAME call_800710fc COMMAND test_call_800710fc)
    add_executable(test_call_8007110c tests/test_call_8007110c.cpp)
    target_link_libraries(test_call_8007110c PRIVATE am3d_exe)
    add_test(NAME call_8007110c COMMAND test_call_8007110c)
    add_executable(test_call_80071134 tests/test_call_80071134.cpp)
    target_link_libraries(test_call_80071134 PRIVATE am3d_exe)
    add_test(NAME call_80071134 COMMAND test_call_80071134)
    add_executable(test_call_8007115c tests/test_call_8007115c.cpp)
    target_link_libraries(test_call_8007115c PRIVATE am3d_exe)
    add_test(NAME call_8007115c COMMAND test_call_8007115c)
    add_executable(test_call_80071184 tests/test_call_80071184.cpp)
    target_link_libraries(test_call_80071184 PRIVATE am3d_exe)
    add_test(NAME call_80071184 COMMAND test_call_80071184)
    add_executable(test_call_80071fe4 tests/test_call_80071fe4.cpp)
    target_link_libraries(test_call_80071fe4 PRIVATE am3d_exe)
    add_test(NAME call_80071fe4 COMMAND test_call_80071fe4)
    add_executable(test_call_800793d4 tests/test_call_800793d4.cpp)
    target_link_libraries(test_call_800793d4 PRIVATE am3d_exe)
    add_test(NAME call_800793d4 COMMAND test_call_800793d4)
    add_executable(test_call_800124cc tests/test_call_800124cc.cpp)
    target_link_libraries(test_call_800124cc PRIVATE am3d_exe)
    add_test(NAME call_800124cc COMMAND test_call_800124cc)
    add_executable(test_call_8007b118 tests/test_call_8007b118.cpp)
    target_link_libraries(test_call_8007b118 PRIVATE am3d_exe)
    add_test(NAME call_8007b118 COMMAND test_call_8007b118)
    add_executable(test_call_8007b128 tests/test_call_8007b128.cpp)
    target_link_libraries(test_call_8007b128 PRIVATE am3d_exe)
    add_test(NAME call_8007b128 COMMAND test_call_8007b128)
    add_executable(test_call_8007c2a8 tests/test_call_8007c2a8.cpp)
    target_link_libraries(test_call_8007c2a8 PRIVATE am3d_exe)
    add_test(NAME call_8007c2a8 COMMAND test_call_8007c2a8)
    add_executable(test_call_8007c2b8 tests/test_call_8007c2b8.cpp)
    target_link_libraries(test_call_8007c2b8 PRIVATE am3d_exe)
    add_test(NAME call_8007c2b8 COMMAND test_call_8007c2b8)
    add_executable(test_call_8007c2c4 tests/test_call_8007c2c4.cpp)
    target_link_libraries(test_call_8007c2c4 PRIVATE am3d_exe)
    add_test(NAME call_8007c2c4 COMMAND test_call_8007c2c4)
    add_executable(test_call_8007ca78 tests/test_call_8007ca78.cpp)
    target_link_libraries(test_call_8007ca78 PRIVATE am3d_exe)
    add_test(NAME call_8007ca78 COMMAND test_call_8007ca78)
    add_executable(test_call_8007e198 tests/test_call_8007e198.cpp)
    target_link_libraries(test_call_8007e198 PRIVATE am3d_exe)
    add_test(NAME call_8007e198 COMMAND test_call_8007e198)
    add_executable(test_call_8007e1a8 tests/test_call_8007e1a8.cpp)
    target_link_libraries(test_call_8007e1a8 PRIVATE am3d_exe)
    add_test(NAME call_8007e1a8 COMMAND test_call_8007e1a8)
    add_executable(test_call_8007e2c4 tests/test_call_8007e2c4.cpp)
    target_link_libraries(test_call_8007e2c4 PRIVATE am3d_exe)
    add_test(NAME call_8007e2c4 COMMAND test_call_8007e2c4)
    add_executable(test_call_8007f040 tests/test_call_8007f040.cpp)
    target_link_libraries(test_call_8007f040 PRIVATE am3d_exe)
    add_test(NAME call_8007f040 COMMAND test_call_8007f040)
    add_executable(test_call_8007fbdc tests/test_call_8007fbdc.cpp)
    target_link_libraries(test_call_8007fbdc PRIVATE am3d_exe)
    add_test(NAME call_8007fbdc COMMAND test_call_8007fbdc)
    add_executable(test_call_800125ac tests/test_call_800125ac.cpp)
    target_link_libraries(test_call_800125ac PRIVATE am3d_exe)
    add_test(NAME call_800125ac COMMAND test_call_800125ac)
    add_executable(test_call_8007fc1c tests/test_call_8007fc1c.cpp)
    target_link_libraries(test_call_8007fc1c PRIVATE am3d_exe)
    add_test(NAME call_8007fc1c COMMAND test_call_8007fc1c)
    add_executable(test_call_8007fc3c tests/test_call_8007fc3c.cpp)
    target_link_libraries(test_call_8007fc3c PRIVATE am3d_exe)
    add_test(NAME call_8007fc3c COMMAND test_call_8007fc3c)
    add_executable(test_call_80084610 tests/test_call_80084610.cpp)
    target_link_libraries(test_call_80084610 PRIVATE am3d_exe)
    add_test(NAME call_80084610 COMMAND test_call_80084610)
    add_executable(test_call_8008498c tests/test_call_8008498c.cpp)
    target_link_libraries(test_call_8008498c PRIVATE am3d_exe)
    add_test(NAME call_8008498c COMMAND test_call_8008498c)
    add_executable(test_call_80085820 tests/test_call_80085820.cpp)
    target_link_libraries(test_call_80085820 PRIVATE am3d_exe)
    add_test(NAME call_80085820 COMMAND test_call_80085820)
    add_executable(test_call_800864c0 tests/test_call_800864c0.cpp)
    target_link_libraries(test_call_800864c0 PRIVATE am3d_exe)
    add_test(NAME call_800864c0 COMMAND test_call_800864c0)
    add_executable(test_call_8007fbec tests/test_call_8007fbec.cpp)
    target_link_libraries(test_call_8007fbec PRIVATE am3d_exe)
    add_test(NAME call_8007fbec COMMAND test_call_8007fbec)
    add_executable(test_call_80080c5c tests/test_call_80080c5c.cpp)
    target_link_libraries(test_call_80080c5c PRIVATE am3d_exe)
    add_test(NAME call_80080c5c COMMAND test_call_80080c5c)
    add_executable(test_call_800856ac tests/test_call_800856ac.cpp)
    target_link_libraries(test_call_800856ac PRIVATE am3d_exe)
    add_test(NAME call_800856ac COMMAND test_call_800856ac)
    add_executable(test_call_80085d94 tests/test_call_80085d94.cpp)
    target_link_libraries(test_call_80085d94 PRIVATE am3d_exe)
    add_test(NAME call_80085d94 COMMAND test_call_80085d94)
    add_executable(test_call_80085dac tests/test_call_80085dac.cpp)
    target_link_libraries(test_call_80085dac PRIVATE am3d_exe)
    add_test(NAME call_80085dac COMMAND test_call_80085dac)
    add_executable(test_call_80012a3c tests/test_call_80012a3c.cpp)
    target_link_libraries(test_call_80012a3c PRIVATE am3d_exe)
    add_test(NAME call_80012a3c COMMAND test_call_80012a3c)
    add_executable(test_call_8008918c tests/test_call_8008918c.cpp)
    target_link_libraries(test_call_8008918c PRIVATE am3d_exe)
    add_test(NAME call_8008918c COMMAND test_call_8008918c)
    add_executable(test_call_8008ac3c tests/test_call_8008ac3c.cpp)
    target_link_libraries(test_call_8008ac3c PRIVATE am3d_exe)
    add_test(NAME call_8008ac3c COMMAND test_call_8008ac3c)
    add_executable(test_call_8008ac5c tests/test_call_8008ac5c.cpp)
    target_link_libraries(test_call_8008ac5c PRIVATE am3d_exe)
    add_test(NAME call_8008ac5c COMMAND test_call_8008ac5c)
    add_executable(test_call_8008ef18 tests/test_call_8008ef18.cpp)
    target_link_libraries(test_call_8008ef18 PRIVATE am3d_exe)
    add_test(NAME call_8008ef18 COMMAND test_call_8008ef18)
    add_executable(test_call_8008f9dc tests/test_call_8008f9dc.cpp)
    target_link_libraries(test_call_8008f9dc PRIVATE am3d_exe)
    add_test(NAME call_8008f9dc COMMAND test_call_8008f9dc)
    add_executable(test_call_8008fad4 tests/test_call_8008fad4.cpp)
    target_link_libraries(test_call_8008fad4 PRIVATE am3d_exe)
    add_test(NAME call_8008fad4 COMMAND test_call_8008fad4)
    add_executable(test_call_80090318 tests/test_call_80090318.cpp)
    target_link_libraries(test_call_80090318 PRIVATE am3d_exe)
    add_test(NAME call_80090318 COMMAND test_call_80090318)
    add_executable(test_call_80095730 tests/test_call_80095730.cpp)
    target_link_libraries(test_call_80095730 PRIVATE am3d_exe)
    add_test(NAME call_80095730 COMMAND test_call_80095730)
    add_executable(test_call_800961c4 tests/test_call_800961c4.cpp)
    target_link_libraries(test_call_800961c4 PRIVATE am3d_exe)
    add_test(NAME call_800961c4 COMMAND test_call_800961c4)
    add_executable(test_call_80096d38 tests/test_call_80096d38.cpp)
    target_link_libraries(test_call_80096d38 PRIVATE am3d_exe)
    add_test(NAME call_80096d38 COMMAND test_call_80096d38)
    add_executable(test_call_80096dac tests/test_call_80096dac.cpp)
    target_link_libraries(test_call_80096dac PRIVATE am3d_exe)
    add_test(NAME call_80096dac COMMAND test_call_80096dac)
    add_executable(test_call_80010c7c tests/test_call_80010c7c.cpp)
    target_link_libraries(test_call_80010c7c PRIVATE am3d_exe)
    add_test(NAME call_80010c7c COMMAND test_call_80010c7c)
    add_executable(test_call_800793ec tests/test_call_800793ec.cpp)
    target_link_libraries(test_call_800793ec PRIVATE am3d_exe)
    add_test(NAME call_800793ec COMMAND test_call_800793ec)
    add_executable(test_call_80012e94 tests/test_call_80012e94.cpp)
    target_link_libraries(test_call_80012e94 PRIVATE am3d_exe)
    add_test(NAME call_80012e94 COMMAND test_call_80012e94)
    add_executable(test_call_80012f94 tests/test_call_80012f94.cpp)
    target_link_libraries(test_call_80012f94 PRIVATE am3d_exe)
    add_test(NAME call_80012f94 COMMAND test_call_80012f94)
    add_executable(test_call_800656ec tests/test_call_800656ec.cpp)
    target_link_libraries(test_call_800656ec PRIVATE am3d_exe)
    add_test(NAME call_800656ec COMMAND test_call_800656ec)
    add_executable(test_call_80076480 tests/test_call_80076480.cpp)
    target_link_libraries(test_call_80076480 PRIVATE am3d_exe)
    add_test(NAME call_80076480 COMMAND test_call_80076480)
    add_executable(test_call_80076490 tests/test_call_80076490.cpp)
    target_link_libraries(test_call_80076490 PRIVATE am3d_exe)
    add_test(NAME call_80076490 COMMAND test_call_80076490)
    add_executable(test_call_800764a0 tests/test_call_800764a0.cpp)
    target_link_libraries(test_call_800764a0 PRIVATE am3d_exe)
    add_test(NAME call_800764a0 COMMAND test_call_800764a0)
    add_executable(test_call_80085dbc tests/test_call_80085dbc.cpp)
    target_link_libraries(test_call_80085dbc PRIVATE am3d_exe)
    add_test(NAME call_80085dbc COMMAND test_call_80085dbc)
    add_executable(test_call_80085dcc tests/test_call_80085dcc.cpp)
    target_link_libraries(test_call_80085dcc PRIVATE am3d_exe)
    add_test(NAME call_80085dcc COMMAND test_call_80085dcc)
    add_executable(test_call_8008917c tests/test_call_8008917c.cpp)
    target_link_libraries(test_call_8008917c PRIVATE am3d_exe)
    add_test(NAME call_8008917c COMMAND test_call_8008917c)
    add_executable(test_call_8008c29c tests/test_call_8008c29c.cpp)
    target_link_libraries(test_call_8008c29c PRIVATE am3d_exe)
    add_test(NAME call_8008c29c COMMAND test_call_8008c29c)
    add_executable(test_call_80012fe8 tests/test_call_80012fe8.cpp)
    target_link_libraries(test_call_80012fe8 PRIVATE am3d_exe)
    add_test(NAME call_80012fe8 COMMAND test_call_80012fe8)
    add_executable(test_call_80076450 tests/test_call_80076450.cpp)
    target_link_libraries(test_call_80076450 PRIVATE am3d_exe)
    add_test(NAME call_80076450 COMMAND test_call_80076450)
    add_executable(test_call_80076468 tests/test_call_80076468.cpp)
    target_link_libraries(test_call_80076468 PRIVATE am3d_exe)
    add_test(NAME call_80076468 COMMAND test_call_80076468)
    add_executable(test_call_80096d18 tests/test_call_80096d18.cpp)
    target_link_libraries(test_call_80096d18 PRIVATE am3d_exe)
    add_test(NAME call_80096d18 COMMAND test_call_80096d18)
    add_executable(test_call_80096d4c tests/test_call_80096d4c.cpp)
    target_link_libraries(test_call_80096d4c PRIVATE am3d_exe)
    add_test(NAME call_80096d4c COMMAND test_call_80096d4c)
    add_executable(test_call_80096d6c tests/test_call_80096d6c.cpp)
    target_link_libraries(test_call_80096d6c PRIVATE am3d_exe)
    add_test(NAME call_80096d6c COMMAND test_call_80096d6c)
    add_executable(test_call_80096d8c tests/test_call_80096d8c.cpp)
    target_link_libraries(test_call_80096d8c PRIVATE am3d_exe)
    add_test(NAME call_80096d8c COMMAND test_call_80096d8c)
    add_executable(test_call_80013318 tests/test_call_80013318.cpp)
    target_link_libraries(test_call_80013318 PRIVATE am3d_exe)
    add_test(NAME call_80013318 COMMAND test_call_80013318)
    add_executable(test_call_800132dc tests/test_call_800132dc.cpp)
    target_link_libraries(test_call_800132dc PRIVATE am3d_exe)
    add_test(NAME call_800132dc COMMAND test_call_800132dc)
    add_executable(test_call_80014b7c tests/test_call_80014b7c.cpp)
    target_link_libraries(test_call_80014b7c PRIVATE am3d_exe)
    add_test(NAME call_80014b7c COMMAND test_call_80014b7c)
    add_executable(test_call_80015a50 tests/test_call_80015a50.cpp)
    target_link_libraries(test_call_80015a50 PRIVATE am3d_exe)
    add_test(NAME call_80015a50 COMMAND test_call_80015a50)
    add_executable(test_call_80015cfc tests/test_call_80015cfc.cpp)
    target_link_libraries(test_call_80015cfc PRIVATE am3d_exe)
    add_test(NAME call_80015cfc COMMAND test_call_80015cfc)
    add_executable(test_call_8003741c tests/test_call_8003741c.cpp)
    target_link_libraries(test_call_8003741c PRIVATE am3d_exe)
    add_test(NAME call_8003741c COMMAND test_call_8003741c)
    add_executable(test_call_80022dc0 tests/test_call_80022dc0.cpp)
    target_link_libraries(test_call_80022dc0 PRIVATE am3d_exe)
    add_test(NAME call_80022dc0 COMMAND test_call_80022dc0)
    add_executable(test_call_8002134c tests/test_call_8002134c.cpp)
    target_link_libraries(test_call_8002134c PRIVATE am3d_exe)
    add_test(NAME call_8002134c COMMAND test_call_8002134c)
    add_executable(test_call_80017484 tests/test_call_80017484.cpp)
    target_link_libraries(test_call_80017484 PRIVATE am3d_exe)
    add_test(NAME call_80017484 COMMAND test_call_80017484)
    add_executable(test_call_80036258 tests/test_call_80036258.cpp)
    target_link_libraries(test_call_80036258 PRIVATE am3d_exe)
    add_test(NAME call_80036258 COMMAND test_call_80036258)
    add_executable(test_call_80036278 tests/test_call_80036278.cpp)
    target_link_libraries(test_call_80036278 PRIVATE am3d_exe)
    add_test(NAME call_80036278 COMMAND test_call_80036278)
    add_executable(test_call_800265a4 tests/test_call_800265a4.cpp)
    target_link_libraries(test_call_800265a4 PRIVATE am3d_exe)
    add_test(NAME call_800265a4 COMMAND test_call_800265a4)
    add_executable(test_call_800268e4 tests/test_call_800268e4.cpp)
    target_link_libraries(test_call_800268e4 PRIVATE am3d_exe)
    add_test(NAME call_800268e4 COMMAND test_call_800268e4)
    add_executable(test_call_800278b8 tests/test_call_800278b8.cpp)
    target_link_libraries(test_call_800278b8 PRIVATE am3d_exe)
    add_test(NAME call_800278b8 COMMAND test_call_800278b8)
    add_executable(test_call_800329d0 tests/test_call_800329d0.cpp)
    target_link_libraries(test_call_800329d0 PRIVATE am3d_exe)
    add_test(NAME call_800329d0 COMMAND test_call_800329d0)
    add_executable(test_call_80036774 tests/test_call_80036774.cpp)
    target_link_libraries(test_call_80036774 PRIVATE am3d_exe)
    add_test(NAME call_80036774 COMMAND test_call_80036774)
    add_executable(test_call_800367ac tests/test_call_800367ac.cpp)
    target_link_libraries(test_call_800367ac PRIVATE am3d_exe)
    add_test(NAME call_800367ac COMMAND test_call_800367ac)
    add_executable(test_call_80018b64 tests/test_call_80018b64.cpp)
    target_link_libraries(test_call_80018b64 PRIVATE am3d_exe)
    add_test(NAME call_80018b64 COMMAND test_call_80018b64)
    add_executable(test_call_80057714 tests/test_call_80057714.cpp)
    target_link_libraries(test_call_80057714 PRIVATE am3d_exe)
    add_test(NAME call_80057714 COMMAND test_call_80057714)
    add_executable(test_call_8005775c tests/test_call_8005775c.cpp)
    target_link_libraries(test_call_8005775c PRIVATE am3d_exe)
    add_test(NAME call_8005775c COMMAND test_call_8005775c)
    add_executable(test_call_800265b8 tests/test_call_800265b8.cpp)
    target_link_libraries(test_call_800265b8 PRIVATE am3d_exe)
    add_test(NAME call_800265b8 COMMAND test_call_800265b8)
    add_executable(test_call_8003c514 tests/test_call_8003c514.cpp)
    target_link_libraries(test_call_8003c514 PRIVATE am3d_exe)
    add_test(NAME call_8003c514 COMMAND test_call_8003c514)
    add_executable(test_call_8003b774 tests/test_call_8003b774.cpp)
    target_link_libraries(test_call_8003b774 PRIVATE am3d_exe)
    add_test(NAME call_8003b774 COMMAND test_call_8003b774)
    add_executable(test_call_80038728 tests/test_call_80038728.cpp)
    target_link_libraries(test_call_80038728 PRIVATE am3d_exe)
    add_test(NAME call_80038728 COMMAND test_call_80038728)
    add_executable(test_call_80038798 tests/test_call_80038798.cpp)
    target_link_libraries(test_call_80038798 PRIVATE am3d_exe)
    add_test(NAME call_80038798 COMMAND test_call_80038798)
    add_executable(test_call_80038808 tests/test_call_80038808.cpp)
    target_link_libraries(test_call_80038808 PRIVATE am3d_exe)
    add_test(NAME call_80038808 COMMAND test_call_80038808)
    add_executable(test_call_800450d4 tests/test_call_800450d4.cpp)
    target_link_libraries(test_call_800450d4 PRIVATE am3d_exe)
    add_test(NAME call_800450d4 COMMAND test_call_800450d4)
    add_executable(test_call_8003ff08 tests/test_call_8003ff08.cpp)
    target_link_libraries(test_call_8003ff08 PRIVATE am3d_exe)
    add_test(NAME call_8003ff08 COMMAND test_call_8003ff08)
    add_executable(test_call_80042ae4 tests/test_call_80042ae4.cpp)
    target_link_libraries(test_call_80042ae4 PRIVATE am3d_exe)
    add_test(NAME call_80042ae4 COMMAND test_call_80042ae4)
    add_executable(test_call_80044f94 tests/test_call_80044f94.cpp)
    target_link_libraries(test_call_80044f94 PRIVATE am3d_exe)
    add_test(NAME call_80044f94 COMMAND test_call_80044f94)
    add_executable(test_call_8003d874 tests/test_call_8003d874.cpp)
    target_link_libraries(test_call_8003d874 PRIVATE am3d_exe)
    add_test(NAME call_8003d874 COMMAND test_call_8003d874)
    add_executable(test_call_80049330 tests/test_call_80049330.cpp)
    target_link_libraries(test_call_80049330 PRIVATE am3d_exe)
    add_test(NAME call_80049330 COMMAND test_call_80049330)
    add_executable(test_call_8005eeb4 tests/test_call_8005eeb4.cpp)
    target_link_libraries(test_call_8005eeb4 PRIVATE am3d_exe)
    add_test(NAME call_8005eeb4 COMMAND test_call_8005eeb4)
    add_executable(test_call_8004c4e8 tests/test_call_8004c4e8.cpp)
    target_link_libraries(test_call_8004c4e8 PRIVATE am3d_exe)
    add_test(NAME call_8004c4e8 COMMAND test_call_8004c4e8)
    add_executable(test_call_8005e5a0 tests/test_call_8005e5a0.cpp)
    target_link_libraries(test_call_8005e5a0 PRIVATE am3d_exe)
    add_test(NAME call_8005e5a0 COMMAND test_call_8005e5a0)
    add_executable(test_call_8005e5c0 tests/test_call_8005e5c0.cpp)
    target_link_libraries(test_call_8005e5c0 PRIVATE am3d_exe)
    add_test(NAME call_8005e5c0 COMMAND test_call_8005e5c0)
    add_executable(test_call_800608dc tests/test_call_800608dc.cpp)
    target_link_libraries(test_call_800608dc PRIVATE am3d_exe)
    add_test(NAME call_800608dc COMMAND test_call_800608dc)
    add_executable(test_call_80076b78 tests/test_call_80076b78.cpp)
    target_link_libraries(test_call_80076b78 PRIVATE am3d_exe)
    add_test(NAME call_80076b78 COMMAND test_call_80076b78)
    add_executable(test_call_80076ba0 tests/test_call_80076ba0.cpp)
    target_link_libraries(test_call_80076ba0 PRIVATE am3d_exe)
    add_test(NAME call_80076ba0 COMMAND test_call_80076ba0)
    add_executable(test_call_80077038 tests/test_call_80077038.cpp)
    target_link_libraries(test_call_80077038 PRIVATE am3d_exe)
    add_test(NAME call_80077038 COMMAND test_call_80077038)
    add_executable(test_call_80078260 tests/test_call_80078260.cpp)
    target_link_libraries(test_call_80078260 PRIVATE am3d_exe)
    add_test(NAME call_80078260 COMMAND test_call_80078260)
    add_executable(test_call_80075bc8 tests/test_call_80075bc8.cpp)
    target_link_libraries(test_call_80075bc8 PRIVATE am3d_exe)
    add_test(NAME call_80075bc8 COMMAND test_call_80075bc8)
    add_executable(test_call_80076e98 tests/test_call_80076e98.cpp)
    target_link_libraries(test_call_80076e98 PRIVATE am3d_exe)
    add_test(NAME call_80076e98 COMMAND test_call_80076e98)
    add_executable(test_call_8007ec74 tests/test_call_8007ec74.cpp)
    target_link_libraries(test_call_8007ec74 PRIVATE am3d_exe)
    add_test(NAME call_8007ec74 COMMAND test_call_8007ec74)
    add_executable(test_call_8004dbdc tests/test_call_8004dbdc.cpp)
    target_link_libraries(test_call_8004dbdc PRIVATE am3d_exe)
    add_test(NAME call_8004dbdc COMMAND test_call_8004dbdc)
    add_executable(test_call_8004dee8 tests/test_call_8004dee8.cpp)
    target_link_libraries(test_call_8004dee8 PRIVATE am3d_exe)
    add_test(NAME call_8004dee8 COMMAND test_call_8004dee8)
    add_executable(test_call_8007941c tests/test_call_8007941c.cpp)
    target_link_libraries(test_call_8007941c PRIVATE am3d_exe)
    add_test(NAME call_8007941c COMMAND test_call_8007941c)
    add_executable(test_call_8007b150 tests/test_call_8007b150.cpp)
    target_link_libraries(test_call_8007b150 PRIVATE am3d_exe)
    add_test(NAME call_8007b150 COMMAND test_call_8007b150)
    add_executable(test_call_8007b170 tests/test_call_8007b170.cpp)
    target_link_libraries(test_call_8007b170 PRIVATE am3d_exe)
    add_test(NAME call_8007b170 COMMAND test_call_8007b170)
    add_executable(test_call_80081e44 tests/test_call_80081e44.cpp)
    target_link_libraries(test_call_80081e44 PRIVATE am3d_exe)
    add_test(NAME call_80081e44 COMMAND test_call_80081e44)
    add_executable(test_call_80081e64 tests/test_call_80081e64.cpp)
    target_link_libraries(test_call_80081e64 PRIVATE am3d_exe)
    add_test(NAME call_80081e64 COMMAND test_call_80081e64)
    add_executable(test_call_80081ea8 tests/test_call_80081ea8.cpp)
    target_link_libraries(test_call_80081ea8 PRIVATE am3d_exe)
    add_test(NAME call_80081ea8 COMMAND test_call_80081ea8)
    add_executable(test_call_80084260 tests/test_call_80084260.cpp)
    target_link_libraries(test_call_80084260 PRIVATE am3d_exe)
    add_test(NAME call_80084260 COMMAND test_call_80084260)
    add_executable(test_call_8004974c tests/test_call_8004974c.cpp)
    target_link_libraries(test_call_8004974c PRIVATE am3d_exe)
    add_test(NAME call_8004974c COMMAND test_call_8004974c)
    add_executable(test_call_8004dbfc tests/test_call_8004dbfc.cpp)
    target_link_libraries(test_call_8004dbfc PRIVATE am3d_exe)
    add_test(NAME call_8004dbfc COMMAND test_call_8004dbfc)
    add_executable(test_call_80079e1c tests/test_call_80079e1c.cpp)
    target_link_libraries(test_call_80079e1c PRIVATE am3d_exe)
    add_test(NAME call_80079e1c COMMAND test_call_80079e1c)
    add_executable(test_call_8007f3c8 tests/test_call_8007f3c8.cpp)
    target_link_libraries(test_call_8007f3c8 PRIVATE am3d_exe)
    add_test(NAME call_8007f3c8 COMMAND test_call_8007f3c8)
    add_executable(test_call_80083374 tests/test_call_80083374.cpp)
    target_link_libraries(test_call_80083374 PRIVATE am3d_exe)
    add_test(NAME call_80083374 COMMAND test_call_80083374)
    add_executable(test_call_800834dc tests/test_call_800834dc.cpp)
    target_link_libraries(test_call_800834dc PRIVATE am3d_exe)
    add_test(NAME call_800834dc COMMAND test_call_800834dc)
    add_executable(test_call_800835dc tests/test_call_800835dc.cpp)
    target_link_libraries(test_call_800835dc PRIVATE am3d_exe)
    add_test(NAME call_800835dc COMMAND test_call_800835dc)
    add_executable(test_call_800849ac tests/test_call_800849ac.cpp)
    target_link_libraries(test_call_800849ac PRIVATE am3d_exe)
    add_test(NAME call_800849ac COMMAND test_call_800849ac)
    add_executable(test_call_8008dabc tests/test_call_8008dabc.cpp)
    target_link_libraries(test_call_8008dabc PRIVATE am3d_exe)
    add_test(NAME call_8008dabc COMMAND test_call_8008dabc)
    add_executable(test_call_8008f6cc tests/test_call_8008f6cc.cpp)
    target_link_libraries(test_call_8008f6cc PRIVATE am3d_exe)
    add_test(NAME call_8008f6cc COMMAND test_call_8008f6cc)
    add_executable(test_call_8008f6dc tests/test_call_8008f6dc.cpp)
    target_link_libraries(test_call_8008f6dc PRIVATE am3d_exe)
    add_test(NAME call_8008f6dc COMMAND test_call_8008f6dc)
    add_executable(test_call_8008f6ec tests/test_call_8008f6ec.cpp)
    target_link_libraries(test_call_8008f6ec PRIVATE am3d_exe)
    add_test(NAME call_8008f6ec COMMAND test_call_8008f6ec)
    add_executable(test_call_8004ff84 tests/test_call_8004ff84.cpp)
    target_link_libraries(test_call_8004ff84 PRIVATE am3d_exe)
    add_test(NAME call_8004ff84 COMMAND test_call_8004ff84)
    add_executable(test_call_80066b7c tests/test_call_80066b7c.cpp)
    target_link_libraries(test_call_80066b7c PRIVATE am3d_exe)
    add_test(NAME call_80066b7c COMMAND test_call_80066b7c)
    add_executable(test_call_8007c17c tests/test_call_8007c17c.cpp)
    target_link_libraries(test_call_8007c17c PRIVATE am3d_exe)
    add_test(NAME call_8007c17c COMMAND test_call_8007c17c)
    add_executable(test_call_8007c1a8 tests/test_call_8007c1a8.cpp)
    target_link_libraries(test_call_8007c1a8 PRIVATE am3d_exe)
    add_test(NAME call_8007c1a8 COMMAND test_call_8007c1a8)
    add_executable(test_call_8007c1c8 tests/test_call_8007c1c8.cpp)
    target_link_libraries(test_call_8007c1c8 PRIVATE am3d_exe)
    add_test(NAME call_8007c1c8 COMMAND test_call_8007c1c8)
    add_executable(test_call_8007cf60 tests/test_call_8007cf60.cpp)
    target_link_libraries(test_call_8007cf60 PRIVATE am3d_exe)
    add_test(NAME call_8007cf60 COMMAND test_call_8007cf60)
    add_executable(test_call_8008f6fc tests/test_call_8008f6fc.cpp)
    target_link_libraries(test_call_8008f6fc PRIVATE am3d_exe)
    add_test(NAME call_8008f6fc COMMAND test_call_8008f6fc)
    add_executable(test_call_8008f70c tests/test_call_8008f70c.cpp)
    target_link_libraries(test_call_8008f70c PRIVATE am3d_exe)
    add_test(NAME call_8008f70c COMMAND test_call_8008f70c)
    add_executable(test_call_8008f71c tests/test_call_8008f71c.cpp)
    target_link_libraries(test_call_8008f71c PRIVATE am3d_exe)
    add_test(NAME call_8008f71c COMMAND test_call_8008f71c)
    add_executable(test_call_8008f9cc tests/test_call_8008f9cc.cpp)
    target_link_libraries(test_call_8008f9cc PRIVATE am3d_exe)
    add_test(NAME call_8008f9cc COMMAND test_call_8008f9cc)
    add_executable(test_call_80075370 tests/test_call_80075370.cpp)
    target_link_libraries(test_call_80075370 PRIVATE am3d_exe)
    add_test(NAME call_80075370 COMMAND test_call_80075370)
    add_executable(test_call_800753bc tests/test_call_800753bc.cpp)
    target_link_libraries(test_call_800753bc PRIVATE am3d_exe)
    add_test(NAME call_800753bc COMMAND test_call_800753bc)
    add_executable(test_call_80074360 tests/test_call_80074360.cpp)
    target_link_libraries(test_call_80074360 PRIVATE am3d_exe)
    add_test(NAME call_80074360 COMMAND test_call_80074360)
    add_executable(test_call_8005be28 tests/test_call_8005be28.cpp)
    target_link_libraries(test_call_8005be28 PRIVATE am3d_exe)
    add_test(NAME call_8005be28 COMMAND test_call_8005be28)
    add_executable(test_call_8005be50 tests/test_call_8005be50.cpp)
    target_link_libraries(test_call_8005be50 PRIVATE am3d_exe)
    add_test(NAME call_8005be50 COMMAND test_call_8005be50)
    add_executable(test_call_8005be3c tests/test_call_8005be3c.cpp)
    target_link_libraries(test_call_8005be3c PRIVATE am3d_exe)
    add_test(NAME call_8005be3c COMMAND test_call_8005be3c)
    add_executable(test_call_8005be9c tests/test_call_8005be9c.cpp)
    target_link_libraries(test_call_8005be9c PRIVATE am3d_exe)
    add_test(NAME call_8005be9c COMMAND test_call_8005be9c)
    add_executable(test_call_80075318 tests/test_call_80075318.cpp)
    target_link_libraries(test_call_80075318 PRIVATE am3d_exe)
    add_test(NAME call_80075318 COMMAND test_call_80075318)
    add_executable(test_call_8007533c tests/test_call_8007533c.cpp)
    target_link_libraries(test_call_8007533c PRIVATE am3d_exe)
    add_test(NAME call_8007533c COMMAND test_call_8007533c)
    add_executable(test_call_80075404 tests/test_call_80075404.cpp)
    target_link_libraries(test_call_80075404 PRIVATE am3d_exe)
    add_test(NAME call_80075404 COMMAND test_call_80075404)
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

    add_executable(test_call_80023264 tests/test_call_80023264.cpp)
    target_link_libraries(test_call_80023264 PRIVATE am3d_exe)
    add_test(NAME call_80023264 COMMAND test_call_80023264)

    add_executable(test_call_8007f920_11 tests/test_call_8007f920_11.cpp)
    target_link_libraries(test_call_8007f920_11 PRIVATE am3d_exe)
    add_test(NAME call_8007f920_11 COMMAND test_call_8007f920_11)

    add_executable(test_call_80023274 tests/test_call_80023274.cpp)
    target_link_libraries(test_call_80023274 PRIVATE am3d_exe)
    add_test(NAME call_80023274 COMMAND test_call_80023274)

    add_executable(test_call_80063ed8_11 tests/test_call_80063ed8_11.cpp)
    target_link_libraries(test_call_80063ed8_11 PRIVATE am3d_exe)
    add_test(NAME call_80063ed8_11 COMMAND test_call_80063ed8_11)

    add_executable(test_call_80076508_11 tests/test_call_80076508_11.cpp)
    target_link_libraries(test_call_80076508_11 PRIVATE am3d_exe)
    add_test(NAME call_80076508_11 COMMAND test_call_80076508_11)

    add_executable(test_call_80063f18_11 tests/test_call_80063f18_11.cpp)
    target_link_libraries(test_call_80063f18_11 PRIVATE am3d_exe)
    add_test(NAME call_80063f18_11 COMMAND test_call_80063f18_11)

    add_executable(test_call_80023288 tests/test_call_80023288.cpp)
    target_link_libraries(test_call_80023288 PRIVATE am3d_exe)
    add_test(NAME call_80023288 COMMAND test_call_80023288)

    add_executable(test_call_800235a4 tests/test_call_800235a4.cpp)
    target_link_libraries(test_call_800235a4 PRIVATE am3d_exe)
    add_test(NAME call_800235a4 COMMAND test_call_800235a4)

    add_executable(test_call_800235b0 tests/test_call_800235b0.cpp)
    target_link_libraries(test_call_800235b0 PRIVATE am3d_exe)
    add_test(NAME call_800235b0 COMMAND test_call_800235b0)

    add_executable(test_call_80063ed4 tests/test_call_80063ed4.cpp)
    target_link_libraries(test_call_80063ed4 PRIVATE am3d_exe)
    add_test(NAME call_80063ed4 COMMAND test_call_80063ed4)

    add_executable(test_call_80063ed8_12 tests/test_call_80063ed8_12.cpp)
    target_link_libraries(test_call_80063ed8_12 PRIVATE am3d_exe)
    add_test(NAME call_80063ed8_12 COMMAND test_call_80063ed8_12)
    add_executable(test_call_80076508_12 tests/test_call_80076508_12.cpp)
    target_link_libraries(test_call_80076508_12 PRIVATE am3d_exe)
    add_test(NAME call_80076508_12 COMMAND test_call_80076508_12)
    add_executable(test_call_80063f18_12 tests/test_call_80063f18_12.cpp)
    target_link_libraries(test_call_80063f18_12 PRIVATE am3d_exe)
    add_test(NAME call_80063f18_12 COMMAND test_call_80063f18_12)
    add_executable(test_call_800235bc tests/test_call_800235bc.cpp)
    target_link_libraries(test_call_800235bc PRIVATE am3d_exe)
    add_test(NAME call_800235bc COMMAND test_call_800235bc)
    add_executable(test_call_800235a4_2 tests/test_call_800235a4_2.cpp)
    target_link_libraries(test_call_800235a4_2 PRIVATE am3d_exe)
    add_test(NAME call_800235a4_2 COMMAND test_call_800235a4_2)
    add_executable(test_call_800235b0_2 tests/test_call_800235b0_2.cpp)
    target_link_libraries(test_call_800235b0_2 PRIVATE am3d_exe)
    add_test(NAME call_800235b0_2 COMMAND test_call_800235b0_2)
    add_executable(test_call_80063ed8_13 tests/test_call_80063ed8_13.cpp)
    target_link_libraries(test_call_80063ed8_13 PRIVATE am3d_exe)
    add_test(NAME call_80063ed8_13 COMMAND test_call_80063ed8_13)
    add_executable(test_call_80076508_13 tests/test_call_80076508_13.cpp)
    target_link_libraries(test_call_80076508_13 PRIVATE am3d_exe)
    add_test(NAME call_80076508_13 COMMAND test_call_80076508_13)
    add_executable(test_call_80063f18_13 tests/test_call_80063f18_13.cpp)
    target_link_libraries(test_call_80063f18_13 PRIVATE am3d_exe)
    add_test(NAME call_80063f18_13 COMMAND test_call_80063f18_13)
    add_executable(test_call_800235ec tests/test_call_800235ec.cpp)
    target_link_libraries(test_call_800235ec PRIVATE am3d_exe)
    add_test(NAME call_800235ec COMMAND test_call_800235ec)
    add_executable(test_call_80023674 tests/test_call_80023674.cpp)
    target_link_libraries(test_call_80023674 PRIVATE am3d_exe)
    add_test(NAME call_80023674 COMMAND test_call_80023674)
    add_executable(test_call_80023914 tests/test_call_80023914.cpp)
    target_link_libraries(test_call_80023914 PRIVATE am3d_exe)
    add_test(NAME call_80023914 COMMAND test_call_80023914)
    add_executable(test_call_800255d8 tests/test_call_800255d8.cpp)
    target_link_libraries(test_call_800255d8 PRIVATE am3d_exe)
    add_test(NAME call_800255d8 COMMAND test_call_800255d8)
    add_executable(test_call_80045374 tests/test_call_80045374.cpp)
    target_link_libraries(test_call_80045374 PRIVATE am3d_exe)
    add_test(NAME call_80045374 COMMAND test_call_80045374)
    add_executable(test_call_8007d234 tests/test_call_8007d234.cpp)
    target_link_libraries(test_call_8007d234 PRIVATE am3d_exe)
    add_test(NAME call_8007d234 COMMAND test_call_8007d234)
    add_executable(test_call_800453a8 tests/test_call_800453a8.cpp)
    target_link_libraries(test_call_800453a8 PRIVATE am3d_exe)
    add_test(NAME call_800453a8 COMMAND test_call_800453a8)
    add_executable(test_call_80062434_5 tests/test_call_80062434_5.cpp)
    target_link_libraries(test_call_80062434_5 PRIVATE am3d_exe)
    add_test(NAME call_80062434_5 COMMAND test_call_80062434_5)
    add_executable(test_call_80061f80_5 tests/test_call_80061f80_5.cpp)
    target_link_libraries(test_call_80061f80_5 PRIVATE am3d_exe)
    add_test(NAME call_80061f80_5 COMMAND test_call_80061f80_5)
    add_executable(test_call_80062474_4 tests/test_call_80062474_4.cpp)
    target_link_libraries(test_call_80062474_4 PRIVATE am3d_exe)
    add_test(NAME call_80062474_4 COMMAND test_call_80062474_4)
    add_executable(test_call_80075198_11 tests/test_call_80075198_11.cpp)
    target_link_libraries(test_call_80075198_11 PRIVATE am3d_exe)
    add_test(NAME call_80075198_11 COMMAND test_call_80075198_11)
    add_executable(test_call_800624cc_4 tests/test_call_800624cc_4.cpp)
    target_link_libraries(test_call_800624cc_4 PRIVATE am3d_exe)
    add_test(NAME call_800624cc_4 COMMAND test_call_800624cc_4)
    add_executable(test_call_80045418 tests/test_call_80045418.cpp)
    target_link_libraries(test_call_80045418 PRIVATE am3d_exe)
    add_test(NAME call_80045418 COMMAND test_call_80045418)
    add_executable(test_call_8007e290 tests/test_call_8007e290.cpp)
    target_link_libraries(test_call_8007e290 PRIVATE am3d_exe)
    add_test(NAME call_8007e290 COMMAND test_call_8007e290)
    add_executable(test_call_80045524 tests/test_call_80045524.cpp)
    target_link_libraries(test_call_80045524 PRIVATE am3d_exe)
    add_test(NAME call_80045524 COMMAND test_call_80045524)
    add_executable(test_call_8007e248 tests/test_call_8007e248.cpp)
    target_link_libraries(test_call_8007e248 PRIVATE am3d_exe)
    add_test(NAME call_8007e248 COMMAND test_call_8007e248)
    add_executable(test_call_8007e280 tests/test_call_8007e280.cpp)
    target_link_libraries(test_call_8007e280 PRIVATE am3d_exe)
    add_test(NAME call_8007e280 COMMAND test_call_8007e280)
    add_executable(test_call_8004552c tests/test_call_8004552c.cpp)
    target_link_libraries(test_call_8004552c PRIVATE am3d_exe)
    add_test(NAME call_8004552c COMMAND test_call_8004552c)
    add_executable(test_call_8007eac8 tests/test_call_8007eac8.cpp)
    target_link_libraries(test_call_8007eac8 PRIVATE am3d_exe)
    add_test(NAME call_8007eac8 COMMAND test_call_8007eac8)
    add_executable(test_call_8007f920_12 tests/test_call_8007f920_12.cpp)
    target_link_libraries(test_call_8007f920_12 PRIVATE am3d_exe)
    add_test(NAME call_8007f920_12 COMMAND test_call_8007f920_12)
    add_executable(test_call_8007eafc tests/test_call_8007eafc.cpp)
    target_link_libraries(test_call_8007eafc PRIVATE am3d_exe)
    add_test(NAME call_8007eafc COMMAND test_call_8007eafc)
    add_executable(test_call_8007f920_13 tests/test_call_8007f920_13.cpp)
    target_link_libraries(test_call_8007f920_13 PRIVATE am3d_exe)
    add_test(NAME call_8007f920_13 COMMAND test_call_8007f920_13)
    add_executable(test_call_8007f920_14 tests/test_call_8007f920_14.cpp)
    target_link_libraries(test_call_8007f920_14 PRIVATE am3d_exe)
    add_test(NAME call_8007f920_14 COMMAND test_call_8007f920_14)
    add_executable(test_call_8007eb10 tests/test_call_8007eb10.cpp)
    target_link_libraries(test_call_8007eb10 PRIVATE am3d_exe)
    add_test(NAME call_8007eb10 COMMAND test_call_8007eb10)
    add_executable(test_call_80045540 tests/test_call_80045540.cpp)
    target_link_libraries(test_call_80045540 PRIVATE am3d_exe)
    add_test(NAME call_80045540 COMMAND test_call_80045540)
    add_executable(test_call_80045aa8 tests/test_call_80045aa8.cpp)
    target_link_libraries(test_call_80045aa8 PRIVATE am3d_exe)
    add_test(NAME call_80045aa8 COMMAND test_call_80045aa8)
    add_executable(test_call_80045548 tests/test_call_80045548.cpp)
    target_link_libraries(test_call_80045548 PRIVATE am3d_exe)
    add_test(NAME call_80045548 COMMAND test_call_80045548)
    add_executable(test_call_800452ac tests/test_call_800452ac.cpp)
    target_link_libraries(test_call_800452ac PRIVATE am3d_exe)
    add_test(NAME call_800452ac COMMAND test_call_800452ac)
    add_executable(test_call_80045570 tests/test_call_80045570.cpp)
    target_link_libraries(test_call_80045570 PRIVATE am3d_exe)
    add_test(NAME call_80045570 COMMAND test_call_80045570)
    add_executable(test_call_800255e4 tests/test_call_800255e4.cpp)
    target_link_libraries(test_call_800255e4 PRIVATE am3d_exe)
    add_test(NAME call_800255e4 COMMAND test_call_800255e4)
    add_executable(test_call_80065894 tests/test_call_80065894.cpp)
    target_link_libraries(test_call_80065894 PRIVATE am3d_exe)
    add_test(NAME call_80065894 COMMAND test_call_80065894)
    add_executable(test_call_80063ed8_14 tests/test_call_80063ed8_14.cpp)
    target_link_libraries(test_call_80063ed8_14 PRIVATE am3d_exe)
    add_test(NAME call_80063ed8_14 COMMAND test_call_80063ed8_14)
    add_executable(test_call_80076508_14 tests/test_call_80076508_14.cpp)
    target_link_libraries(test_call_80076508_14 PRIVATE am3d_exe)
    add_test(NAME call_80076508_14 COMMAND test_call_80076508_14)
    add_executable(test_call_80063f18_14 tests/test_call_80063f18_14.cpp)
    target_link_libraries(test_call_80063f18_14 PRIVATE am3d_exe)
    add_test(NAME call_80063f18_14 COMMAND test_call_80063f18_14)
    add_executable(test_call_800658bc tests/test_call_800658bc.cpp)
    target_link_libraries(test_call_800658bc PRIVATE am3d_exe)
    add_test(NAME call_800658bc COMMAND test_call_800658bc)
    add_executable(test_call_80063ed8_15 tests/test_call_80063ed8_15.cpp)
    target_link_libraries(test_call_80063ed8_15 PRIVATE am3d_exe)
    add_test(NAME call_80063ed8_15 COMMAND test_call_80063ed8_15)
    add_executable(test_call_80076508_15 tests/test_call_80076508_15.cpp)
    target_link_libraries(test_call_80076508_15 PRIVATE am3d_exe)
    add_test(NAME call_80076508_15 COMMAND test_call_80076508_15)
    add_executable(test_call_80063f18_15 tests/test_call_80063f18_15.cpp)
    target_link_libraries(test_call_80063f18_15 PRIVATE am3d_exe)
    add_test(NAME call_80063f18_15 COMMAND test_call_80063f18_15)
    add_executable(test_call_800658ec tests/test_call_800658ec.cpp)
    target_link_libraries(test_call_800658ec PRIVATE am3d_exe)
    add_test(NAME call_800658ec COMMAND test_call_800658ec)
    add_executable(test_call_80063ed8_16 tests/test_call_80063ed8_16.cpp)
    target_link_libraries(test_call_80063ed8_16 PRIVATE am3d_exe)
    add_test(NAME call_80063ed8_16 COMMAND test_call_80063ed8_16)
    add_executable(test_call_80076508_16 tests/test_call_80076508_16.cpp)
    target_link_libraries(test_call_80076508_16 PRIVATE am3d_exe)
    add_test(NAME call_80076508_16 COMMAND test_call_80076508_16)
    add_executable(test_call_80063f18_16 tests/test_call_80063f18_16.cpp)
    target_link_libraries(test_call_80063f18_16 PRIVATE am3d_exe)
    add_test(NAME call_80063f18_16 COMMAND test_call_80063f18_16)
    add_executable(test_call_80065904 tests/test_call_80065904.cpp)
    target_link_libraries(test_call_80065904 PRIVATE am3d_exe)
    add_test(NAME call_80065904 COMMAND test_call_80065904)
    add_executable(test_call_80063ed8_17 tests/test_call_80063ed8_17.cpp)
    target_link_libraries(test_call_80063ed8_17 PRIVATE am3d_exe)
    add_test(NAME call_80063ed8_17 COMMAND test_call_80063ed8_17)
    add_executable(test_call_80076508_17 tests/test_call_80076508_17.cpp)
    target_link_libraries(test_call_80076508_17 PRIVATE am3d_exe)
    add_test(NAME call_80076508_17 COMMAND test_call_80076508_17)
    add_executable(test_call_80063f18_17 tests/test_call_80063f18_17.cpp)
    target_link_libraries(test_call_80063f18_17 PRIVATE am3d_exe)
    add_test(NAME call_80063f18_17 COMMAND test_call_80063f18_17)
    add_executable(test_call_8006591c tests/test_call_8006591c.cpp)
    target_link_libraries(test_call_8006591c PRIVATE am3d_exe)
    add_test(NAME call_8006591c COMMAND test_call_8006591c)
    add_executable(test_call_80063ed8_18 tests/test_call_80063ed8_18.cpp)
    target_link_libraries(test_call_80063ed8_18 PRIVATE am3d_exe)
    add_test(NAME call_80063ed8_18 COMMAND test_call_80063ed8_18)
    add_executable(test_call_80076508_18 tests/test_call_80076508_18.cpp)
    target_link_libraries(test_call_80076508_18 PRIVATE am3d_exe)
    add_test(NAME call_80076508_18 COMMAND test_call_80076508_18)
    add_executable(test_call_80063f18_18 tests/test_call_80063f18_18.cpp)
    target_link_libraries(test_call_80063f18_18 PRIVATE am3d_exe)
    add_test(NAME call_80063f18_18 COMMAND test_call_80063f18_18)
    add_executable(test_call_80065954 tests/test_call_80065954.cpp)
    target_link_libraries(test_call_80065954 PRIVATE am3d_exe)
    add_test(NAME call_80065954 COMMAND test_call_80065954)
    add_executable(test_call_8005b6dc tests/test_call_8005b6dc.cpp)
    target_link_libraries(test_call_8005b6dc PRIVATE am3d_exe)
    add_test(NAME call_8005b6dc COMMAND test_call_8005b6dc)
    add_executable(test_call_8006596c tests/test_call_8006596c.cpp)
    target_link_libraries(test_call_8006596c PRIVATE am3d_exe)
    add_test(NAME call_8006596c COMMAND test_call_8006596c)
    add_executable(test_call_80062e0c tests/test_call_80062e0c.cpp)
    target_link_libraries(test_call_80062e0c PRIVATE am3d_exe)
    add_test(NAME call_80062e0c COMMAND test_call_80062e0c)
    add_executable(test_call_80062434_6 tests/test_call_80062434_6.cpp)
    target_link_libraries(test_call_80062434_6 PRIVATE am3d_exe)
    add_test(NAME call_80062434_6 COMMAND test_call_80062434_6)
    add_executable(test_call_80061f80_6 tests/test_call_80061f80_6.cpp)
    target_link_libraries(test_call_80061f80_6 PRIVATE am3d_exe)
    add_test(NAME call_80061f80_6 COMMAND test_call_80061f80_6)
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
    add_executable(test_front_tim tests/test_front_tim.cpp)
    target_link_libraries(test_front_tim PRIVATE am3d_platform_core)
    add_test(NAME front_tim COMMAND test_front_tim)
    if(AM3D_WITH_SDL2)
        add_executable(test_sdl_platform tests/test_sdl_platform.cpp)
        target_link_libraries(test_sdl_platform PRIVATE am3d_platform_sdl2)
        add_test(NAME sdl_platform COMMAND test_sdl_platform)
        set_tests_properties(sdl_platform PROPERTIES
            ENVIRONMENT "SDL_VIDEODRIVER=dummy;SDL_AUDIODRIVER=dummy;SDL_RENDER_DRIVER=software")
    endif()
endif()
