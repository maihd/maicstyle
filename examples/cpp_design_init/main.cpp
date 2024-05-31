// C++ Designated Initializers
// Designated Initializers is a feature that was added in C++20. It allows you to initialize a struct or class with a specific member without having to initialize all the members in the struct or class. This is similar to the designated initializers feature in C99.
// Which also work as Clang 11.0.0 and GCC 10.1.0
// In this example, we will see how to use designated initializers in C++.

#include <stdio.h>


struct Vec2
{
    float x;
    float y;
};


int main()
{
    Vec2 v = Vec2{ .x = 1, .y = 2 };
    printf("v.x = %f, v.y = %f\n", v.x, v.y); 
    return 0;
}

//! EOF
