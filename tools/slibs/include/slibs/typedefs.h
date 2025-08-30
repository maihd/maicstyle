#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdbool.h>


typedef enum StrBufFlags
{
    StrBuf_None     = 0,
    StrBuf_Fixed    = 1 << 0,
    StrBuf_Owned    = 1 << 1,
    StrBuf_Alloced  = 1 << 2,
    StrBuf_ViewOnly = 1 << 3,
} StrBufFlags;


typedef struct StrBuf
{
    char*       data;
    uint32_t    size;
    uint32_t    flags;
} StrBuf;


typedef struct StrBuf128
{
    union
    {
        StrBuf  strbuf;
        char*   data;  
    };

    char fixed_buffer[128];
} StrBuf128;


typedef struct StrView
{
    char*    data;
    uint32_t size;
} StrView;


//! EOF

