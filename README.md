# MaiHD's C/C++ programming style

## Disclaimer

- TLDR: Just learn and use Odin programming language. It have the same mindset and features what I want. I encourage you to learn it!
- I'm still learning and practicing for better as C/C++. Ideas and opinions may wrong.
- Mai English is not good, if You find the typos, wrong words and wrong meanings, please help!
- This repo can be consider as a R&D for Mai personal work, you can find some ideas in `docs/collections`/`examples` folder.


# Language can affect this style
Language that mostly can use DoD approachs:
- C/C++
- Odin
- Beef
- C#
- Lua flat procedural coding style (Hades, Bitsquid Games, ...)


# Table of Contents

1. [Inventing on Principles](#inventing-on-principles)
2. [Workflow](#workflow)
3. [Programming Languages, Standards, Spirits](#proglang-standards-spirits)
4. [Naming conventions](#naming-conventions)
5. [Types](#types)
6. [Scoping](#scoping)
7. [File layout](#file-layout)
8. [Project architecture](#project-architecture)
9. [Build system](#build-system)
10. [Tooling](#tooling)
11. [Additional Resources](#additional-resources)


## Inventing on Principles <a name="inventing-on-principles" />

- Do what matter to get the job done!
- Immediate feedback, iterations is king.
- What you see is what you get: WYSIWYG
- SOLID: Simple, open, low level and learn the hard way, immediate, debug/discipline
- Self-reliance, mindfulness: Stay focused on the project, and the project only, right now!
- "What I cannot create, I cannot understand" - Richard Feynman
- Zen creating & living!


## Workflow <a name="workflow" />
Working on it. But follow above principles.


## Programming Languages, Standards, Spirits <a name="proglang-standards-spirits" />

- Basically use C99 and C++11.
    - Update 5/6/2024: C11 (C17 just a fix bugs version of C11) and C++17 widely support now (MSCV, Clang, GCC). But without appreciate reasons, you should avoid thoses features.
    - Update 3/7/2025: C11 and C++20
- Follow spirits of C, simple and easy to read. Joy of programming.
- `#pragma once` is widely supported now. Use it preferly over header guards.
- Use unix encoding.
- Content file only support ASCII. Donot use utf8 file format.
- Prefer code that both compile on C and C++, especially on header files.
- Some features can be support both on C and C++ with extensions, define a keyword with preprocessor.
- Preprocessor is not bad. Duck typing is not bad. Un-tested code is bad. Write the code are needed to be written, test and proof that code work, are the good resolutions for thoses problems. But preprocessor will make you hard to debugging the program, be careful!
- Prefer clang (and family like zig cc) for toolchains, feel free to use extensions if project is clang-only.
- Deep dive in [ProgLang.md](/docs/ProgLang.md)


## Naming conventions <a name="naming-conventions" />
See [NAMING.md](/docs/NAMING.md)


## Types <a name="types" />

- Integer type: use specified width integers for data structures, int for parameters, return types, local variables.
    + `int8_t`/`uint8_t` instead of `char`/`unsigned char` in data structures.
    + `int16_t`/`uint16_t` instead of `short`/`unsigned short` in data structures.
    + `int32_t`/`uint32_t` instead of `int`/`unsigned int` in data structures.
    + `int64_t`/`uint64_t` instead of `long long`/`unsigned long long` (`long` is 32-bit on Windows) in data structures.
    + In some cases, there will need `float32_t`/`float64_t` instead of `float`/`double`
    + Specified width integers in ensure the data structures are same size independent on platforms.
    + `int` and familiar is prefer because this help compiler do optimization. (rarely use, only helpful for uncommon platforms)

- `float` prefer to `double`, only use `double` when needed.
- (C only) Generic types: `Array(T)`, `Buffer(T)`, `HashTable(T)`. Avoid `T*` for multiple values. Should add prefix `T`.
- `T*` mean pass-by-reference, it mustnot be `NULL`. In C++, we have pass-by-reference, use it.
- Use value semantic, pass-by-value. For performance reason, make sure use const reference/pointer to prevent evil work on data structures.
- Typedef struct, enum, union. Prefer explicit aligned data structures.
    ```C
    typedef struct ALIGNAS(vec3, 16) // ALIGNAS is crossplatform of __declspec(align)
    {
        float x, y, z;
    } vec3;

    typedef enum WindowFlags
    {
        ...
    } WindowFlags;

    typedef union Handle
    {
        void*       onWindows;
        uint64_t    onUnix;
    } Handle;
    ```

- Plain-old data prefer to C++ struct.
- Avoid use C++ namespace, because C doesnot support. So avoid enum class too.
- Extended primitive types: vectors and matrices (for graphics and game programming)
    + `vec2`, `vec3`, `vec4`: single precision floating-point vectors (32-bit per component)
    + `ivec2`, `ivec3`, `ivec4`: signed integer vectors (32-bit per component)
    + `uvec2`, `uvec4`, `uvec4`: unsigned interger vectors (32-bit per component)
    + `mat2`, `mat3`, `mat4`: single precision floating-point matrices (32-bit per component)
    + `imat2`, `imat3`, `imat4`: signed integer vectors (32-bit per component)
    + `umat2`, `umat3`, `umat4`: unsigned integer vectors (32-bit per component)
    + `bool2`, `bool3`, `bool4`: one-byte wide component (1-bit per component)
    + `<std_wided_prim>x<components>_t` (`uint32x4_t`, `int32x4_t`, `float32x4_t`, ...): SIMD primitive types


## Scoping <a name="scoping" />

- Single `{`/`}` in one line, add newline after it.
- But all definition of macro when have multiple lines.


## File layout <a name="file-layout" />

- File Header (beginning of the file, not to confusing with .h files)
    - Optional meta information, grouping by a block of coments
    - Pragma, header guards, compiler/linker options
    - Include all needed dependencies
    - Declaration of all types
    - Declaration of all functions/macros. But donot declare `main`.

- File Body
    - Definitions of all types
    - Definitions of all functions

- File Footer
    - An optional end-of-file mark. Ex: `//! EOF`
    - Should end with a newline, some compilers need this (gcc family)

- Grouping
    - Functions and types declaration should be grouping
    - Functions and types need to align by columm, easy to find return-type, function name
    - Seperate functions, types declaration group with 1 empty line
    - Separate functions, types define with 2 empty lines


## Function
- Grouping chunk by work, what to do
- Prefer clear, readable code
- Prefer pure function if available
- Avoid declare one line variables for pointer type (missing *)
- Can use 2 newlines to seperating big chunk of code


## Project architecture <a name="project-architecture" />

- Filename: prefer PascalCase. Maybe have `Namespace_` prefix. Ex: `Example_HelloWorld.c`
- Libraries/modules should be small. The smallest size of a library is a single header file. The smallest size of a module is a function.
- Prefer test of module, usage of module. Unit tests should help, but not always.
- Should have an real-life application come with it.
- Everything should have been maintaining, so the place of VCS.
- Self-reliance, so less dependencies. Add and use with care. Even standard library (see [`examples/free_runtime_1`](/examples/free_runtime_1/) for more details).


## Build system <a name="build-system" />

- CMake is default choice for many platforms.
- Base knowlege of gmake/VisualStudio always needed.
- Some incremental build systems like: Ninja, FASTBuild,... Help your iterations, CMake help working with Ninja flawless.
- gmake maybe best fit for many projects, counting cross-platforms.
- Sometime `build.bat`/`build.sh` is all I need.
- Sometime Premake/GENie help me faster in prototype build system.


## Tooling (helpful and need to learn) <a name="tooling" />

- Clang and LLVM, and families
- Clang Static Analyzer
- Clang Format
- Clang Tidy
- Clang AST dump (for bindgen and preprocessing)
- Undefined behavior sanitizer (all compilers)
- Memory sanitizer (all compilers)
- Thread sanitizer?
- Tracy Profiler
- Platform's native profiler
- VSCode clangd (LSP for coding C/C++ with VSCode, better than VSCode Intellisense, also support swizzle syntax for vector primitives)
    - Note (11/03/2024): clangd is extremely using too much resources (RAM, CPU) when project have large header files (commonly with single header file libraries)
- Visual Studio and helpers (not only compiler and code editor part)


## Additional Resources <a name="additional-resources" />
This section is a resources to other styles that help me through time, and it's worth to findout. It's also proved production-ready, inuse by many products, companies. (You will find its' gamedev-oriented).
- [Orthodox C++](https://gist.github.com/bkaradzic/2e39896bc7d8c34e042b)
- [idSoftware CodingConventions](https://fabiensanglard.net/fd_proxy/doom3/CodeStyleConventions.pdf) [Mirror](/docs/idCodeStyleConventions.pdf)
- [John Carmack's inline code](http://number-none.com/blow/john_carmack_on_inlined_code.html)
- [Casey Muratori's Compression Oriented Programming](https://caseymuratori.com/blog_0015)
- [Insomniac's Coding Standard](https://gist.github.com/Kerollmops/fcad27cfef9e3552cb75a3d201494ba6)
- [Lucas Sas's Modern C](https://www.youtube.com/watch?v=QpAhX-gsHMs)
- [Eskil Steenberg's How I program C](https://www.youtube.com/watch?v=443UNeGrFoM&list=PLT6InxK-XQvOpYklsuSAcQ9zmVDClRX6x&index=1)
- [Cognitive load for programming](https://github.com/zakirullin/cognitive-load)
- [Mordern C in BeefLang](https://github.com/maihd/FunWithBeef/blob/main/Essays/BeefForModernC/README.md)
