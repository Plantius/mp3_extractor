#ifndef STANDARD_H
#define STANDARD_H
#include <iostream>
#include <climits>

template <typename T>
T swap_endian(T u)
{
    // Credit to Alexandre C. (https://stackoverflow.com/users/373025/alexandre-c)
    static_assert (CHAR_BIT == 8, "CHAR_BIT != 8");

    union
    {
        T u;
        unsigned char u8[sizeof(T)];
    } source, dest;

    source.u = u;

    for (size_t k = 0; k < sizeof(T); k++)
        dest.u8[k] = source.u8[sizeof(T) - k - 1];

    return dest.u;
}

template <typename T>
void 
print_bits(T num)
{
    for (size_t i = 0; i < sizeof(T)*8; i++){
        std::cout << ((num >> i) & 0b1);
        if (i == 24 || i == 16 || i == 8)
            std::cout << " ";
    }
    std::cout << std::endl;
}

#endif