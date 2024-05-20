#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/// Arena
/// Simple implementation which is the best for this example (not in practice/production)
typedef struct Arena
{
    size_t  head;
    size_t  tail;

    void*   data;
    size_t  size;
} Arena;


/// ListNode
/// Generic node data structure implementation for using Linked List
typedef struct ListNode
{
    struct ListNode* next;
} ListNode;


/// LIST_NULL_NODE 
/// NULL in C is void*, which is untyped, may caused compile-error when using macro
/// For more robust code, we can use the address of a predefined static variables node
/// which will prevent null-pointer access, reduce null-pointer check before access node
#define LIST_NULL_NODE ((ListNode*)0)


/// container_of
/// The famous Linux kernel's macro
/// This macro is helpful when cast Member to Super data structure
/// Details explain: http://www.kroah.com/log/linux/container_of.html
#define container_of(ptr, TSuper, member) ((TSuper*)((uint8_t*)(ptr) - offsetof(TSuper, member)))


/// node_entry
/// Another famous Linux kernel's macro
/// This macro is helpful when cast ListNode to Entry data structure
#define node_entry(ptr, Entry) container_of(ptr, Entry, node)


/// new_node
/// Create new node, memory get from Arena for cache-friendly accessing
#define new_node(Type, arena, prev_node) (prev_node != LIST_NULL_NODE \
    ? ((prev_node)->next = &((Type*)memset(acquire_memory(arena, sizeof(Type)), 0, sizeof(Type)))->node \
    , node_entry((prev_node)->next, Type)) \
    : (Type*)memset(acquire_memory(arena, sizeof(Type)), 0, sizeof(Type))\
    )


/// list_for_each
/// Simple pattern for loop through each node of linked list
#define list_for_each(pos, node) for (ListNode* (pos) = (node); pos; (pos) = (pos)->next)


// No node delete algorithms are welcome in single linked list
// void list_node_del(ListNode* list, ListNode* entry)
// {
//  	ListNode* p;

//     if (entry == list)
//     {
//         list->next = LIST_NULL_NODE;
//         return;
//     }

// 	for (p = list; p; p = p->next)
//     {
// 		if (p->next != entry) continue;
// 		p->next = entry->next;
// 		return;
// 	}
// }


/// acquire_memory
/// Get memory from Arena (no system memory allocation happen)
void* acquire_memory(Arena* arena, size_t size)
{
    if (arena == NULL || arena->tail - arena->head < size)
    {
        return NULL;
    }

    void* result = (uint8_t*)arena->data + arena->head;
    arena->head += size;
    return result;
}


/// Test
/// Data structure for testing
typedef struct Test
{
    ListNode    node;   // Must be value (not pointer or crash)
                        // And place this node in the first member will result zero-cost abstraction 

    int32_t     value;  // Simple value
} Test;


int main()
{
    printf("Linked list example!\n");

    size_t buffer_size = 1024;
    void* buffer_data = malloc(buffer_size);

    Arena arena = {
        .head = 0,
        .tail = buffer_size,
        .data = buffer_data,
        .size = buffer_size,
    };

    Test* a = new_node(Test, &arena, LIST_NULL_NODE);
    Test* b = new_node(Test, &arena, &a->node);
    
    a->value = 1;
    b->value = 2;

    list_for_each (p, &a->node)
    {
        Test* v = node_entry(p, Test);
        printf("Value of %p = %d\n", p, v->value); 
        // You will see the address of node is nearly sitting next previous node
        // That why this Linked List is cache friendly
    }

    // Cleanup
    free(buffer_data); // The only needing to cleanup is to free buffer_data

    return 0;
}

//! EOF
