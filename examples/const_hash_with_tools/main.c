#include <stdio.h>
#include <stdint.h>

#define const_hash(str) 0
#define const_hash_v(str, x) (x)

uint64_t hash(const char* str, size_t len)
{
    uint64_t hash = 14695981039346656037ULL;

    for (int i = 0; i < len; i++)
    {
        hash ^= str[i];
        hash *= 1099511628211ULL;
    }

    return hash;
}

int main(void)
{
    const uint64_t hash_0 = hash("test", 4);
    const uint64_t hash_1 = const_hash("test");

    printf("hash_0 = %llu\n", hash_0);
    printf("hash_1 = %llu\n", hash_1);

    switch (hash("test", 4))
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
