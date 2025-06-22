#pragma once

#include <stdint.h>
#include <stddef.h>

typedef void (*GCDtorFn)(void*);

typedef struct GCHeader
{
    uint32_t            flags;
    GCDtorFn            dtor;
    struct GCHeader*    next;
} GCHeader;


void*   gc_alloc(size_t size, GCDtorFn dtor);
void    gc_mark(void* ptr);
void    gc_collect(void);
size_t  gc_allocated_count(void);


#define gc_new(Type, dtor) ((Type*)gc_alloc(sizeof(Type), dtor))

#if defined(GC_IMPLEMENTATION)
#include <stdio.h>
#include <stdlib.h>

static GCHeader*    s_gc_head = NULL;
static size_t       s_gc_alloc_count = 0;

void* gc_alloc(size_t size, GCDtorFn dtor)
{
    GCHeader* header = malloc(sizeof(GCHeader) + size);
    if (!header) return NULL;
    
    header->flags = 0;
    header->dtor = dtor;
    header->next = s_gc_head;

    s_gc_head = header;
    s_gc_alloc_count++;
    
    return (void*)(header + 1); // Return memory after header
}


void gc_mark(void* ptr) 
{
    if (!ptr) return;
    GCHeader* header = ((GCHeader*)ptr) - 1;
    header->flags = 1;
}


static void gc_sweep() 
{
    GCHeader** current = &s_gc_head;
    while (*current) 
    {
        GCHeader* entry = *current;
        
        if (!entry->flags) 
        {
            // Unmarked - destroy it
            printf("Unmarked\n");
            *current = entry->next;
            s_gc_alloc_count--;

            if (entry->dtor) 
            {
                entry->dtor(entry + 1);
            }
            free(entry);
        } 
        else 
        {
            // Keep it, reset mark for next collection
            printf("Keep\n");

            entry->flags = 0;
            current = &entry->next;
        }
    }
}

void gc_collect() 
{
    // In more complex systems, you'd walk object graph here
    // For your case, we rely on explicit gc_mark() calls
    
    gc_sweep();
}


size_t gc_allocated_count() 
{
    return s_gc_alloc_count;
}
#endif

//! EOF
