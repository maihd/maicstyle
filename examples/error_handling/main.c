#include <stdio.h>

typedef struct IntParsed
{
    int value;
    int ok;
} IntParsed;

IntParsed parse_int(const char* str)
{
    int c, value = 0;
    while ((c = *str++) != 0)
    {
        if (c > '9' || c < '0')
        {
            return (IntParsed){
                .value = 0,
                .ok = 0
            };
        }

        value = value * 10 + (c - '0');
    }

    return (IntParsed){
        .value = value,
        .ok = 1
    };
}

int main(void)
{
    printf("Error handling example\n");

    const char* str0 = "100";
    const IntParsed int_parsed_0 = parse_int(str0);
    if (int_parsed_0.ok)
    {
        printf("Parse '%s' success: %d\n", str0, int_parsed_0.value);
    }
    else
    {
        printf("Failed to parse: %s\n", str0);
    }

    const char* str1 = "100a";
    const IntParsed int_parsed_1 = parse_int(str1);
    if (int_parsed_1.ok)
    {
        printf("Parse '%s' success: %d\n", str1, int_parsed_1.value);
    }
    else
    {
        printf("Failed to parse: %s\n", str1);
    }

    return 0;
}

//! EOF


