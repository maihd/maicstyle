#pragma once

typedef int             b32;
typedef int             i32;
typedef unsigned int    u32;
typedef float           f32;

typedef i32             i32x2 __attribute__((ext_vector_type(2))); // Vector2 of i32
typedef u32             u32x2 __attribute__((ext_vector_type(2))); // Vector2 of u32
typedef f32             f32x2 __attribute__((ext_vector_type(2))); // Vector2 of f32

//! EOF


