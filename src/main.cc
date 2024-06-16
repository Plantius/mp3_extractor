#include <iostream>
#include <fstream>
#include "tags.h"


int main() 
{
    std::ifstream file("/home/niels/projects/mp3_wave_extractor/001.mp3", std::ifstream::binary);

    if (file){
        file.seekg(0, std::ios::end);
        size_t length = file.tellg();
        file.seekg(0, std::ios::beg);
        char* buffer = new char[length];

        file.read(buffer, length);
        file.close();


        // for (size_t i = 0; i < length; i++){
        //     // for (uint8_t b = 0; b < 8; b++){
        //     //     std::cout << buffer[i] << (i-6)%sizeof(this->size) & 0b1);
        //     // }std::cout << std::endl;
        // }
        tag_v1 tag1(buffer, length);
        tag_v2 tag2(buffer, length);
        tag1.print_tag();
        tag2.print_tag();
        
        delete[] buffer;
    }

    return 0;
}