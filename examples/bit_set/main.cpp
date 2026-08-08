#include <stdio.h>


// Simple and lightweight std::initialize_list
namespace std 
{
    template<class E>
    struct initializer_list 
    {
        const E* start_ptr;
        size_t   list_size;

        initializer_list() : start_ptr(nullptr), list_size(0) {}
        initializer_list(const E* ptr, size_t sz) : start_ptr(ptr), list_size(sz) {}

        size_t size() const { return list_size; }
        const E* begin() const { return start_ptr; }
        const E* end() const { return start_ptr + list_size; }
    };
}


// Odin bit_set
template <typename Enum, typename Storage = int>
struct Bit_Set
{
    Storage bits;


    constexpr Bit_Set() : bits(0) {}
    constexpr Bit_Set(Storage bits) : bits(bits) {}
    constexpr Bit_Set(Enum enum_value) : bits(1 << enum_value) {}
    constexpr Bit_Set(std::initializer_list<Enum> enum_values)
    {
        for (const auto e : enum_values)
        {
            bits |= 1 << (Storage)e;
        }
    }


    constexpr Storage operator&(Enum enum_value)
    {
        return bits & (1 << (Storage)enum_value);
    }

    // Add more operators here
};


// Bit_Set is required to be trivially copyable (or so called blitable data type)
enum __Enum_For_Static_Assert {};
static_assert(__is_trivially_copyable(Bit_Set<__Enum_For_Static_Assert, int>), "Bit_Set must be PoD-like");
static_assert(__is_trivially_copyable(std::initializer_list<__Enum_For_Static_Assert>), "std::initializer_list must be PoD-like");


enum class File_Mode
{
    Read,
    Write,
};


typedef Bit_Set<File_Mode> File_Modes;


int main()
{
    auto file_modes = File_Modes{ File_Mode::Read, File_Mode::Write };

    printf("file_modes: %d\n", file_modes.bits);
    printf("file_modes has File_Mode::Read: %s\n", (file_modes & File_Mode::Read) ? "true" : "false");
    printf("file_modes has File_Mode::Write: %s\n", (file_modes & File_Mode::Write) ? "true" : "false");
}

//! EOF
