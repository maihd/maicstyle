const fs = require("fs");

const HASH_PRIME = "1099511628211ULL";
const HASH_OFFSET_BASIS = "14695981039346656037ULL";

// Only support max length <= 64, larger will cause compiler fatal error:
//  main.c:24:29: fatal error: bracket nesting level exceeded maximum of 256
const MAX_LENGTH = 64;

const header = `
#pragma once

#define CONST_MAX_LENGTH ${MAX_LENGTH}
#define CONST_HASH_PRIME ${HASH_PRIME}
#define CONST_HASH_OFFSET_BASIS ${HASH_OFFSET_BASIS}

#define const_hash_func(s, n, i, x) ((x ^ s[i < n ? n - 1 - i : 0]) * CONST_HASH_PRIME)

#define const_hash_impl_${MAX_LENGTH}(s, n, x) x
`;

const footer = `

#define const_hash(s) const_hash_impl_0(s, sizeof(s) - 1, CONST_HASH_OFFSET_BASIS)

//! EOF

`;

// Create algorithm content per length of string
const lines = [];

for (let i = MAX_LENGTH - 1; i > -1; i--)
{
    const line = `#define const_hash_impl_${i}(s, n, x) ((${i} < n) ? const_hash_func(s, n, ${i}, const_hash_impl_${i + 1}(s, n, x)) : x)`;

    lines.push(line);
}

// Create file content
const content = header + lines.join("\n") + footer;
fs.writeFileSync("const_hash_pp.h", content);