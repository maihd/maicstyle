#include <stdio.h>

/// Print Celsius-Fahrenheit table
/// for celsius = -20, ..., 150;
/// floating-point version
int main()
{
    const int lower = -20;
    const int upper = 150;
    const int step  = 10;

    printf("| Celsius |   Fahr  |\n");
    printf("|---------|---------|\n");
    for (float celsius = (float)lower; celsius <= (float)upper; celsius += step)
    {
        const float fahr = celsius * 1.8f + 32.0f;
        printf("|   %3.0f   |  %5.1f  |\n", celsius, fahr);
    }

    return 0;
}

//! EOF

