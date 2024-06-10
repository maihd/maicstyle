/// C function with array as params
/// Work like C# params keyword
/// Underhood, with help of C99 compound expression


#include <stdio.h>

#define sum(...) sum_w_params(((const int[]){ __VA_ARGS__ }))
#define sum_w_params(params) sum_impl(sizeof(params) / sizeof((params)[0]), params) // space between function name and '(' is required

int sum_impl(int argc, const int argv[])
{
    int result = 0;

    for (int i = 0; i < argc; i++)
    {
        result += argv[i];
    }

    return result;
}


int main(int argc, const char* argv[])
{
    printf("sum(1, 2, 3) = %d\n", sum(1, 2, 3));

    return 0;
}


//! EOF
