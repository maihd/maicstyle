@echo off

clang++ -c lib.cpp -o lib.o

clang++ -c main.c -o main.o

clang++ main.o lib.o -o a2.exe

a2.exe

del a2.exe
