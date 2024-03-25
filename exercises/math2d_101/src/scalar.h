#pragma once

#include <math.h>
#include "types.h"
#include "compiler.h"

__forceinline i32 i32_sign(i32 x)
{
    return x < 0 ? -1 : 1;
}

__forceinline i32 f32_sign(f32 x)
{
    return x < 0 ? -1 : 1;
}

//! EOF

