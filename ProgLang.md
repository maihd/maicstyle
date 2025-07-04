# C/C++ Programming language definitons
All features and extensions that should use for MaiCStyle

## Paradigms
- Make the job done
- Yolo coding from the start, you dont know the future, so should not always plan ahead (but experiences and knowledges can help avoid some bad futures)
- Functional when logic are more important than performance
- Sometime imperative make the job more easily
- OOP have its place, but not everywhere


## C standard and extensions
- C99 is enough to use in all cases
- C11 if you need some things fancy, modern (Generics, static assert)
- C2x never used


## C++ if needed
- Prefer Orthodox C++ approachs
- Keep simple and stupid
- Keep class hierarchy narrow
- Composite over inheritance
- Avoid template metaprogramming in most cases
- Prefer mature language standards
    - Only C++11 is good enough
    - Now C++17 is mature on common compilers
    - Take care of compiled code in new features
- If statement with init-statement
- Constexpr


## C++ Extensions (maybe used)
- Designated initializer (required G++ or Clang++)
- Compiler-depended attributes, modifiers


## C++ avoid features
- RTTI, `std::type_info`. If Reflection and Serialization is needed, roll your own implementation.
- Exceptions, avoid as all costs.
- Deep and complex class inheritation hierarchy.
- Interface for polymorphism over class.
- No heavy OOP and design pattern, prefer data structure and algorithm. Simple implementation.


## Uniserval keywords
See details in example/compiler_extenions
- `nullptr`
- `alignof`, `alignas`
- `constexpr`
- `__forceinline`
- `__enum_type`
- `__default_init`
- `__typename`
- `__deprecated`
- `__deprecated_msg`


# Combine C/C++ 
Combine C/C++ with clang compiler to form a good language with some ergonomic features for productivity.
One of showcase are Mai Vectormath library use this form of language to make API more ergonomic.
