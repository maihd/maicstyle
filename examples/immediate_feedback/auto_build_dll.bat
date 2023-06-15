@echo off

set CFLAGS=-fno-sanitize=undefined -Iinclude
set LFLAGS=lib/raylibdll.lib

zig cc -o auto_build_dll.exe auto_build_dll.c HotDylibEx.c -fno-sanitize=undefined

auto_build_dll.exe