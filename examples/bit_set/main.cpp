#include <stdio.h>


// Simple and lightweight std::initializer_list
namespace std
{
    template<typename E>
    struct initializer_list
    {
        const E*    data;
        size_t      len;
    };
}

// Readonly slice, can have syntax sugar from compiler like { 1, 2, 3 }
template <typename E>
using InitList = std::initializer_list<E>;

// Odin's bit_set
template <typename TEnum, typename TStorage = int>
struct BitSet
{
    static_assert(__is_enum(TEnum), "TEnum must be a enum type");
    static_assert(__is_integral(TStorage), "TStorage must be a integer type");

    TStorage bits;
};

template <typename TEnum, typename TStorage = int>
consteval BitSet<TEnum, TStorage> MakeBitSet(InitList<TEnum> enum_values)
{
    BitSet<TEnum, TStorage> res = { 0 };
    for (int i = 0; i < enum_values.len; i += 1)
    {
        TEnum e = enum_values.data[i];
        res.bits |= 1 << (TStorage)e;
    }
    return res;
}

template <typename TEnum, typename TStorage = int>
constexpr BitSet<TEnum, TStorage> operator&(BitSet<TEnum, TStorage> bitset, TEnum enum_value)
{
    return {bitset.bits & (1 << (TStorage)enum_value)};
}

template <typename TEnum, typename TStorage = int>
constexpr BitSet<TEnum, TStorage> operator|(BitSet<TEnum, TStorage> bitset, TEnum enum_value)
{
    return {bitset.bits | (1 << (TStorage)enum_value)};
}

template <typename TEnum, typename TStorage = int>
constexpr bool HasFlags(BitSet<TEnum, TStorage> bitset, TEnum enum_value)
{
    return bitset.bits & (1 << (TStorage)enum_value);
}

template <typename TEnum, typename TStorage = int>
constexpr bool HasFlags(BitSet<TEnum, TStorage> bitset, InitList<TEnum> enum_values)
{
    return bitset.bits & MakeBitSet<TEnum, TStorage>(enum_values).bits;
}

template <typename TEnum, typename TStorage = int, typename TStorage2 = int>
constexpr bool HasFlags(BitSet<TEnum, TStorage> a, BitSet<TEnum, TStorage2> b)
{
    return a.bits & (TStorage)b.bits;
}

#define DEFINE_BITSET(Name, ...)                                        \
    typedef BitSet<__VA_ARGS__> Name;                                   \
    consteval FileModes Make ## Name(InitList<__VA_ARGS__> enum_values) \
    {                                                                   \
        return MakeBitSet<__VA_ARGS__>(enum_values);                    \
    }

// Example code

enum FileMode
{
    FileMode_Read,
    FileMode_Write,
};

DEFINE_BITSET(FileModes, FileMode);

int main()
{
    auto file_modes = MakeFileModes({ FileMode_Read, FileMode_Write });

    printf("file_modes: %d\n", file_modes.bits);
    printf("file_modes has FileMode_Read: %s\n", HasFlags(file_modes, FileMode_Read) ? "true" : "false");
    printf("file_modes has FileMode_Write: %s\n", HasFlags(file_modes, FileMode_Write) ? "true" : "false");
}

//! EOF
