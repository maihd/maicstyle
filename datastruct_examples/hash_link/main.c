#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct HashLinkEntry HashLinkNode;

struct HashLinkEntry
{
    HashLinkNode*   next;

    uint32_t        key;
    uint32_t        value;
};


typedef struct HashLink
{
    int32_t        entry_count;
    HashLinkNode*  entries[];
} HashLink;


void hash_link_add(HashLink* head, uint32_t key, uint32_t value)
{
    HashLinkNode* node = malloc(sizeof(HashLinkNode));
    node->next = NULL;

    node->key = key;
    node->value = value;

    int32_t entry_index = key & (head->entry_count);
    node->next = head->entries[entry_index];
    head->entries[entry_index] = node;
}


uint32_t hash_link_find(HashLink* head, uint32_t key, uint32_t def_value)
{
    int32_t entry_index = key & (head->entry_count);

    HashLinkNode* node = head->entries[entry_index];
    while (node != NULL)
    {
        if (node->key == key)
        {
            return node->value;
        }

        node = node->next;
    }
    
    return def_value;
}


HashLink* hash_link_new(int32_t entry_count)
{
    HashLink* head = malloc(sizeof(HashLink) + sizeof(HashLinkNode*) * entry_count);
    head->entry_count = entry_count;
    for (int i = 0; i < entry_count; i++)
    {
        head->entries[i] = NULL;
    }

    return head;
}


void hash_link_free(HashLink* head)
{
    for (int i = 0, n = head->entry_count; i < n; i++)
    {
        HashLinkNode* node = head->entries[i];
        while (node)
        {
            HashLinkNode* next = node->next;
            free(node);
            node = next;
        }
    }
}


static uint32_t strhash(const char* str);


int main()
{
    HashLink* head = hash_link_new(8);
    hash_link_add(head, strhash("STR_KEY"), 0);
    hash_link_add(head, strhash("STR_KEY_1"), 1);
    hash_link_add(head, strhash("STR_KEY_2"), 2);

    printf("hash_link_find(STR_KEY) = %u\n", hash_link_find(head, strhash("STR_KEY"), -1));
    printf("hash_link_find(STR_KEY_1) = %u\n", hash_link_find(head, strhash("STR_KEY_1"), -1));
    printf("hash_link_find(STR_KEY_2) = %u\n", hash_link_find(head, strhash("STR_KEY_2"), -1));

    hash_link_free(head);

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
