# Examples data structures designing that use MaiCStyle to programming
Guided for using and designing data structure. All come from other people and ideas.
Inspired by:
- Bitsquid Foundation library
- OdinLang
- Linux kernel codebase


## Building
All examples should be only contains main.c only and can be compile with GCC or Clang.
In special case, build scripts were provided.


## Contents
- [Good taste linked list](/linked_list)
- [Centralized memory allocations (Arena only, no abstract allocators)](/memory_allocations)


## Common data structures
- Array: fixed-size, can be known as compile-time
- Slice: buffer, count (commonly work as array view or string view)
- Sparse set/array: array with holes/unused items
- Vector/DynArray: resizable array, best for dynamic usages, may cause problem in hot loops, should avoid to use it as huge containers
- Fixed capacity vector: no resizable, but have count.
- Huge array: sparse set + free list + handle lookup, avoid realloc (scaling to big when resizing)
- Handle map: one solution for huge array problems.
- Linked list: first node, each node have store a data to access next node (maybe one of pointer, index, offset, handle)
- Free list: like linked list, for fast lookup unused items, but more lightweight, some time just use small data type (uint16, uint32) for index or offset of unused items
- Lookup array: simple array store index/offset for spareset array
- Handle lookup array: for weak reference fast lookup
- Hash indexor: fast lookup of index/address of actual array, use open SoA to fast iteration through keys, can use SIMD for acceleration
- Hash link: linear chaining hash table, from hash to find index/pointer/handle. Acceptable performance in linear allocated memory (item sit near each others in address space)


## Abstract data structures (from book)
- Stack and queue: an abstractions of array or list for special use case, maybe use ring buffer to avoid dynamic memory allocations. Or just simply an array, push/enqueue and clear after done:
    - If push/pop oftenly: array or list is naturely worked
    - If enqueue/dequeue oftenly: use ring buffer backed with array/list
    - If data only live in one frame (short live): clear_all after done
- Tree: to manage inherit relations of data object, also implement-depend to choose array/list.
- QuadTree or OctaTree: good for partition spacing use in physics and camera culling


## Caching data structures
- Ring buffer: usually non-resizable, infinite circular loop for accessing items
- LRU and MRU cached: implement with ring buffer, or queue
- Free list or Pool: storing pre-allocated and or after free (avoid calling malloc/free which is slow)


## Memory access patterns
- Offset: result of pointer address subtractions
- Pointer: address to memory
- Index: offset from first item of array, with the help of the compiler to calculate pointer address
- Handle: ganeration + index, for weak reference, still fast lookup with extra step of checking generation, may cause generations collision in frequently create/destroy loop
- Hash: number present of the result after hashing a block of data (iterate all items, each item is hashed and combine to the results), good for lookup in complex storage
- Id: a data to present identify of data object. In runtime, use hash or handle are good enough. In persistent, real world data object, guid or uuid solve this problem
- Name: a human readable identify of data object, should store as string
- StringId: a human readable identify, store as hash, in debug mode can store presented string


## Pointer, Index, Handle
- Pointer: direct access, unsafe, no lifetime, maybe dangling, non-serializable. Fastest (in theory).
- Index: indirect access, more safe but no lifetime, maybe dangling, serializable. Slower than pointer (in theory).
- Handle: indirect access, more safe, lifetime, no dangling, serializable. Slower than index (in theory).


## Compare Id and hash/handle
- Id: does not change when data change, storage change. Id are given when creation. Persistent until destroy data object.
- Hash: depend on data. Data changed, hash changed.
- Handle: depend on storage, given when add item to storage.

## Things
- A thing can be anythings: Entity, Actor, UI Widget
- Fixed size struct, only contains dump fields
- Trivial copyable
- Should have no pointer, only use indirect reference
```C++
enum class ThingKind : uint32_t // no need uint8_t or uint16_t, saved 2 or 3 bytes is not worth
{
    None,
    Player,
    Enemy_Goblin,
    Enemy_Orc,

    // If you do UI 
    UI_Button,
    UI_Text,
    UI_Slider,
};

enum ThingFlags : uint32_t // Fast turning on/off features/behaviours of Kind. Use uint64_t of BitSet if your required bigger set
{
    ThingFlags_None,
    // ThingFlags_Movable   = 1 << 0,
    // ThingFlags_AI_Input  = 1 << 1,
    // Blah blah
};

struct ThingHandle
{
    int32_t index;
    int32_t generation;
};

struct alignas(64) Thing // Cacheline commonly have size of 64 byte
{
    // Header
    ThingKind kind;             // offset 0
    ThingFlags flags;           // offset 4

    // Properties
    vec3 position;              // offset 8
    quat rotation;              // offset 24 (vec3 is simd)
    vec3 scale;                 // offset 40

    // Relationship
    ThingHandle parent;         // offset 56
    ThingHandle firstChild;     // offset 64
    ThingHandle lastChild;      // offset 72
    ThingHandle nextSibling;    // offset 80 
    ThingHandle prevSibling;    // offset 88

    // Padding, good for hot reloading, serialization
    char padding[160];          // offset 96
};

// You should control your thing size, 1KB is not too big
// Commonly 256 is big enough for most cases
static_assert(size_of(Thing) == 160, "Thing size is wrong"); 
```

## Compare Id and Name
- Id: not human readable, given by the system
- Name: human readable, given by human
- StringId: human readable, but fast as runtime, usually place in code


## Suggestions
- Should avoid contain container into data object (thing, entity, actor)
- Use huge array for system
- Linked list and hash link for parsing data from text file (which linear allocator for acceptable cache friendly)
- Array for bulk data, batch processing
- Slice for passing data around


## More complex data structures
I usually done touch theses data structures:
- Bounding Volume Hierarchy (BVH), commonly use in high performance system. Like physics and graphics.
- Binary space partition (BSP), famous in Doom 1.