@echo off

set CFLAGS=-std=c11 -D_CRT_SECURE_NO_WARNINGS -I../slibs/include
set LFLAGS=

clang autocompile.c Json.c ../slibs/src/slibs.c -o autocompile.exe %CFLAGS% %LFLAGS%

if %ErrorLevel% equ 0 (
    echo Build done at %TIME%
) else (
    echo Build autocompile.exe failed!
)