#include <stdio.h>
#include <stdint.h>

static uint32_t strhash(const char* str);

typedef struct HashIndexor
{
    uint32_t*   hashes;
    int32_t*    indices;

    int32_t*    entries;
    int32_t*    next_entries;
    
    int32_t     count;
    int32_t     capacity;
    int32_t     entry_count;
} HashIndexor;

static int32_t find_index(const HashIndexor* hash_indexor, uint32_t hash)
{
    int32_t entry_index = (int32_t)(hash % (uint32_t)hash_indexor->entry_count);
    int32_t entry = hash_indexor->entries[entry_index];
    while (entry > -1)
    {
        if (hash_indexor->hashes[entry] == hash)
        {
            return hash_indexor->indices[entry];
        }

        entry = hash_indexor->next_entries[entry];
    }

    return -1;
}

int main()
{
    // Preallocated memory
    // This will prove that our HashIndexor is openned for custom operations

    enum { DATA_CAPACITY = 8, ENTRY_COUNT = 8 };

    uint32_t    hashes[DATA_CAPACITY];
    int32_t     indices[DATA_CAPACITY];
    int32_t     entries[ENTRY_COUNT];
    int32_t     next_entries[DATA_CAPACITY];

    const char* keys[] = { "key1", "key2", "key3" };
    const char* values[] = { "value1", "value2", "value3" };

    for (int i = 0; i < ENTRY_COUNT; i++)
    {
        entries[i] = -1;
    }

    for (int i = 0; i < DATA_CAPACITY; i++)
    {
        hashes[i] = (uint32_t)-1;
        indices[i] = -1;
        next_entries[i] = -1;
    }

    HashIndexor hash_indexor = {
        .hashes = hashes,
        .indices = indices,
        
        .entries = entries,
        .next_entries = next_entries,

        .count = 0,
        .capacity = DATA_CAPACITY,
        .entry_count = sizeof(entries) / sizeof(entries[0])
    };

    // Add values
    for (int i = 0; i < (sizeof(keys) / sizeof(keys[0])); i++)
    {
        const uint32_t hash = strhash(keys[i]);
        
        const uint32_t entry_index = hash % (uint32_t)hash_indexor.entry_count;
        if (hash_indexor.entries[entry_index] > -1)
        {
            // Resolving entry collision here
        }
        
        const uint32_t entry = hash_indexor.count++;
        hash_indexor.entries[entry_index] = entry;

        hash_indexor.hashes[entry] = hash;
        hash_indexor.indices[entry] = i;
    }

    // Tests
    for (int i = 0; i < (sizeof(keys) / sizeof(keys[0])); i++)
    {
        const char*     key         = keys[i];
        const uint32_t  hash        = strhash(key);
        const int32_t   value_index = find_index(&hash_indexor, hash);

        printf("find_index(\"%s\") = %d\n", key, value_index);
        printf("values[\"%s\"] = \"%s\"\n\n", key, values[value_index]);
    }

    return 0;
}


// Pseudo hash functions
uint32_t strhash(const char* str)
{
    uint32_t h = 0;

    uint32_t c;
    while ((c = *str++))
    {
        h += c;
        h |= (c << 8);
        h ^= (c << 16);
        h *= c;
        h |= (c << 24);
    }

    return h;
}

//! EOF
