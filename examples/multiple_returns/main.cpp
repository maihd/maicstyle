#include <stdio.h>

enum IOError 
{
    IOError_None,
    IOError_FileNotFound,
};


struct IOResult
{
    void*   handle;
    IOError error;  
};


IOResult IO_OpenFile(const char* filename)
{
    return IOResult{ nullptr, IOError_FileNotFound };
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
