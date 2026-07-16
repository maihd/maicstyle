# Editor for ECS Hierarchy
```C
typedef struct alignas(16) Entity // Fit to simd128 registers
{
    uint32_t id; // the combination of index and generation
    uint32_t flags_or_relationship;
    uint32_t components;
    uint32_t reserved_or_more_components;
} Entity;

typedef struct StringBuffer
{
    size_t size;
    size_t capacity;
    char*  data;
} StringBuffer;

// This component can be excluded in runtime build
typedef struct EntityName
{
    StringBuffer name;
} EntityName;

void editor_system_hierarchy(EntityId entity, EntityName* name)
{
    int indent = editor_get_entity_intent(entity);
    // draw imgui here
}
```
