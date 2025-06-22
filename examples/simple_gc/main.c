#define GC_IMPLEMENTATION
#include "gc.h"

#include <stdio.h>

int main()
{
    int* safe_int = gc_new(int, NULL);
    gc_mark(safe_int);

    *safe_int = 10;
    printf("safe_int value: %d\n", *safe_int);
    printf("Allocated count: %zu\n\n", gc_allocated_count());

    // No memory free here, just unmarked
    gc_collect();
    printf("safe_int value after gc_collect: %d\n", *safe_int);
    printf("Allocated count after gc_collect: %zu\n\n", gc_allocated_count());
    
    // Still print 10, because free(entry) do no rewrite memory
    // And deference the old pointer is undefined behaviour
    gc_collect();
    printf("safe_int value after gc_collect again: %d\n", *safe_int);
    printf("Allocated count after gc_collect again: %zu\n", gc_allocated_count());

    return 0;
}

//! EOF
