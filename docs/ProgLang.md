# C/C++ Programming language definitons
All features and extensions that should use for MaiCStyle. Forming C/C++ into a dialect.


## Paradigms
- Make the job done
- Joy of programming and effortless coding
- Procedural programming by default
- OOP have its place, but not everywhere. Sometime you just need interfaces, dynamic dispatch, not class and inheritation.
- C++ come with some features that we will needed to make code more productivity and performance. But be careful!
- Features and coding patterns inspired from Odin (both languages and compiler source code)


## C standard and extensions
- C99 is enough to use in all cases
- C11 if you need some things fancy, modern (Generics, static assert)
- C2x never used


## C features that I avoid
- Increment and decrement, use `+=`/`-=` instead. In seperated line.
- Too much global state. If use global state, it's much reasonable. The most cases is library have its global state.
- Pointer for everything, if useful, but have drawbacks, and have other solution fit better. Like handle. Same usage of weak pointer.


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
    - C++14 is a good balance between usable and features bloat
- If statement with init-statement
- Constexpr


## C++ Extensions (maybe used)
- Designated initializer (required G++ or Clang++)
- Compiler-depended attributes, modifiers
- Be careful of Unwind tables too
- Compiler flags: ```

```

## C++ avoid features
- RTTI, `std::type_info`. If Reflection and Serialization is needed, roll your own implementation.
- Exceptions, avoid as all costs.
- Deep and complex class inheritation hierarchy.
- Interface for polymorphism over class.
- No heavy OOP and design pattern, prefer data structure and algorithm. Simple implementation.
- Compiler flags: `-fno-rtti -fno-exceptions -fno-unwind-tables`


## Extended Uniserval Keywords
See details in `example/compiler_extenions`
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
- `defer`


## Combine C/C++
Combine C/C++ with clang compiler to form a good language with some ergonomic features for productivity.
One of showcase are Mai Vectormath library use this form of language to make API more ergonomic.
I called this ProC++ (Procedural Programming C++).
