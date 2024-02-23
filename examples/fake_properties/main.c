#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef struct StringView
{
    size_t      size;
    const char* data;
} StringView;

typedef struct String
{
    union
    {
        // FakeProperty: get StringView from String, zero-cost abstractions
        StringView  as_view;

        // True fields, share memory-layout with StringView above, only diff is `data` is not read-only
        struct
        {
            size_t  size;
            char*   data;
        };
    };

    // Adding other fields here
} String;

//! EOF

