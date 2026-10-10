# Tips and tricks for programming (C and beyond)

## Ring buffer and ring memory access
```C
void draw_polygon(vec2* points, int num)
{
    for (int i = 0; i < num; i++)
    {
        draw_line(points[i], points[(i + 1) % num]);
        // in the last line (when i == num - 1, i == num)
        // points[i + 1] will crash
        // push (i + 1) == 0
        // which is safe and fast
        // and have no branches
        // this a natural of how ring buffer worked
    }
}
```

## Safe list, use ring access, but for list
```C
struct Node
{
    Node* next;
    Node* prev;
};

Node nil        = { &nil, &nil };

Node first      = { &nil, &nil };
Node second     = { &nil, &nil };

first->next     = &second;
second->prev    = &first;

Node* node = &first;
while (node != &nil)
{
    // do works

    node = node->next;
}

// other option, ring linked list
first->prev     = &second;
second->next    = &first;

Node* node = &first;
do
{
    // do works

    node = node->next;
} while (node != &first);

// No you see, we never have null pointer
// More use case of this pattern, check "Good taste" of Linus Torvalds
```

# Fast remove item from array, but trade off of ordering
```
items[i] = items[num_items - 1];
num_items -= 1;
// You see, that you just move the last item into the removed item's slot
``
