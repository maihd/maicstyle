# Immediate Feedback Principles Examples
This demo to help me development Immediate Feedback principle, the need and pros/cons to use it.

## Requirements
- Zig compiler
- Windows
- (Optional) GMake

## Build
With gmake:
- `make exe` to create executable
- `make dll` to create dynamic library, which is loaded at runtime by executable
- `make autodll` to automatically check change the lib.c file, and recompiled, executable will take effect immediately

With Windows batch:
- `build_exe.bat` to create executable
- `build_dll.bat` to create dynamic library, which is loaded at runtime by executable
- `auto_build_dll.bat` to automatically check change the lib.c file, and recompiled, executable will take effect immediately

## Acknowledge
- Raysan5 and His raylib
- Zig community