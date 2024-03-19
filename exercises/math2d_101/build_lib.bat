@echo off

call vars.bat

set SRC=src/lib.c

%CC% -shared -o lib.dll %SRC% tigr.dll
