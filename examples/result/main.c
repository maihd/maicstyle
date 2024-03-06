#include <stdio.h>
#include <stdint.h>
#include <string.h>


// Like error_handling example
// But Result work as generic type for many functions that can failed 
// Not recommend when interfaces is complete
// But helpful when working with new functions, faster iterate of development
typedef struct Result
{
    uint32_t code;

    union
    {
        void*       ptr_value;
        
        int32_t     i32_value;
        uint32_t    u32_value;
        float       f32_value;
        double      f64_value;
        const char* str_value;

        /* Add other common values here */

        const char* message;
    };
} Result;


// Basic, most commonly code of Result
// Can be add more with #define or enum (a.k.a extending)
enum
{
    ResultCode_Ok,      // Work perfectly
    ResultCode_Error,   // Program error (Ex: nullptr, out of memory)
    ResultCode_Failed,  // User mistake (Ex: input is invalid)
};


// Like parse_int function of error_handling example
// But the return type now is Result:
//  - have message for logging and debugging
//  - have the reason why its failed 
//  - can chainning its with other results? (Result<i32> -> Result<Entity>?)
Result i32_parse(const char* str, size_t len)
{
    int32_t value = 0;
    for (size_t i = 0; i < len; i++)
    {
        char c = str[i];
        if (c < '0' || c > '9')
        {
            return (Result){
                .code = ResultCode_Failed,

                // No need to init i32_value, because we dont use its 
                // Or can be mark with magic number, for debugging purposes
                // Or return the error message (should not allocate memory in global heap)
                .message = "Expect digital characters only!"
            };
        }

        value = value * 10 + (int32_t)(c - '0');
    }

    return (Result){
        .code = ResultCode_Ok,
        .i32_value = value
    };
}

// Not much differences from error_handling's main()
int main(void)
{
    printf("Error handling with Result (generic data structure) example\n");

    const char* str0 = "100";
    const Result int_parsed_0 = i32_parse(str0, strlen(str0));
    if (int_parsed_0.code == ResultCode_Ok)
    {
        printf("Parse '%s' success: %d\n", str0, int_parsed_0.i32_value);
    }
    else
    {
        printf("Failed to parse: %s, Error message: %s\n", str0, int_parsed_0.message);
    }

    const char* str1 = "100a";
    const Result int_parsed_1 = i32_parse(str1, strlen(str1));
    if (int_parsed_1.code == ResultCode_Ok)
    {
        printf("Parse '%s' success: %d\n", str1, int_parsed_1.i32_value);
    }
    else
    {
        printf("Failed to parse: %s, Error message: %s\n", str1, int_parsed_1.message);
    }

    return 0;
}

//! EOF
