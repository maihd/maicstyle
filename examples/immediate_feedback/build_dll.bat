@echo off

set CFLAGS=-fno-sanitize=undefined -Iinclude
set LFLAGS=lib/raylibdll.lib

zig cc -shared -o lib.dll -fPIC lib.c %CFLAGS% %LFLAGS%