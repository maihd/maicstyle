@echo off

call vars.bat

set SRC=src/main.c src/HotDylib.c src/HotDylibEx.c

%CC% -o a.exe %SRC% tigr.dll
