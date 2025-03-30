@echo off

clang++ -c lib.cpp -o lib.o

llvm-ar rcs lib.lib lib.o

clang++ main.c lib.lib -o a.exe
