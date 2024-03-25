#pragma one

#include "types.h"
#include "vector.h"
#include "compiler.h"

__forceinline AABB aabb_new(f32x2 min, f32x2 max)
{
    return (AABB){ .min = min, .max = max };
}

__forceinline f32 aabb_width(AABB aabb)
{
    return aabb.max.x - aabb.min.x;
}

__forceinline f32 aabb_height(AABB aabb)
{
    return aabb.max.y - aabb.min.y;
}

__forceinline f32x2 aabb_center(AABB aabb)
{
    return (aabb.min + aabb.max) * 0.5f;
}

//! EOF


