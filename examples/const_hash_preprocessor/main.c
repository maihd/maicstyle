#include <stdio.h>
#include <stdint.h>

#include "const_hash_pp.h"

uint64_t hash(const char* str, size_t length)
{
    uint64_t hash = CONST_HASH_OFFSET_BASIS;

    for (int i = 0; i < length; i++)
    {
        hash ^= str[i];
        hash *= CONST_HASH_PRIME;
    }

    return hash;
}

int main(void)
{
    const char content[] = "test";

    const uint64_t hash_0 = hash(content, sizeof(content) - 1);
    const uint64_t hash_1 = const_hash("test");

    printf("hash_0 = %llu\n", hash_0);
    printf("hash_1 = %llu\n", hash_1);

    switch (hash(content, sizeof(content) - 1))
    {
        case const_hash("test"):
            printf("Test success\n");
            break;

        default:
            printf("Test failed\n");
            break;
    }

    return 0;
}

//! EOF
