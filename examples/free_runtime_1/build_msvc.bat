@echo off

cl.exe -nologo -Gm- -GR- -EHa- -Oi -GS- -Gs9999999 main.c -link -nodefaultlib -subsystem:console kernel32.lib main.obj
