/// Sometime you will face the design problem like GLSL math
/// that require constructor for data type: vec2(...)
/// constructor may help your code cleaner
/// But C does not support constructor
/// And C++ constructor broke the POD, add abstraction costs
/// One solution is: Macros
///     - C: use _Generic to select named function overloading
///     - C++: just use function overloading


#include <stdio.h>


typedef struct vec2
{
    float x, y;
} vec2;


vec2 vec2_new(float x, float y)
{
    vec2 v = { x, y };
    return v;
}


vec2 vec2_new1(float s)
{
    vec2 v = { s, s };
    return v;
}


#ifdef __cplusplus
vec2 vec2_new(float s)
{
    return vec2_new1(s);
}
#define vec2(...) vec2_new(__VA_ARGS__)
#else
#define vec2_(args, x, y, ...)  \
    _Generic((y)                \
        , vec2: vec2_new1       \
        , default: vec2_new) args

// pass copy of args as the first argument
// add void value, only its type matters
// add dummy `~` argument to ensure that `...` in `foo_` catches something
#define vec2(...) vec2_((__VA_ARGS__), __VA_ARGS__, (vec2){0}, ~)
#endif


int main()
{
    vec2 v = vec2(1, 2);
    vec2 v1 = vec2(1);

    printf("v = { %f, %f }\n", v.x, v.y);
    printf("v1 = { %f, %f }\n", v1.x, v1.y);

    return 0;
}

// !EOF

