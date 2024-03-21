#pragma once

#include "types.h"
#include "compiler.h"

__forceinline f32x2 f32x2_new(f32 x, f32 y)
{
    f32x2 v;
    v.x = x;
    v.y = y;
    return v;
}

__forceinline f32 f32x2_dot(f32x2 a, f32x2 b)
{
    return a.x * b.x + a.y * b.y;
}


//! EOF

