#include <stdio.h>

#define __macro_var_2(i, l)   i ## l
#define __macro_var_1(i, l)   __macro_var_2(i, l)
#define __macro_var(i)        __macro_var_1(i, __LINE__)
#define __defer(expr)         for (int __macro_var(__i_) = 0; __macro_var(__i_) == 0; __macro_var(__i_)--, expr)
#define __scope(init, deinit) for (int __macro_var(__i_) = (init, 0); __macro_var(__i_) == 0; __macro_var(__i_)--, deinit)


int main()
{
    __defer(printf("__defer showcase: End of block!\n"))
    {
        printf("__defer showcase: Start of block!\n");
    }

    printf("-------------------------------\n");

    __scope(
        printf("__scope showcase: Init phrase!\n"),
        printf("__scope showcase: Deinit phrase!\n")
    )
    {
        printf("__scope showcase: Do work...\n");
    }

    return 0;
}


//! EOF
