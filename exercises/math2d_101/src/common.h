#pragma once

#include "tigr.h"

#ifndef __cplusplus
#define nullptr ((void*)0)
#endif

typedef void UpdateFn(Tigr* window);
typedef void DrawFn(Tigr* window);

#define __stringify_2(x) #x
#define __stringify(x) __stringify_2(x)

#define UPDATE_FN update
#define DRAW_FN draw
#define INIT_FN init

#define UPDATE_FN_NAME __stringify(UPDATE_FN)
#define DRAW_FN_NAME __stringify(DRAW_FN)
#define INIT_FN_NAME __stringify(INIT_FN)

#define DEFINE_UPDATE_FN(WINDOW) __declspec(dllexport) void UPDATE_FN(Tigr* WINDOW)
#define DEFINE_DRAW_FN(WINDOW) __declspec(dllexport) void DRAW_FN(Tigr* WINDOW)

//! EOF

