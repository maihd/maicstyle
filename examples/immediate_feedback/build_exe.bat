@echo off

set CFLAGS=-fno-sanitize=undefined -Iinclude
set LFLAGS=lib/raylibdll.lib

zig cc main.c HotDylib.c %CFLAGS% %LFLAGS%