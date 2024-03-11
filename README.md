# MaiHD's C/C++ programming style

## Notes

- I'm still learning and practicing for better as C/C++. Ideas and opinions may wrong.
- My English is not good, if You find the typos, wrong words and wrong meanings, please help!
- Some my projects will follow its own style for special reasons. Ex: vectormath
- I use other projects style guide for thoses projects. It help me learn the others, and new stuffs, why not?
- Because I will use Zig and Beef for some future projects, each languages has its own styles, I will follow the style, but the heart of priciple will be same: Simply make the job done!
- Based on the important of the section, I will bring it first the most important, last section is the least important.

# Table of Contents

1. [Inventing on Principles](#inventing-on-principles)
2. [Workflow](#workflow)
3. [Languages, Standards, Spirits](#languages-standards-spirits)
4. [Naming convention](#naming-convention)
5. [Naming convention 2](#naming-convention-2)
6. [Naming cheatsheet](#naming-cheatsheet)
7. [Types](#types)
8. [Scoping](#scoping)
9. [File layout](#file-layout)
10. [Project architecture](#project-architecture)
11. [Build system](#build-system)
12. [Tooling](#tooling)
13. [License](#license)
14. [Additional Resources](#additional-resources)

## Inventing on Principles <a name="inventing-on-principles" />

- Do what matter to get the job done!
- Immediate feedback
- What you see is what you get: WYSIWYG
- Simple, open, immediate, low level, debug/discipline
    - The new SOLID principles
    - Keep it simple and small, for product
    - Keep it slow and steady, for development product
    - Open mind to the problem
    - Open data for the program to do what it needs to do
    - Open source for people
    - Open the black box practice
    - Immediate feedback, also know as low-latency iterations
    - Inventing on principles (recursive until there are no principles needed)
    - Incrementally development
    - Low level for abstractions
    - Love and passion
    - Learn the hard way
    - Debug easily, focus on development, and use better tools
    - Discipline, donot break the rules of the project (each project have each own rules)
    - All principles support each others
- Self-reliance, mindfulness
    - "What I cannot create, I cannot understand" - Richard Feynman
    - First, use it; second, attempt to create it with simple implementation; third, use it better
    - Stay focused on the project, and the project only, right now!
- Zen creating & living!

## Workflow <a name="workflow" />

Working on it.

## Languages, Standards, Spirits <a name="languages-standards-spirits" />

- Use C99 and C++14
- Follow spririts of C, simple and easy to read
- `#pragma once` is widely supported now. Use it prefer to header guards
- Use unix encoding
- Content file only support ascii. Donot use utf8 file format.
- Prefer code that both compile on C and C++
- Some features can be support both on C and C++ with extensions, define a keyword with preprocessor
- Preprocessor is not bad. Duck typing is not bad. Un-tested code is bad. Write the code are needed to be written, test and proof that code work, are the good resolutions for thoses problems.
- Prefer clang (and family like zig cc) for toolchains, feel free to use extensions if project is clang-only.

## Naming convention <a name="naming-convention" />
Please know that naming convention in C/C++ is not forcing in variant type of projects. Mean that naming for readable more important than conventions.
- Typename: `PascalCase`. Ex: `Texture`, `Shader`, `Image`, ...
- Function name: `PascalCase`, `ModuleName_FunctionName`. Ex: `ArrayPush`, `Texture_New`, ...
- Enums, constants: `ALL_CAPS_CASE`. Ex: `PI`, `NULL`, `PIXEL_RGBA`, ...
- Enums only: `TypeName_MemberName`. Ex: `JsonError_OutOfMemory`, `FileAccess_ReadWrite`, ...
- Variables, fields, paramaters: `camelCase`. Ex: `texture.width`, `texture.height`, ...
- Custom keywords: `__snake_case`. Ex: `__enum_type`, `__default_init`, `__defer`, `__typename`, `__scope`, ...
- Reuse keywords instead of define new: `constexpr`, `__forceinline`, `alignas`, `alignof`, `offsetof`, `container_of`, `__vectorcall`, ...

## Naming convention 2 <a name="naming-convention-2" />
This convention is more common in C/C++. So I accept this.
- Typename: `PascalCase`. Ex: `Texture`, `Shader`, `Image`, ...
- Module name: `snake_case`. Ex: `vec2`, `mat4`, ...
- Function name: `snake_case`, `module_name_function_name`. Ex: `array_push`, `texture_new`, ...
- Enums, constants: `ALL_CAPS_CASE`. Ex: `PI`, `NULL`, `PIXEL_RGBA`, ...
- Enums only: `TypeName_MemberName`. Ex: `JsonError_OutOfMemory`, `FileAccess_ReadWrite`, ...
- Variables, fields, paramaters: `snake_case`. Ex: `texture.width`, `texture.height`, ...
- Custom keywords: `__snake_case`. Ex: `__enum_type`, `__default_init`, `__defer`, `__typename`, `__scope`, ...
- Reuse keywords instead of define new: `constexpr`, `__forceinline`, `alignas`, `alignof`, `offsetof`, `container_of`, `__vectorcall`, ...

## Naming cheatsheet <a name ="naming-cheatsheet" />
This section need a database, because naming is enormous and must have only one meaning.
- Init/Deinit: for initialization/deinitialization, no return pointer
- Create/Destroy: create new memory, init/deinit, and return pointer (object)
- Alloc/Free: actually request memory from system
- Acquire/Release: get memory (also resources) from a buffer/arena/allocator (not return to system when call release)

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
- `T*` mean pass-by-reference, it mustnot be `NULL`.
- Use value semantic, pass-by-value. For performance reason, make sure use const to prevent evil work on data structures.
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
    + `<std_wided_prim>x<components>_t>` (`uint32x4_t`, `int32x4_t`, `float32x4_t`, ...): SIMD primitive types

## Scoping <a name="scoping" />

- Single `{` `}` in one line, add newline after it.
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

## Project architecture <a name="project-architecture" />

- Filename: prefer PascalCase. Maybe have `Namespace_` prefix. Ex: `Example_HelloWorld.c`
- Libraries/modules should be small. The smallest size of a library is a single header file. The smallest size of a module is a function.
- Prefer test of module, usage of module. Unit tests should help, but not always.
- Should have an real-life application come with it.
- Everything should have been maintaining, so the place of VCS.
- Self-reliance, so less dependencies. Add and use with care. Even standard library (see `examples/free_runtime_1` for more details).

## Build system <a name="build-system" />

- Prefer premake over cmake
- But knowing cmake can be help
- Base knowlege of gmake/VisualStudio always needed
- Some incremental build systems like: ninja, FASTBuild,... Should only use when needed
- gmake maybe best fit for many projects, counting cross-platforms
- Sometime build.bat is all I need

## Tooling (helpful and need to learn) <a name="tooling" />

- Clang and LLVM, and families
- Clang Static Analyzer
- Clang Format
- Clang Tidy
- Clang AST dump (for bindgen and preprocessing)
- VSCode clangd (LSP for coding C/C++ with VSCode, better than VSCode Intellisense, also support swizzle syntax for vector primitives)
    - Note (11/03/2024): clangd is extremely using too much when project have large header files (commonly with single header file libraries)
- Visual Studio and helpers (not only compiler and code editor part)

## License <a name="license" />

Why you need a license for coding style. Copyright MaiHD @ Heart and Head.

## Additional Resources <a name="additional-resources" />

This section is a resources to other styles that help me through time, and it's worth to findout. It's also proved production-ready, inuse by many products, companies. (You will find its' gamedev-oriented).
- [Orthodox C++](https://gist.github.com/bkaradzic/2e39896bc7d8c34e042b)
- [idSoftware CodingConventions](https://fabiensanglard.net/fd_proxy/doom3/CodeStyleConventions.pdf) [Mirror](/docs/idCodeStyleConventions.pdf)
- [John Carmack's inline code](http://number-none.com/blow/john_carmack_on_inlined_code.html)
- [Insomniac's Coding Standard](https://gist.github.com/Kerollmops/fcad27cfef9e3552cb75a3d201494ba6)
- [Lucas Sas's Modern C](https://www.youtube.com/watch?v=QpAhX-gsHMs)
- [Eskil Steenberg's How I program C](https://www.youtube.com/watch?v=443UNeGrFoM&list=PLT6InxK-XQvOpYklsuSAcQ9zmVDClRX6x&index=1)
