#pragma once

#include "types.h"
#include "compiler.h"

__forceinline f32 f32x2_dot(f32x2 a, f32x2 b)
{
    return a.x * b.x + a.y * b.y;   
}


//! EOF

