#include <stdio.h>

// Zero-allocation version of std::function
struct DeferFunc
{
    typedef void (DeferFunc::*MethodPtr)(void);

    void* object;
    MethodPtr method;

    template<typename T>
    void operator=(const T& caller)
    {
        object = (void*)&caller;
        method = (MethodPtr)&T::operator();
    }

    void operator()(void) 
    {
        (((DeferFunc*)object)->*method)();
    }
};

// Auto call defer when out-of-scope (trick with destructor)
struct AutoDeferCallDtor 
{
    DeferFunc* func;
    
    AutoDeferCallDtor(DeferFunc* func) : func(func) {}
    ~AutoDeferCallDtor() { (*func)(); }
};

#define DEFER_NAME_1(X, Y) __defer ## X ## Y
#define DEFER_NAME_2(X, Y) DEFER_NAME_1(X, Y)
#define DEFER_NAME(APPEND) DEFER_NAME_2(__LINE__, APPEND)
#define defer DeferFunc DEFER_NAME(_func); AutoDeferCallDtor DEFER_NAME()(&DEFER_NAME(_func)); DEFER_NAME(_func) = [&]() -> void


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
