@echo off

call vars.bat

set SRC=src/main.c src/HotDylib.c

%CC% -o a.exe %SRC% tigr.dll
