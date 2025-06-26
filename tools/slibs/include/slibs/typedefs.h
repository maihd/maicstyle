#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdbool.h>

typedef struct StrBuf
{
    char*       data;
    uint32_t    size;
    uint32_t    flags;
} StrBuf;

//! EOF

