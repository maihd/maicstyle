#include <stdio.h>

#define macro_var_2(i, l)   i ## l
#define macro_var_1(i, l)   macro_var_2(i, l)
#define macro_var(i)        macro_var_1(i, __LINE__)
#define defer(expr)         for (int macro_var(__i_) = 0; macro_var(__i_) == 0; macro_var(__i_)--, expr)
#define scope(init, deinit) for (int macro_var(__i_) = (init, 0); macro_var(__i_) == 0; macro_var(__i_)--, deinit)


int main()
{
    defer(printf("defer showcase: End of block!\n"))
    {
        printf("defer showcase: Start of block!\n");
    }

    printf("-------------------------------\n");

    scope(
        printf("scope showcase: Init phrase!\n"),
        printf("scope showcase: Deinit phrase!\n")
    )
    {
        printf("scope showcase: Do work...\n");
    }

    return 0;
}
