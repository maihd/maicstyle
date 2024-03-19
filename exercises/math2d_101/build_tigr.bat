@echo off

call vars.bat

%CC% -shared src/tigr.c -o tigr.dll -DTIGR_EXPORT -lUser32 -lGDI32 -lOpenGL32
