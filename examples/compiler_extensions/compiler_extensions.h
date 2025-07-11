#pragma once

// An example of compiler extensions that commonly use in many projects of mine.
// __vectorcall: unused
// __forceinline: widely used in math library, and this is shorter than __attribute__((always_inline))
// __deprecated: mark an API deprecated
// __deprecated_msg: mark an API deprecated with compile time message
// constexpr: only use for constants, constexpr functions are not supported in C
// nullptr: easier to write than NULL, have the same semantic with NULL
// __enum_type: make an enum type in C more like a enum type in C++ (actually no-ops, just to make C++ code compile with C compiler)
// __default_init: support default initialization in C (actually no-ops, just to make C++ code compile with C compiler)
// __typename: get typename of a type, in C use macro #, in C++ use __PRETTY_FUNCTION__ or __FUNCSIG__ with constexpr to get name

// -------------------------------------------------------------
// Function call conventions
// -------------------------------------------------------------

/// __vectorcall
/// Support __vectorcall for non MSVC compiler
#if !defined(_WIN32) && !defined(__vectorcall)
#if defined(__clang__)
#   define __vectorcall __attribute__((vectorcall))
#else
#   define __vectorcall /* NO VECTORCALL SUPPORTED */
#endif
#endif


/// __forceinline
/// Support __forceinline for non MSVC compiler
#if !defined(_WIN32) && !defined(__forceinline)
#   define __forceinline static __attribute__((always_inline)) inline
#endif


/// __deprecated
/// Uniserval compiler of __deperecated (Apple SDK)
#if !defined(__deprecated)
#if defined(_MSC_VER)
#define __deprecated __declspec(deprecated)
#else
#define __deprecated __attribute__((deprecated))
#endif
#endif


/// __deprecated_msg
/// Uniserval compiler of __deperecated_msg (Apple SDK)
#if !defined(__deprecated)
#if defined(_MSC_VER)
#define __deprecated_msg(msg) __declspec(deprecated(msg))
#else
#define __deprecated_msg(msg) __attribute__((deprecated(msg)))
#endif
#endif


// -------------------------------------------------------------
// C++ modifiers for C
// -------------------------------------------------------------

/// constexpr
/// C++ constexpr
#if !(defined(__cplusplus) || (__STDC_VERSION__ >= 202311L)) && !defined(constexpr)
#define constexpr static const
#endif


/// nullptr
/// C++ nullptr 
#if !(defined(__cplusplus) || (__STDC_VERSION__ >= 202311L)) && !defined(nullptr)
#define nullptr ((void*)0)
#endif

// -------------------------------------------------------------
// C extensions that commonly use in C++
// -------------------------------------------------------------

/// __enum_type
/// Define underlying type for enum
/// @note(maihd): 
///     enum in C does not support underlying type yet (until C23), 
///     so maybe cause different struct layout inbetween C/C++ world
#if !defined(__enum_type)
#if defined(__cplusplus) || (__STDC_VERSION__ >= 202311L)
#define __enum_type(T) : T
#else
#define __enum_type(T)
#endif
#endif


/// __default_init 
/// Default initialization for struct fields and function arguments
/// Help to support universal API in C/C++ world (more ergonomics)
#if !defined(__default_init)
#ifdef __cplusplus
#define __default_init(expr) = (expr)
#else
#define __default_init(expr)
#endif
#endif

// -------------------------------------------------------------
// Get typename of a type
// -------------------------------------------------------------

/// __typename
/// Get name of type with help of C++ constexpr to make sure type is existed
/// @spoiler(maihd): long definition
#if !defined(__typename)
#if !defined(__cplusplus) || defined(USE_FAST_TYPENAME)
#define __typename(T) #T
#else
#define __typename(T) __typename_impl<T>()

template <typename T>
constexpr auto __typename_GetTypeNameHelper();

template <typename T>
constexpr const char* __typename_impl(void)
{
    static auto string = __typename_GetTypeNameHelper<T>();
    return string.data;
}

template <typename T>
constexpr auto __typename_GetTypeNameHelper()
{
    #if defined(_MSC_VER)
    #define __FUNC__ __FUNCSIG__
    #else
    #define __FUNC__ __PRETTY_FUNCTION__
    #endif

    int head = 0;
    int tail = 0;
    for (int i = 0; i < sizeof(__FUNC__); i++)
    {
        if (__FUNC__[i] == '<')
        {
            if (head == 0)
            {
                head = i + 1;
            }
        }
        else if (__FUNC__[i] == '>')
        {
            tail = i - 1;
        }
    }
    
    /// Result of __typename
    /// Subset typeof StringBuffer
    /// @note: need manually change when StringBuffer changed
    struct Result 
    {
        int     memtag                  = 0x2e9497f4U;      // WEAK tag
        int     memref                  = 0;
        int     length                  = 0;
        int     capacity                = sizeof(__FUNC__);        
        char    data[sizeof(__FUNC__)]  = "";
    };

    Result result;
    
    int index = head;
    int& length = result.length;
    char* typeName = result.data;
    const char* funcName = __FUNC__ + head;
    while (*funcName != '\0' && index <= tail)
    {
        // Skip 'struct' prefix
        if (true
            && funcName[0] == 's'
            && funcName[1] == 't'
            && funcName[2] == 'r'
            && funcName[3] == 'u'
            && funcName[4] == 'c'
            && funcName[5] == 't'
            && funcName[6] == ' ')
        {
            funcName += 7;
            index += 7;
            continue;
        }

        // Skip 'class' prefix
        if (true
            && funcName[0] == 'c'
            && funcName[1] == 'l'
            && funcName[2] == 'a'
            && funcName[3] == 's'
            && funcName[4] == 's'
            && funcName[5] == ' ')
        {
            funcName += 6;
            index += 6;
            continue;
        }

        // Skip 'union' prefix
        if (true
            && funcName[0] == 'u'
            && funcName[1] == 'n'
            && funcName[2] == 'i'
            && funcName[3] == 'o'
            && funcName[4] == 'n'
            && funcName[5] == ' ')
        {
            funcName += 6;
            index += 6;
            continue;
        }

        // Skip 'enum' prefix
        if (true
            && funcName[0] == 'e'
            && funcName[1] == 'n'
            && funcName[2] == 'u'
            && funcName[3] == 'm'
            && funcName[4] == ' ')
        {
            funcName += 5;
            index += 5;
            continue;
        }

        *typeName++ = *funcName++;
        length++;    
        index++;
    }

    #undef __FUNC__ // Release __FUNC__ to other usages
    return result;
}
#endif
#endif

// assert_type_is_memcopyable();
// assert_type_is_trivial();
// assert_type_is_pod();
// assert_type_size();
// assert_type_alignment();
// assert_not_null();
// assert_in_range();
// assert_enough_memory();

//! LEAVE AN EMPTY LINE HERE, REQUIRE BY GCC/G++
