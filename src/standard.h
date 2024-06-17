#ifndef STANDARD_H
#define STANDARD_H
#include <iostream>

template <typename T>
void 
print_bits(T num)
{
    for (size_t i = 0; i < sizeof(T)*4; i++)
        std::cout << ((num >> i) & 0b1);
    std::cout << std::endl;
}

#endif