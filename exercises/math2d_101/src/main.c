#include <stdio.h>

#include "tigr.h"

int main()
{
    printf("Math 2D 101 - v1.0\n");

    Tigr* window = tigrWindow(320, 240, "Math 2D 101", 0);

    while (!tigrClosed(window))
    {
        tigrClear(window, tigrRGB(0x80, 0x90, 0xa0));
        tigrPrint(window, tfont, 120, 110, tigrRGB(0xff, 0xff, 0xff), "Hello world!");
        tigrUpdate(window);
    }

    tigrFree(window);
    return 0;
}

//! EOF

