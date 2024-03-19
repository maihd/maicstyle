#include <stdio.h>

#include "HotDylibApi.h"
#include "common.h"

HOTDYLIB_EXPORT void* INIT_FN(void* data, HotDylibState newState, HotDylibState oldState)
{
    return nullptr;
}

DEFINE_UPDATE_FN(window)
{

}

DEFINE_DRAW_FN(window)
{
    tigrPrint(window, tfont, 120, 110, tigrRGB(0xff, 0xff, 0xff), "Hello world 2!");
}

//! EOF

