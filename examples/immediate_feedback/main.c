#include <stdio.h>
#include <raylib.h>
#include "HotDylib.h"

int main()
{
    printf("Immediate Feedback Demo\n");
    printf("-----------------------\n");

    InitWindow(800, 600, "Immediate Feedback Demo");
    SetTargetFPS(60);

    HotDylib* dylib = HotDylibOpen("lib.dll", "LibEntry");

    typedef void (*UpdateFn)(float dt);
    typedef void (*DrawFn)();

    UpdateFn updateFn = NULL;
    DrawFn drawFn = NULL;

    while (!WindowShouldClose())
    {
        if (updateFn != NULL)
        {
            updateFn(GetFrameTime());
        }

        HotDylibState state = HotDylibUpdate(dylib);
        switch (state)
        {
            case HOTDYLIB_INIT:
            case HOTDYLIB_RELOAD:
                updateFn = (UpdateFn)HotDylibGetSymbol(dylib, "Update");
                drawFn = (DrawFn)HotDylibGetSymbol(dylib, "Draw");
                break;

            case HOTDYLIB_QUIT:
            case HOTDYLIB_UNLOAD:
                updateFn = NULL;
                drawFn = NULL;
                break;

            default:
                break;
        }

        BeginDrawing();
        {
            if (drawFn != NULL)
            {
                drawFn();
            }
        }
        EndDrawing();
    }

    HotDylibFree(dylib);
    CloseWindow();
    return 0;
}
