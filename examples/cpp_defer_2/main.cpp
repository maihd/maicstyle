#include <stdio.h>

// Zero-allocation version of std::function
template <typename T>
struct __defer_call
{
    T f;
    
    __defer_call(const T& f) : f(f) {}
    ~__defer_call() { f(); }
};

// Auto call defer when out-of-scope (trick with destructor)
struct __defer_help 
{
    template <typename T>
    __defer_call<T> operator+(const T& f) { return __defer_call<T>(f); }
};

#define __DEFER_NAME_1(X)    __defer ## X
#define __DEFER_NAME         __DEFER_NAME_1(__LINE__)

#define defer const auto& __DEFER_NAME = __defer_help{} + [&]() -> void


int main() 
{
    defer 
    {
        printf("Call from defer!\n");
    }; // Require ';' here

    printf("Call before defer!\n");

    return 0;
}

//! EOF
