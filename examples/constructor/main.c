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


vec2 vec2_new0(void)
{
    vec2 v = { 0, 0 };
    return v;
}


#ifdef __cplusplus
vec2 vec2_new(float s)
{
    return vec2_new1(s);
}
vec2 vec2_new(void)
{
    return vec2_new0();
}
#define vec2(...) vec2_new(__VA_ARGS__)
#else
#define vec2_(args, x, y, ...)      \
    _Generic((x)                    \
        , vec2: vec2_new0           \
        , default:  _Generic((y)    \
            , vec2: vec2_new1       \
            , default: vec2_new)) args

// pass copy of args as the first argument
// add vec2 value, only its type matters
// add dummy `~` argument to ensure that `...` in `vec2_` catches something
#define vec2(...) vec2_((__VA_ARGS__), __VA_ARGS__, (vec2){0}, (vec2){0}, ~)
#endif


typedef struct vec3
{
    float x, y, z;
} vec3;


vec3 vec3_new(float x, float y, float z)
{
    vec3 v = { x, y, z};
    return v;
}


vec3 vec3_new1(float s)
{
    vec3 v = { s, s, s };
    return v;
}


vec3 vec3_new0(void)
{
    vec3 v = { 0, 0, 0 };
    return v;
}


#ifdef __cplusplus
vec3 vec3_new(float s)
{
    return vec3_new1(s);
}
vec3 vec3_new(void)
{
    return vec3_new0();
}
#define vec3(...) vec3_new(__VA_ARGS__)
#else
#define vec3_(args, x, y, ...)      \
    _Generic((x)                    \
        , vec3: vec3_new0           \
        , default:  _Generic((y)    \
            , vec3: vec3_new1       \
            , default: vec3_new)) args

// pass copy of args as the first argument
// add vec3 value, only its type matters
// add dummy `~` argument to ensure that `...` in `vec3_` catches something
#define vec3(...) vec3_((__VA_ARGS__), __VA_ARGS__, (vec3){0}, (vec3){0}, ~)
#endif


int main()
{
    vec2 v = vec2(1, 2);
    vec2 v1 = vec2(1);
    vec2 v0 = vec2();

    printf("v = { %f, %f }\n", v.x, v.y);
    printf("v1 = { %f, %f }\n", v1.x, v1.y);
    printf("v0 = { %f, %f }\n", v0.x, v0.y);

    vec3 v3 = vec3(1, 2, 3);
    vec3 v3_1 = vec3(1);
    vec3 v3_0 = vec3();

    printf("v3 = { %f, %f, %f }\n", v3.x, v3.y, v3.z);
    printf("v3_1 = { %f, %f, %f }\n", v3_1.x, v3_1.y, v3_1.z);
    printf("v3_0 = { %f, %f, %f }\n", v3_0.x, v3_0.y, v3_0.z);

    return 0;
}

// !EOF

