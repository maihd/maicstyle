#include <stdio.h>

#include "HotDylibApi.h"
#include "common.h"
#include "types.h"
#include "vector.h"

__forceinline void tigrLineV(Tigr* window, f32x2 p0, f32x2 p1, TPixel color)
{
    tigrLine(window, (int)p0.x, (int)p0.y, (int)p1.x, (int)p1.y, color);
}

HOTDYLIB_EXPORT void* INIT_FN(void* data, HotDylibState newState, HotDylibState oldState)
{
    return nullptr;
}

DEFINE_UPDATE_FN(window)
{

}

DEFINE_DRAW_FN(window)
{
    tigrLine(window, 0, 0, 100, 100, tigrRGB(0xff, 0xff, 0xff));
    tigrLineV(window, f32x2_new(0, 0), f32x2_new(30, 200), tigrRGB(0xff, 0xff, 0xff));
}

//! EOF

