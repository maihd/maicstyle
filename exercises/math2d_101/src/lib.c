#include <math.h>
#include <stdio.h>

#include "HotDylibApi.h"

#include "common.h"
#include "types.h"
#include "aabb.h"
#include "vector.h"


f32x2 world_to_screen(f32x2 p)
{
    const f32 half_screen_width = 160.0f;
    const f32 half_screen_height = 120.0f;
    return f32x2_new(p.x, -p.y) + f32x2_new(half_screen_width, half_screen_height);
}


void draw_point(Tigr* window, f32x2 p, TPixel color)
{
    p = world_to_screen(p);
    tigrPlot(window, (int)p.x, (int)p.y, color);
}


TPixel color_white(void)
{
    return tigrRGB(0xff, 0xff, 0xff);
}


TPixel color_black(void)
{
    return tigrRGB(0x0, 0x0, 0x0);
}


TPixel color_red(void)
{
    return tigrRGB(0xFF, 0, 0);
}


TPixel color_green(void)
{
    return tigrRGB(0, 0xFF, 0);
}


TPixel color_blue(void)
{
    return tigrRGB(0, 0, 0xFF);
}


void draw_line(Tigr* window, f32x2 p0, f32x2 p1, TPixel color)
{
    p0 = world_to_screen(p0);
    p1 = world_to_screen(p1);
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
    draw_line(window, p3, p4 + f32x2_new(0, 1), color);
}


static AABB red_box;
static AABB blue_box;


HOTDYLIB_EXPORT void* INIT_FN(void* data, HotDylibState newState, HotDylibState oldState)
{
    red_box = aabb_new(f32x2_new(-25.0f, -25.0f), f32x2_new(25.0f, 25.0f));
    blue_box = aabb_new(f32x2_new(-25.0f, -25.0f), f32x2_new(25.0f, 25.0f));

    return nullptr;
}


static f32 t = 0.0f;
static f32 dt = 0.0f;

DEFINE_UPDATE_FN(window)
{
    dt = tigrTime();
    t += dt;
}


DEFINE_DRAW_FN(window)
{
// Ex1
//     tigrLine(window, 0, 0, 100, 100, tigrRGB(0xff, 0xff, 0xff));
//     draw_line(window, f32x2_new(0, 0), f32x2_new(30, 200), tigrRGB(0xff, 0xff, 0xff));

//     draw_point(window, f32x2_new(100, 100), color_white());
//     draw_point(window, f32x2_new(100, 100) + f32x2_new(10, 0), color_white());
//     draw_point(window, f32x2_new(100, 100) * 1.25f, color_white());

// Ex2
//     AABB aabb = aabb_new(f32x2_new(60, 60), f32x2_new(270, 180));
//     f32x2 offset = f32x2_new(cosf(t), sinf(t)) * 50.0f;

//     aabb.min -= offset;
//     aabb.max += offset;

//     draw_aabb(
//         window,
//         aabb,
//         color_white()
//     );

// Ex3
    red_box.min += f32x2_new(15.0f, 0) * dt;
    red_box.max += f32x2_new(15.0f, 0) * dt;
    blue_box.min += f32x2_new(0, 15.0f) * dt;
	blue_box.max += f32x2_new(0, 15.0f) * dt;
	draw_aabb(window, red_box, color_red());
	draw_aabb(window, blue_box, color_blue());
}

//! EOF

