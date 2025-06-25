@echo off

set CFLAGS=-fno-sanitize=undefined

zig cc main.c %CFLAGS%

a.exe