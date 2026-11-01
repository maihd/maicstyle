# API design for procedural code

## Large Arrays of Things
- Thing is PoD, fixed size, contains no dynamic data
- Things is container of Thing, define custom access pattern, processing, ...
- Thing can index of parent, first child, last child, next sibling, prev sibling for hierarchy.
- Index can replace with Handle. Things can use Handle_Map to store thing.
That's enough, we no need generics code here.
```C
struct ThingHandle
{
    uint32_t index;
    uint32_t generation;
};

struct Thing
{
    // Properties


    // Hierarchy
    ThingHandle parent;
    ThingHandle firstChild;
    ThingHandle lastChild;
    ThingHandle nextSibling;
    ThingHandle prevSibling;
};


struct Things
{
    Thing   items[1024];
    bool    used[1024];
};


ThingHandle ThingsAdd(Things* things, Thing thing);
bool        ThingsRemove(Things* things, ThingHandle handle);
Thing*      ThingsGet(Things* things, ThingHandle handle);
```

## Simple and easy use assets registry
- I call this registry, not database is simple, just for find asset id.
- This solution require no generics or template
- This solution does not do dynamic allocations, so it is more simpler.
```C
#define HASH_INDEXOR_MAX_NUMS       1024 // If you need more assets, use more registry
#define HASH_INDEXOR_NUM_BUCKETS    64
#define HASH_INDEXOR_BUCKET_SIZE    (HASH_INDEXOR_MAX_NUMS / HASH_INDEXOR_NUM_BUCKETS)

#define hi_assert_no_collisions(hi, hash) assert(hi_find(hi, hash) == -1)

struct Hash_Indexor
{
    uint64_t    hashes[HASH_INDEXOR_MAX_NUMS];
    int32_t     indices[HASH_INDEXOR_MAX_NUMS];
    int32_t     num_per_buckets[HASH_INDEXOR_NUM_BUCKETS];
    int32_t     num_items;
};

int hi_bucket_idx(uint64_t hash)
{
    return hash / HASH_INDEXOR_BUCKET_SIZE;
    // We can do hash >> __builtin_ctz(HASH_INDEXOR_BUCKET_SIZE)
    // for more performance, required bucket size is power of twos
    // some compiler will do this optimize, but sometime you want control
}

int hi_item_idx_to_bucket_idx(int item_idx)
{
    return item_idx % HASH_INDEXOR_BUCKET_SIZE;
    // We can do hash & (HASH_INDEXOR_BUCKET_SIZE)
    // for more performance, required bucket size is power of twos
    // some compiler will do this optimize, but sometime you want control
}

int32_t hi_find_slot(const Hash_Indexor* hi, uint64_t hash)
{
    int bucket_idx          = hi_bucket_idx(hash);
    int bucket_num_items    = hi->num_per_buckets[bucket_idx];
    for (int i = 0; i < bucket_num_items; i += 1)
    {
        int item_idx = bucket_idx * HASH_INDEXOR_BUCKET_SIZE + i;
        if (hi->hashes[item_idx] == hash)
        {
            return item_idx;
        }
    }

    return -1;
    // You can use '0' as sentinel for index, if you wanna support no crash code path
}

int hi_add(Hash_Indexor* hi, uint64_t hash, int32_t index)
{
    hi_assert_no_collisions(hi, hash);

    int bucket_idx          = hi_bucket_idx(hash);
    int bucket_num_items    = hi->num_per_buckets[bucket_idx];

    assert(bucket_num_items < HASH_INDEXOR_BUCKET_SIZE);

    int item_idx            = bucket_idx * HASH_INDEXOR_BUCKET_SIZE + 1;

    hi->hashes[item_idx]    = hash;
    hi->indices[item_idx]   = index;

    hi->num_per_buckets[bucket_idx] += 1;
    hi->num_items                   += 1;

    return item_idx;
}

int32_t hi_remove(Hash_Indexor* hi, uint32_t hash)
{
    int item_idx = hi_find_slot(hi, hash);
    if (item_idx > -1)
    {
        int32_t index               = hi->indices[item_idx];
        int32_t bucket_idx          = hi_bucket_idx(hash);
        int32_t bucket_num_items    = hi->num_per_buckets[bucket_idx];

        int32_t item_idx_in_bucket  = hi_item_idx_to_bucket_idx(bucket_idx);

        hi->hashes[item_idx]        = hi->hashes[bucket_num_items - 1];
        hi->indices[item_idx]       = hi->indices[bucket_num_items - 1];

        hi->num_per_buckets[bucket_idx] -= 1;
        hi->num_items                   -= 1;

        return index;
    }

    return -1;
    // You can use '0' as sentinel for index, if you wanna support no crash code path
}

int hi_set(Hash_Indexor* hi, uint32_t hash, int32_t index)
{
    int item_idx = hi_find_slot(hi, hash);
    if (item_idx > -1)
    {
        hi->indices[item_idx] = index;
        return item_idx;
    }

    return -1;
    // most case you should use hi_set and hi_add seperatedly
}

int32_t hi_get(const Hash_Indexor* hi, uint64_t hash)
{
    int item_idx = hi_find_slot(hi, hash);
    if (item_idx > -1)
    {
        return hi->indices[item_idx];
    }

    return -1;
    // You can use '0' as sentinel for index, if you wanna support no crash code path
}

// Usages

struct Assets_Entry
{
    uint64_t    hash;   // Assume we recalcuting hash by tools
    const char* path;   // Or runtime hashing based on path
};

enum Assets_Flags
{
    Assets_Flags_Invalid    = 0,
    Assets_Flags_Success    = 1 << 0,
};

struct Assets_Data
{
    Assets_Entry    entry;
    Assets_Flags    flags;      // For checking return assets_data state
    Texture         texture;    // For simple, we only support texture now
};

struct Assets
{
    Hash_Indexor    indexor;
    Assets_Data     datas[HASH_INDEXOR_MAX_NUMS];
    int32_t         num_items;
};

Assets_Data assets_load_texture(Assets* assets, Assets_Entry entry)
{
    int32_t idx = hi_get(&assets->indexor, entry.hash);
    if (idx == -1)
    {
        Texture texture = create_texture_from_path(entry.path);
        if (texture.id == 0) {
            Assets_Data data = {
                .flags = Assets_Flags_Invalid,
            };

            return data;
        }

        idx = assets->num_items;
        assets->num_items += 1;

        hi_add(assets, entry.hash, idx);

        assets->datas[idx] = (Assets_Data){
            .entry      = entry,
            .flags      = Assets_Flags_Success,
            .texture    = texture,
        };
    }

    return assets->data[idx];
}

// You can do unload easily, without any allocations or allocator
// My current game use this design, work very well, hot reloadable
```