#pragma once

#include "types.h"
#include "scalar.h"
#include "compiler.h"

static_assert(sizeof(f32x2) == 2 * sizeof(f32), "Wrong size of f32x2");

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

__forceinline f32 f32x2_len(f32x2 v)
{
    return sqrtf(v.x * v.x + v.y * v.y);
}


//! EOF

