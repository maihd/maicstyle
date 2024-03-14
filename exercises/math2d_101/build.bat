@echo off

set SRC=src/main.c src/tigr.c

clang -o a.exe %SRC%
