# Auto compile and run C console program
Good for practice C coding.


## Features
- Watch files changed and compile
- Clear screen after compile
- Faster iterations for create C console program

## Todos features
- Auto reload config
- Custom compiler, auto find common compilers path (msvc)


## Configs
```jsonc
{
    // Compiler to use (gcc, clang, msvc). Default are clang (cross-platform)
    "compiler": "clang",

    // Compile flags
    "flags": "",

    // Params for run program
    "runParams": "",

    // Interval to watch file (use loop to check file changed)
    "watchInterval": 2,

    // Clear screen before launch
    "clearScreen": true
}
```