# Math2D 101 exercises and practices
Based on Randy Gaul's Game Math 101, but the language is C99 + Clang compiler.

## Links
- https://randygaul.github.io/math/2022/09/18/Game-Math-101-Writing-your-Own-2D-Math-in-CPP.html

## Building and development
- Require Clang on MinGW runtime:
    ```batch
    :: Download this:
    ::  https://www.msys2.org/
    :: And install it to C:\msys64
    :: Then run this:
    ::  C:\msys64\mingw64.exe
    :: And install clang:
    ::  pacman -S mingw-w64-x86_64-clang
    ```
- Build steps:
    ```batch
    build_tigr.bat
    build_lib.bat
    build.bat
    ```

- Running:
    ```batch
    a.exe :: or `start a.exe` to execute in another console

    build_lib.bat :: when change the logic code
    ```
