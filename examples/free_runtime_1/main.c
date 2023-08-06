#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

int __stdcall mainCRTStartup(void)
{
    char msg[] = "Hello world!\n";
    HANDLE stdout = GetStdHandle(STD_OUTPUT_HANDLE);
    WriteFile(stdout, msg, sizeof(msg), NULL, NULL);
    return 0;
}

//! EOF
