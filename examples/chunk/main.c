#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

#define container_of(ptr, Type, member)                     \
    ({                                                      \
        const typeof(((Type*)0)->member)* __mptr = ptr;     \
        (Type*)((uint8_t*)__mptr - offsetof(Type, member)); \
    })

int main()
{
    struct Test
    {
        int value;
    };

    int v = 10;
    struct Test* test = container_of(&v, struct Test, value);

    printf("v = %d\n", v);
    printf("test->value = %d\n", test->value);

    return 0;
}

//! EOF

