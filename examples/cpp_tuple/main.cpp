#include <stdio.h>

// Simple, PoD tuple implementation, tuple should be use with return type only

template <typename... Types> struct Tuple;

template <typename T0>
struct Tuple<T0> { T0 v0; };

template <typename T0, typename T1>
struct Tuple<T0, T1> { T0 v0; T1 v1; };

template <typename T0, typename T1, typename T2>
struct Tuple<T0, T1, T2> { T0 v0; T1 v1; T2 v3; };

template <typename T0, typename T1, typename T2, typename T3>
struct Tuple<T0, T1, T2, T3> { T0 v0; T1 v1; T2 v2; T3 v3; };


enum IOError 
{
    IOError_None,
    IOError_FileNotFound,
};


Tuple<void*, IOError> IO_OpenFile(const char* filename)
{
    return { nullptr, IOError_FileNotFound };
}


void IO_CloseFile(void* handle)
{
    // no-ops
}


int main()
{
    auto [ file, error ] = IO_OpenFile("hello_world.txt");
    if (error != IOError_None)
    {
        fprintf(stderr, "Failed to open file! Error: %d\n", error);
        return 1;
    }

    IO_CloseFile(file);
    return 0;
}

//! EOF
