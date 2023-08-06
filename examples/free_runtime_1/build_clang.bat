@echo off

clang -v -nostdlib -ffreestanding -mconsole -O2 -fno-stack-check -fno-stack-protector -mno-stack-arg-probe -o free_runtime_1.exe main.c -lkernel32 -fuse-ld=lld-link