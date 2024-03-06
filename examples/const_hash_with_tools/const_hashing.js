const fs = require("fs");

const src = fs.readFileSync("main.c").toString();
const regex = /const_hash\(\"([^"\\\n]|\\.|\\\n)*\"\)/g;

const lines = [];
for (const line of src.split("\n")) {
    const matches = line.match(regex);
    if (matches) {
        for (const match of matches) {
            // console.log(match);

            const str = match.substring("const_hash(\"".length, match.length - "\")".length);
            // console.log(str);

            const hash = calcHash(str);
            // console.log(hash);

            const result = `const_hash_v("${str}", 0x${hash.toString(16)}ULL)`;
            // console.log(result);

            const computedLine = line.replace(regex, result);
            lines.push(computedLine);
        }
    } else {
        lines.push(line);
    }
}

const content = lines.join("\n");
fs.writeFileSync("main.pp.c", content);

function calcHash(str) {
    const buffer = Buffer.from(str);

    let hash = BigInt.asUintN(64, 14695981039346656037n);
    for (const byte of buffer) {
        hash = BigInt.asUintN(64, hash ^ BigInt.asUintN(64, BigInt(byte)));
        hash = BigInt.asUintN(64, hash * BigInt.asUintN(64, 1099511628211n));
    }

    return BigInt.asUintN(64, hash);
}