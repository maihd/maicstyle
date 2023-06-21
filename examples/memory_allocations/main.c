#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Arena
{
    void*   page;
    int32_t pageHead;
    int32_t pageTail;
    int32_t pageSize;
} Arena;

void Arena_Init(Arena* arena, int32_t pageSize)
{
    // Verify user input, use int32_t to maximize flexibility
    assert(arena != NULL);
    assert(pageSize > 0);

    // Use malloc to simply demonstrate the algorithm
    // In real-world application, may need virtual space memory
    void* page = malloc((size_t)pageSize);

    // Fast-crash when out of memory, easier to debug
    assert(page != NULL);

    // Actual init
    arena->page     = page;
    arena->pageSize = pageSize;
    arena->pageHead = 0;
    arena->pageTail = pageSize;
}

void Arena_Deinit(Arena* arena)
{
    // Verify arena
    assert(arena != NULL);
    assert(arena->page != NULL);
    assert(arena->pageSize > 0);

    // Actual deinit
    arena->page     = NULL;
    arena->pageSize = 0;
    arena->pageHead = 0;
    arena->pageTail = 0;
}

// Instead of use Alloc name, we use Acquire because there are no inner allocations in Arena
void* Arena_Acquire(Arena* arena, int32_t size, int32_t alignment)
{
    // Not support alignment now
    (void)alignment;

    // Immediate crash instead of return error
    // @todo: add flags to make Arena auto-grow 
    assert(arena->pageTail - arena->pageHead >= size);

    // Simply increase pageHead and single pointer
    void* ptr = (uint8_t*)arena->page + arena->pageHead;
    arena->pageHead += size;
    return ptr;
}

// No free allocations in arena
// @todo: Add stack-based memory allocations, support free allocations in tail position
//void Arena_Free(Arena arena);

// Extend/utils functions
const char* Arena_FormatString(Arena* arena, const char* format, ...)
{
    va_list args;
    va_start(args, format);

    // Get size of buffer
    //@todo: this code is not work to calculate string size 
    //  (int32_t)vsprintf(NULL, format, args);
    int32_t size = 1024;
    assert(size > 0); 
    
    // Allocate buffer
    char* buffer = Arena_Acquire(arena, size, 0);

    // Do the actual format string
    vsprintf(buffer, format, args);
    // assert(size == );

    va_end(args);

    // Return the buffer
    return buffer;
}

int main()
{
    printf("Simple memory allocations\n");
    printf("-------------------------\n");

    // printf("Init arena\n");
    Arena arena;
    Arena_Init(&arena, 4096);

    // printf("Format string\n");
    const char* greeting = Arena_FormatString(&arena, "Hello world, I'm %s", "MaiHD");
    printf("Greeting: %s\n", greeting);

    // printf("Deinit arena\n");
    Arena_Deinit(&arena);
    return 0;
}

