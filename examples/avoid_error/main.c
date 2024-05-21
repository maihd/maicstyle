/// -------------------------------------------------------------------------------
/// "The Easiest Way To Handle Errors Is To Not Have Them" 
///     - Ryan Fleury, https://www.rfleury.com/p/the-easiest-way-to-handle-errors
/// -------------------------------------------------------------------------------

#include <stdio.h>
#include <stdint.h>


/// Solution 1: Guarantee valid reads (null pointers)


typedef struct Node
{
    struct Node* next;
    int value;
} Node;

Node null_node = { &null_node };


Node* child_from_value(Node* node, int value)
{
    Node* result = &null_node;
    for(; node != &null_node; node = node->next)
    {
        if (value == node->value)
        {
            result = node;
            break;
        }
    }
    return result;
}


Node* search_for_interest_chain(Node* root)
{
    Node* n1 = child_from_value(root, 1);
    Node* n2 = child_from_value(  n1, 2); // No need chain of null checks
    Node* n3 = child_from_value(  n2, 3);
    Node* n4 = child_from_value(  n3, 4);

    // we will necessarily get here - and we're also
    // guaranteeing for all of *our* callers that they
    // can dereference this result, even if it's 'invalid'
    return n4;
}


/// Solution 2: Make Zero Values Valid (Zero-Is-Initialization)


typedef struct StrView
{
    const char* data;   // 0 mean empty
    size_t      size;   // 0 mean empty, too, but we should check this member only
} StrView;


StrView empty_str = {0}; // Easy init
StrView empty_str_w_data = {""}; // Also easy init


/// Solution 3: If You’re Going To Fail, Fail Early
///     Let the app/game crash, debug break occur
///     and we jump the right in to the line that crash
///     trace the bug with information give from debugger, logger
///     more faster and better approach.


/// Solution 4: Prefer Fewer Types—Or, Prefer AND over OR


typedef struct Json
{
    int type;
    int value;
} Json;


typedef enum JsonError
{
    JsonError_None
} JsonError;


typedef struct JsonResult
{
    Json        json;
    JsonError   error;
} JsonResult;


JsonResult JsonParse(const char* json, int32_t jsonLength);


/// Solution 5: Error Information Side-Channels
///     Pros: Keep code smoothly, reduce overhead when coding
///     Cons: Cannot handle error immediately like Result/Option


int32_t i32_parse(const char* str)
{
    int32_t value = 0;
    for (char c = *str; c; (c = *str++))
    {
        if (c < '0' || c > '9')
        {
            // Should log error to file or add to list instead
            // More advance is to add callstack, more information
            fprintf(stderr, "[error] i32_parse: Failed to parse %s\n", str);
            return 0;
        }

        value = value * 10 + (int)(c - '0');
    }
    return value;
}


//! EOF
