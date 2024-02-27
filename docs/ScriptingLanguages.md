# Ideas of Scripting language to generate C code and symbol logic system

```Script
Monster: # Name of the Actor/Prefab/Entity Class
    When has <Weapon>: # When is statement, <Weapon> is dynamic/generic per prefab
        Hand is holding <Weapon> # Hand is and child Entity of Monster
        Slowdown the <MovementSpeed> by 10% # Slowdown is a command

    Otherwise: # Otherwise else-statement of When (More natural language than If-Else)
        Hand is free # Hand is child Entity of Monster, free is a predefined properties of Hand (component)
        Set the <MovementSpeed> to 100% # Slowdown is a TurnBack

# All components and statement are using preprocessing to generates components, with predefined system
# Preprocessor has the knowledges of C, by generate textual output (not machine code or other kinds of bytecode)
# AI may help, but not the purpose from the beginning
# So, why the simple scripting solution like this, now is a best and fit the current problems we have?
# Please no, each states are seperated, can combine to new states (State(StateA, StateB))
# We need to discover the Logic Programming paradises to findout mores.
```

```C

// Autogen.c

static SystemFilter* filter;

// @init
void register_scripts(void)
{
    assert(filter == nullptr);

    filter = ecs_new_filter_by_prefab("Monster");
    register_system_update_by_filter(filter, OnSystemUpdateByFilter);
}

// @deinit
void unregister_scripts(void)
{
    assert(filter != nullptr);

    unregister_system_update_by_filter(filter, OnSystemUpdateByFilter);
    filter = nullptr; // nullptr is predefined, equal to NULL, but more meaningful
}

// @script
// @system-update
void OnSystemUpdateByFilter(float dt, EntityId monster, EntityId weapon)
{
    if (is_has_weapon(monster)) // is_has_weapon is Programmer Code
    {
        attach_weapon(monster);
        slowdown_movement_by_percent(monster, 0.1); // This call is safe in debug, remove check code in release build
    }
    else
    {
        set_movement_by_percent(monster, 1.0);
    }
}

// Commands.c

// @command Set<MovementSpeed, Percent>
// Set is generic command
// Gerenic arg0: MovementSpeed is ComponentType
// Gerenic arg1: Percent is NumberType
void set_movement_by_percent(EntityId entity, float percent);

// @command WhenHas<ETag<Hand>, >
void is_has_weapon(Entity entity);

// @command Is<ETag<Hand>, holding, <Weapon>>
```