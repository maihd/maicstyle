@echo off

@REM set CC=clang
@REM set CC=zig cc
set CC=C:\msys64\mingw64\bin\clang.exe

set LIBS=isocline/src/isocline.c mpc/mpc.c

%CC% main.c %LIBS% -Wno-all -std=c99 -Iisocline/include -Impc
