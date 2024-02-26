@echo off

@REM set CC=clang
@REM set CC=zig cc
set CC=C:\msys64\mingw64\bin\clang.exe

%CC% main.c isocline/src/isocline.c -Wno-all -std=c99 -Iisocline/include
