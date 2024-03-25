#include <stdio.h>

#include "HotDylibApi.h"

#include "common.h"
#include "types.h"
#include "aabb.h"
#include "vector.h"

void draw_point(Tigr* window, f32x2 v, TPixel color)
{
    tigrPlot(window, (int)v.x, (int)v.y, color);
}

TPixel color_white(void)
{
    return tigrRGB(0xff, 0xff, 0xff);
}

TPixel color_black(void)
{
    return tigrRGB(0x0, 0x0, 0x0);
}

void draw_line(Tigr* window, f32x2 p0, f32x2 p1, TPixel color)
{
    tigrLine(window, (int)p0.x, (int)p0.y, (int)p1.x, (int)p1.y, color);
}

void draw_aabb(Tigr* window, AABB aabb, TPixel color)
{
    f32x2 p1 = aabb.min;
    f32x2 p2 = f32x2_new(aabb.min.x, aabb.max.y);
    f32x2 p3 = f32x2_new(aabb.max.x, aabb.min.y);
    f32x2 p4 = aabb.max;

    draw_line(window, p1, p2, color);
    draw_line(window, p1, p3, color);
    draw_line(window, p2, p4, color);
    draw_line(window, p3, p4, color);
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
    draw_line(window, f32x2_new(0, 0), f32x2_new(30, 200), tigrRGB(0xff, 0xff, 0xff));

    draw_point(window, f32x2_new(100, 100), color_white());
    draw_point(window, f32x2_new(100, 100) + f32x2_new(10, 0), color_white());
    draw_point(window, f32x2_new(100, 100) * 1.25f, color_white());

    draw_aabb(window, aabb_new(f32x2_new(50, 50), f32x2_new(100, 100)), color_black());
}

//! EOF

