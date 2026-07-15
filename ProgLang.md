# C/C++ Programming language definitons
All features and extensions that should use for MaiCStyle

## Paradigms
- Make the job done
- Yolo coding from the start, you dont know the future, so should not always plan ahead (but experiences and knowledges can help avoid some bad futures)
- Functional when logic are more important than performance
- Sometime imperative make the job more easily
- OOP have its place, but not everywhere
- C++ come with some features that we will needed to make code more productivity and performance. But be careful!


## C standard and extensions
- C99 is enough to use in all cases
- C11 if you need some things fancy, modern (Generics, static assert)
- C2x never used


## C++ if needed
- Prefer Orthodox C++ approachs
- Keep simple and stupid
- Avoid class and methods when your dont need it
- Keep class hierarchy narrow
- Avoid modules
- Composite over inheritance
- Simple template is good enough
- Avoid template metaprogramming in most cases
- Prefer mature language standards
    - Only C++11 is good enough
    - Now C++20 is mature on common compilers
    - Take care of compiled code in new features
- If statement with init-statement
- Constexpr


## C++ Extensions (maybe used)
- Designated initializer (required G++ or Clang++)
- Compiler-depended attributes, modifiers
- Be careful of Unwind tables too
- Compiler flags: -fno-exceptions -fno-unwind-tables


## C++ avoid features
- RTTI, `std::type_info`. If Reflection and Serialization is needed, roll your own implementation.
- Exceptions, avoid as all costs.
- Deep and complex class inheritation hierarchy.
- Interface for polymorphism over class.
- No heavy OOP and design pattern, prefer data structure and algorithm. Simple implementation.
- Compiler flags: -fno-rtti


## Extended Uniserval Keywords
See details in example/compiler_extenions
- `nullptr`
- `alignof`, `alignas`
- `constexpr`
- `static_assert`
- `__forceinline`
- `__vectorcall`
- `__enum_type`
- `__default_init`
- `__typename`
- `__deprecated`
- `__deprecated_msg`


# Combine C/C++ 
Combine C/C++ with clang compiler to form a good language with some ergonomic features for productivity.
One of showcase are Mai Vectormath library use this form of language to make API more ergonomic.
