# MaiHD's C/C++ programming style

## Notes

- I'm still learning and practicing for better as C/C++. Ideas and opions may wrong. 
- My English is not good, if You find the typos, wrong word and wrong meaning, please help! 
- Some my projects will follow its own style for special reasons. Ex: vectormath
- I use other project style guide for thoses projects. It help me learn the others, and new stuffs, why not? 
- Because I will use Zig and Beef for some future projects, each languages has its own styles, I will follow the style, but the heart of priciple will be same: simple and make the job done!

## Inventing on Principles

- Get the job done! 
- Immediate feedback
- What you see is what you get: WYSIWYG
- Simple, open, immediate, low level, debug
    - The new SOLID principles
    - Keep it simple and small, for product
    - Keep it slow and steady, for development product
    - Open mind to the problem
    - Open data for the program to do what it needs to do
    - Open source for people
    - Immediate feedback, also know as low-latency iterations
    - Low level for abstractions
    - Love and passion
    - Debug easily, focus on development, and use better tools
    - All principles support each other
- Self-reliance, mindfulness
    - "What I cannot create, I cannot understand" - Richard Feynman
    - First, use it; second, attempt to create it with simple implementation; third, use it better
    - Stay focused on the project, and the project only, right now! 
- Zen create & living! 

## Languages, Standards, Spirits

- Use C99 and C++14
- Follow spririts of C, simple and easy to read
- `#pragma once` is widely supported now. Use it prefer to header guards
- Use unix encoding
- Content file only support ascii. Donot use utf8 file format.
- Prefer code that both compile on C and C++
- Some features can be support both on C and C++ with extensions, define a keyword with preprocessor
- Preprocessor is not bad. Duck typing is not bad. Un-tested code is bad. Write the code are needed to be written, test and proof that code work, are the good resolutions for thoses problems. 
- Prefer clang (and family like zig cc) for toolchains, feel free to use extensions if project is clang-only. 

## Naming convention

- Typename: `PascalCase`. Ex: `Texture`, `Shader`, `Image`, ...
- Function name: `PascalCase`, `ModuleName_FunctionName`. Ex: `ArrayPush`, `Texture_New`, ...
- Enums, constants: `ALL_CAPS_CASE`. Ex: `PI`, `NULL`, `PIXEL_RGBA`, ...
- Enums only: `TypeName_MemberName`. Ex: `JsonError_OutOfMemory`, `FileAccess_ReadWrite`, ...
- Variables, fields, paramaters: `camelCase`. Ex: `texture.width`, `texture.height`, ...

## Naming cheatsheet

- Init/Deinit: for initialization/deinitialization, no return pointer
- Create/Destroy: create new memory, init/deinit, and return pointer (object)
- Alloc/Free: actually request memory from system
- Acquire/Collect: get memory from a buffer/arena/allocator

## Types

- Integer type: use specified width integers for data structures, int for parameters, return types, local variables.
    + `int8_t`/`uint8_t` instead of `char`/`unsigned char` in data structures.
    + `int16_t`/`uint16_t` instead of `short`/`unsigned short` in data structures.
    + `int32_t`/`uint32_t` instead of `int`/`unsigned int` in data structures.
    + `int64_t`/`uint64_t` instead of `long long`/`unsigned long long` (`long` is 32-bit on Windows) in data structures.
    + In some cases, there will need `float32_t`/`float64_t` instead of `float`/`double`
    + Specified width integers in ensure the data structures are same size independent on platforms.
    + int and familiar is prefer because this help compiler do optimization.

- float prefer to double, only use double when needed.
- Generic types: `Array(T)`, `Buffer(T)`, `HashTable(T)`. Avoid `T*` for multiple values.
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

## Scoping

- Single `{` `}` in one line, add newline after it.
- But all definition of macro when have multiple lines.

## File layout

- Optional meta information, grouping by a block of comments
- Pragma, header guards, compiler/linker options
- Include all needed dependencies
- Declaration of all types
- Declaration of all functions/macros. But donot declare `main`.
- Definitions of all types
- Definitions of all functions
- An optional end-of-file mark
- Should end with a newline, some compilers need this (gcc family) 

## Project architecture

- Filename: prefer PascalCase. Maybe have Namespace_ prefix. Ex: Example_HelloWorld.c
- Libraries/modules should be small. The smallest size of a library is a single header file. The smallest size of a module is a function.
- Prefer test of module, usage of module. Unit tests should help, but not always.
- Should have an real-life application come with it.
- Everything should have been maintaining, so the place of VCS.

## Build system

- Prefer premake over cmake
- But knowing cmake can be help
- Base knowlege of gmake/VisualStudio always needed
- Some incremental build systems like: ninja, FASTBuild,... Should only use when needed
- gmake maybe best fit for many projects, counting cross-platforms
- Sometime build.bat is all I need

## License

Why you need a license for coding style. Copyright MaiHD @ Heart and Head. 