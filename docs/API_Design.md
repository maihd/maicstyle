# API design for procedural code

## Large Arrays of Things
- Thing is PoD, fixed size, contains no dynamic data
- Things is container of Thing, define custom access pattern, processing, ...
- Thing can index of parent, first child, last child, next sibling, prev sibling for hierarchy.
- Index can replace with Handle. Things can use Handle_Map to store thing.
That's enough, we no need generics code here.
```C
struct ThingHandle
{
    uint32_t index;
    uint32_t generation;
};

struct Thing
{
    // Properties
    
    
    // Hierarchy
    ThingHandle parent;
    ThingHandle firstChild;
    ThingHandle lastChild;
    ThingHandle nextSibling;
    ThingHandle prevSibling;
};


struct Things
{
    Thing items[1024];
    bool used[1024];
};


ThingHandle ThingsAdd(Things* things, Thing thing);
bool        ThingsRemove(Things* things, ThingHandle handle);
Thing*      ThingsGet(Things* things, ThingHandle handle);
```