@echo off

set CFLAGS=-std=c11 -D_CRT_SECURE_NO_WARNINGS -I../slibs/include
set LFLAGS=

pushd %~dp0

clang autocompile.c Json.c ../slibs/src/slibs.c -o autocompile.exe %CFLAGS% %LFLAGS%

popd 

if %ErrorLevel% equ 0 (
    echo Build done at %TIME%
) else (
    echo Build autocompile.exe failed!
)