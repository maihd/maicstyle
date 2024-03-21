#include <stdio.h>
#include <stdlib.h>

#include "tigr.h"
#include "HotDylib.h"
#include "HotDylibEx.h"

#include "common.h"

int main()
{
    printf("Math 2D 101 - v1.0\n");

    HotDylib* lib = HotDylibOpen("lib.dll", INIT_FN_NAME);

    Tigr* window = tigrWindow(320, 240, "Math 2D 101", 0);

    UpdateFn* update_fn = nullptr;
    DrawFn* draw_fn = nullptr;

    HotDylibFileTime dir = { 0, "src/lib.c" };
    HotDylibWatchFiles(&dir, 1);

    while (!tigrClosed(window))
    {
        if (HotDylibWatchFiles(&dir, 1))
        {
            printf("Source changed, rebuild lib with build_lib.bat\n");
            system("build_lib.bat");
            HotDylibWatchFiles(&dir, 1);
            continue;
        }

        HotDylibState state = HotDylibUpdate(lib);
        switch (state)
        {
            case HOTDYLIB_INIT:
            case HOTDYLIB_RELOAD:
                update_fn = (UpdateFn*)HotDylibGetSymbol(lib, UPDATE_FN_NAME);
                draw_fn = (DrawFn*)HotDylibGetSymbol(lib, DRAW_FN_NAME);
                break;

            case HOTDYLIB_QUIT:
            case HOTDYLIB_UNLOAD:
                update_fn = nullptr;
                draw_fn = nullptr;
                break;

            default:
                break;
        }

        if (update_fn != nullptr)
        {
            update_fn(window);
        }

        tigrClear(window, tigrRGB(0x80, 0x90, 0xa0));
        if (draw_fn != nullptr)
        {
            draw_fn(window);
        }
        tigrUpdate(window);
    }

    tigrFree(window);
    HotDylibFree(lib);
    return 0;
}

//! EOF

