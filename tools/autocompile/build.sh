#!/bin/sh

CFLAGS="-std=c11 -I../slibs/include"
LFLAGS=""

clang autocompile.c Json.c ../slibs/src/slibs.c -o autocompile $CFLAGS $LFLAGS