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


## Sentinel (avoid out of bounds indexing)
```C++
struct Thing
{
    // Fields
};

Thing Things[1024];

Thing* get_thing(int index)
{
    assert(index > -1 && index < 1024);
    return Things[index + 1]; // 0 is reserved, nil thing
}

Thing* get_thing(const Handle_Map& handle_map, Handle handle)
{
    assert(handle.index > -1 && handle.index < handle_map.num_items);

    bool    found = (map.sparse_indices[handle.index].generation == map.generation);
    int     index = int(found) * map.sparse_indices[handle.index].index;
    return handle_map.items[index];
}

Thing* target = get_thing(game_state.entities, player.attack_target);
target.hp -= entity.attack_damage; // If have no target, no enemies have been taken damage
```
See, by reversed 1 slot, we have both fast and safe indexing.


## Fast remove item from array, but trade off of ordering
```C
items[i] = items[num_items - 1];
num_items -= 1;
// You see, that you just move the last item into the removed item's slot
```


## Enumerated arrays
```C
enum Values
{
    Foo,
    Bar,
    Jaz,
};

const char* value_names[] = {
    [Foo] = "Foo",
    [Bar] = "Bar",
    [Jaz] = "Jaz",
};
```


## X Macros (extended for above version")
X Macros:
```C
DEFINE_ENTITY(PLAYER)
DEFINE_ENTITY(BULLET)
DEFINE_ENTITY(WALL)
DEFINE_ENTITY(MOB_GOBLIN)
DEFINE_ENTITY(MOB_ORC)
DEFINE_ENTITY(BOSS_ORC_MAGI)
```

Usages:
```C
#define DEFINE_ENTITY(X) X,
enum Entity_Kind
{
    NONE,
    #include "XMacros.h"
};

#undef
#define DEFINE_ENTITY(X) [X] = "" #X,
static const char* const Entity_Names[] = {
    #include "XMacros.h"
};
```


## Dealing with C++ RAII and OOP mindset
```C++
#if defined(__cpluplus) && defined(CPP_STRICT_STYLE)
// Put this to your struct when you wanna use method for shorter code
#define NO_RAII(Type)                                                   \
    Type() = delete; ~Type() = delete;                                  \
    Type(Type&&) = delete;                                              \
    Type(const Type&) = delete; Type& operator=(const Type&) = delete;  \
    static_type(__is_trivial_copy(Type), "RAII detected! Type: " #Type)


// Ban all inheritance system (should undef if you library that use theses)
#define class       DONT_USE_CLASS_USE_STRUCT
#define virtual     DONT_USE_VIRTUAL
#define override    DONT_USE_OVERRIDE_POLYMORPHISM
#define final       DONT_USE_FINAL_KEYWORDS
#define friend      DONT_USE_FRIEND_ENCAPSULATION
#define private     DONT_USE_PRIVATE_DATA_MUST_BE_FLAT
#define protected   DONT_USE_PROTECTED_DATA_MUST_BE_FLAT
#else
#define NO_RAII(Type)
#endif
```


## Force ban keywords of RTTI and exceptions in C++ code (even have -fno-rtti -fno-exceptions)
```C+
#if defined(__cpluplus) && defined(CPP_STRICT_STYLE)
#define noexcept        DONT_USE_EXCEPTIONS
#define throw           DONT_USE_EXCEPTIONS
#define try             DONT_USE_EXCEPTIONS
#define catch           DONT_USE_EXCEPTIONS

#define typeid          DONT_USE_RTTI
#define dynamic_cast    DONT_USE_RTTI_DYNAMIC_CAST
#endif
```


## Flags to use C++ as scripting and hot reload
```cmd
# For GCC / Clang
g++ -shared -fPIC -fno-rtti -fno-exceptions -fno-threadsafe-statics -nostdlib -O3 player_script.cpp -o player_script.dll

# For MSVC (Windows cl.exe)
cl.exe /LD /GR- /EHs-c- /O2 /GS- /NODEFAULTLIB player_script.cpp
```


## More about macros tricks
- https://handmade.network/forums/t/1273-post_your_c_c_macro_tricks/3
