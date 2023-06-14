#include <raylib.h>
#include "HotDylibApi.h"

HOTDYLIB_EXPORT void* LibEntry(void* data, HotDylibState newState, HotDylibState oldState)
{
    return 0;
}

HOTDYLIB_EXPORT void Update(float dt)
{

}

HOTDYLIB_EXPORT void Draw()
{
    ClearBackground(WHITE);
    DrawText("Hello world", 10, 10, 16, GRAY);
}
