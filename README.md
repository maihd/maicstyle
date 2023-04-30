# C/C++ programming style

## Languages, Standards, Spirits
- Use C99 and C++14
- Follow spririts of C, simple and easy to read
- `#pragma once` is widely supported now. Use it prefer to header guards
- Use unix encoding
- Content file only support ascii. Donot use utf8 file format.
- Prefer code that both compile on C and C++
- Some features can be support both on C and C++ with extensions, define a keyword with preprocessor
- Preprocessor is not bad. Duck typing is not bad. Un-tested code is bad. Write the code are needed to be written, test and proof that code work, are the good resolutions for thoses problems. 

## Naming convention

1. Typename: PascalCase. Ex: Texture, Shader, Image, ...
2. Function name: CamelCase, ModuleName_CamelCase. Ex: ArrayPush, Texture_New, ...
3. Enums, constants: ALL_CAPS_CASE. Ex: PI, NULL, PIXEL_RGBA, ...
4. Enums only: TypeName_MemberName. Ex: JsonError_OutOfMemory, FileAccess_ReadWrite, ...
5. Variables, fields, paramaters: camelCase. Ex: texture.width, texture.height, ...

## Types

1. Integer type: use specified width integers for data structures, int for parameters, return types, local variables.
    + int8_t/uint8_t instead of char/unsigned char in data structures.
    + int16_t/uint16_t instead of short/unsigned short in data structures.
    + int32_t/uint32_t instead of int/unsigned int in data structures.
    + int64_t/uint64_t instead of long long/unsigned long long (long is 32bit in Windows) in data structures.
    + Specified width integers in ensure the data structures are same size independent on platforms.
    + int and familiar is prefer because this help compiler do optimization.

2. float prefer to double, only use double when needed.
3. Generic types: Array(T), Buffer(T), HashTable(T). Avoid T* for multiple values.
4. T* mean pass-by-reference, it mustnot be NULL.
5. Use value semantic, pass-by-value. For performance reason, make sure use const to prevent evil work on data structures.
6. Typedef struct, enum, union. Prefer explicit aligned data structures.
    ```c
    typedef struct ALIGNAS(Vector3, 16) // ALIGNAS is crossplatform of __declspec(align)
    {
        float x, y, z;
    } Vector3;

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

## Scoping

1. Single '{' '}' in one line, add newline after it.
2. But all definition of macro when have multiple lines.

## File layout

1. Optional meta information, grouping by a block of comments
2. Pragma, header guards, compiler/linker options
3. Include all needed dependencies
4. Declaration of all types
5. Declaration of all functions/macros. But donot declare `main`.
6. Definitions of all types
7. Definitions of all functions
8. An optional end-of-file mark
9. Should end with a newline, some compiler need this

## Project architecture

1. Filename: prefer PascalCase. Maybe have Namespace_ prefix. Ex: Example_HelloWorld.c
2. Libraries/modules should be small. The smallest size of a library is a single header file. The smallest size of a module is a function.
3. Prefer test of module, usage of module. Unit tests should help, but not always.
4. Should have an real-life application come with it.
5. Everything should have been maintaining, so this place of vcs.

## Build system

1. Prefer premake over cmake
2. But knowing cmake can be help
3. Base knowleged of gmake/VisualStudio always needed
4. Some incremental build systems like: ninja, FASTBuild, ... Should only use when needed
 
## Notes
1. Some projects will follow its own style for special reasons.
