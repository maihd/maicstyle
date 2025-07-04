# Examples data structures designing that use MaiCStyle to programming


## Building
All examples should be only contains main.c only and can be compile with GCC or Clang.
In special case, build scripts were provided.


## Contents
- [Good taste linked list](/linked_list)
- [Centralized memory allocations (Arena only, no abstract allocators)](/memory_allocations)


## Common data structures
- Array: buffer, count, capacity
- Sparse set/array: array with holes/unused items
- Vector: resizable array, best for dynamic usages, may cause problem in hot loops, should avoid to use it as huge containers
- Huge array: sparse set + free list + handle lookup, avoid realloc (scaling to big when resizing)
- Linked list: first node, each node have store a data to access next node (maybe one of pointer, index, offset, handle)
- Free list: like linked list, for fast lookup unused items, but more lightweight, some time just use small data type (uint16, uint32) for index or offset of unused items
- Lookup array: simple array store index/offset for spareset array
- Handle lookup array: for weak reference fast lookup
- Hash indexor: fast lookup of index/address of actual array, use open SoA to fast iteration through keys, can use SIMD for acceleration
- Hash link: linear chaining hash table, from hash to find index/pointer/handle. Acceptable performance in linear allocated memory (item sit near each others in address space)


## Abstract data structures (from book)
- Stack and queue: an abstractions of array or list.


## Caching data structures
- Ring buffer: usually non-resizable, infinite circular loop for accessing items
- LRU and MRU cached: implement with ring buffer, or queue


## Memory access patterns
- Offset: result of pointer address subtractions
- Pointer: address to memory
- Index: offset from first item of array, with the help of the compiler to calculate pointer address
- Handle: ganeration + index, for weak reference, still fast lookup with extra step of checking generation, may cause generations collision in frequently create/destroy loop
- Hash: numbeer present of the result after hashing a block of data (iterate all items, each item is hashed and combine to the results), good for lookup in complex storage
- Id: a data to present identify of data object. In runtime, use hash or handle are good enough. In persistent, real world data object, guid or uuid solve this problem
- Name: a human readable identify of data object, should store as string


## Compare Id and hash/handle
- Id: does not change when data change, storage change. Id are given when creation. Persistent until destroy data object.
- Hash: depend on data. Data changed, hash changed.
- Handle: depend on storage, given when add item to storage.


## Compare Id and Name
- Id: not human readable, given by the system
- Name: human readable, given by human


## Suggestions
- Should avoid contain container into data object
- Use huge array for system
- Linked list and hash link for parsing data from text file (which linear allocator for acceptable cache friendly)
- Array for bulk data, batch processing
