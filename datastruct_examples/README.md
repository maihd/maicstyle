# Examples data structures designing that use MaiCStyle to programming


## Building
All examples should be only contains main.c only and can be compile with GCC or Clang.
In special case, build scripts were provided.


## Contents
- [Good taste linked list](/linked_list)
- [Centralized memory allocations (Arena only, no abstract allocators)](/memory_allocations)


## Data structures
- Array: buffer, count, capacity
- Sparse set/array: array with holes/unused items
- Vector: resizable array, best for dynamic usages, may cause problem in hot loops, should avoid to use it as huge containers
- Huge array: sparse set + free list + handle lookup, avoid realloc (scaling to big when resizing)
- Linked list: first node, each node have store a data to access next node (maybe one of pointer, index, offset, handle)
- Free list: like linked list, for fast lookup unused items, but more lightweight, some time just use small data type (uint16, uint32) for index or offset of unused items
- Lookup array: simple array store index/offset for spareset array


## Memory access patterns


## Suggestions
- Should avoid contain container into data object
- Use huge array for system
- Linked list and hash link for parsing data from text file (which linear allocator for acceptable cache friendly)
- Array for bulk data, batch processing