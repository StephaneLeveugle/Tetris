@echo off

set CommonCompilerFlags=-MTd -nologo -fp:fast -Gm- -GR- -EHa- -Od -Oi -WX -W4 -wd4996 -wd4201 -wd4100 -wd4189 -wd4505 -FC -Z7
set CommonLinkerFlags= -incremental:no -opt:ref user32.lib gdi32.lib winmm.lib

rem cl %CommonCompilerFlags% vmtranslator.cpp /link %CommonLinkerFlags%

cl -MTd -nologo -Z7 ..\sources\win32_layer.cpp /link user32.lib gdi32.lib

