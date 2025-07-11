Original content from: https://blog.kowalczyk.info/article/j/guide-to-predefined-macros-in-c-compilers-gcc-clang-msvc-etc..html

# Guide to predefined macros in C++ compilers (gcc, clang, msvc etc.)

When writing portable C++ code you need to write conditional code that depends on compiler used or the OS for which the code is written.

Here’s a typical case:
```c
#if defined (_MSC_VER)
// code specific to Visual Studio compiler
#endif
```

To perform those checks you need to check pre-processor macros that various compilers set.

It can either be binary is defined vs. is not defined check (e.g. `__APPLE__`) or checking a value of the macro (e.g. `_MSC_VER` defines version of Visual Studio compiler).

This document describes macros set by various compilers.

Other documentations:
- Predefined macros in Visual Studio: https://sourceforge.net/p/predef/wiki/Compilers/
- To list clang’s pre-defined macros: `clang -x c /dev/null -dM -E`
- To list gcc’s pre-defined macros: `gcc -x c /dev/null -dM -E` (not that on mac gcc is actually clang that ships with XCode)
- The `-x c /dev/null -dM -E` also works for mingw (which is based on gcc)
> __Todos__: listing predefined macros for other compilers

## Checking for OS (platform)

To check for which OS the code is compiled:

| OS                                | Macros                                |  
| --------------------------------- | ------------------------------------- |
| Linux and Linux-derived           | `__linux__`                           |
| Android                           | `__ANDROID__` (implies `__linux__`)   |
| Linux (non-Android)               | `__linux__` && `!__ANDROID__`         |
| Darwin (Mac OS X and iOS)         | `__APPLE__`                           |
| Akaros (http://akaros.org)        | `__ros__`                             |
| Windows                           | `_WIN32`                              |
| Windows 64 bit                    | `_WIN64` (implies `_WIN32`)           |
| NaCL                              | `__native_client__`                   |
| AsmJS                             | `__asmjs__`                           |
| Fuschia                           | `__Fuchsia__`                         |

## Checking the compiler

To check which compiler is used:

| Compiler              | Macros                                            |
| --------------------- | ------------------------------------------------- |
| Visual Studio         | `_MSC_VER`                                        |
| gcc                   | `__GNUC__`                                        |
| clang                 | `__clang__`                                       |
| emscripten            | `__EMSCRIPTEN__` (for asm.js and webassembly)     |
| MinGW 32              | `__MINGW32__`                                     |
| MinGW-w64 32bit       | `__MINGW32__`                                     |
| MinGW-w64 64bit       | `__MINGW64__`                                     |

## Checking compiler version

__GNUC__ (e.g. 5) and __GNUC_MINOR__ (e.g. 1).

To check that this is gcc compiler version 5.1 or greater:

```c
#if defined(__GNUC__) && (__GNUC___ > 5 || (__GNUC__ == 5 && __GNUC_MINOR__ >= 1))
// this is gcc 5.1 or greater
#endif
```

Notice the chack has to be: major > 5 || (major == 5 && minor >= 1). If you only do major == 5 && minor >= 1, it won’t work for version 6.0.

clang

```c
__clang_major__, __clang_minor__, __clang_patchlevel__
```

Visual Studio

_MSC_VER and _MSC_FULL_VER:


| VS                            | _MSC_VER      | _MSC_FULL_VER     | 
| ----------------------------- | ------------- | ----------------- |
| 1                             | 800           |                   |
| 3                             | 900           |                   |
| 4                             | 1000          |                   |
| 4                             | 1020          |                   |
| 5                             | 1100          |                   |
| 6                             | 1200          |                   |
| 6 SP6                         | 1200          | 12008804          |
| 7                             | 1300          | 13009466          |
| 7.1 (2003)                    | 1310          | 13103077          |
| 8 (2005)                      | 1400          | 140050727         |
| 9 (2008)                      | 1500          | 150021022         |
| 9 SP1                         | 1500          | 150030729         |
| 10 (2010)                     | 1600          | 160030319         |
| 10 (2010) SP1                 | 1600          | 160040219         |
| 11 (2012)                     | 1700          | 170050727         |
| 12 (2013)                     | 1800          | 180021005         |
| 14 (2015)                     | 1900          | 190023026         |
| 14 (2015 Update 1)            | 1900          | 190023506         |
| 14 (2015 Update 2)            | 1900          | 190023918         |
| 14 (2015 Update 3)            | 1900          | 190024210         |
| 15 (2017 Update 1 & 2)        | 1910          | 191025017         |
| 15 (2017 Update 3 & 4)        | 1911          |                   |
| 15 (2017 Update 5)            | 1912          |                   |

More information:
    
    https://blogs.msdn.microsoft.com/vcblog/2016/10/05/visual-c-compiler-version/
    https://blogs.msdn.microsoft.com/vcblog/2017/11/15/side-by-side-minor-version-msvc-toolsets-in-visual-studio-2017/#comment-467525

MinGW

MinGW (aka MinGW32) and MinGW-w64 32bit: `__MINGW32_MAJOR_VERSION` and `__MINGW32_MINOR_VERSION`

MinGW-w64 64bit: `__MINGW64_VERSION_MAJOR` and `__MINGW64_VERSION_MINOR`

## Checking processor architecture

gcc

The meaning of those should be self-evident:
```c
    __i386__
    __x86_64__
    __arm__. If defined, you can further check:
        __ARM_ARCH_5T__
        __ARM_ARCH_7A__
    __powerpc64__
    __aarch64__
```
