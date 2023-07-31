#include <stdio.h>

/// Print Fahrenheit-Celsius table
/// for fahr = 0, 20, ..., 300;
/// floating-point version
int main()
{
    const int lower = 0;
    const int upper = 300;
    const int step  = 20;

    printf("| Fahr | Celsius |\n");
    printf("|------|---------|\n");
    for (float fahr = (float)lower; fahr <= (float)upper; fahr += step)
    {
        const float celsius = (5.0f / 9.0f) * (fahr - 32.0f);
        printf("| %4.0f | %7.1f |\n", fahr, celsius);
    }

    return 0;
}

//! EOF

