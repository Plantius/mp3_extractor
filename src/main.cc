#include <iostream>
#include <fstream>
#include "tags.h"


int main() 
{
    std::ifstream file("/home/niels/projects/mp3_wave_extractor/001.mp3", std::ifstream::binary);
    int frames = 0;

    if (file){
        file.seekg(0, std::ios::end);
        size_t length = file.tellg();
        file.seekg(0, std::ios::beg);
        char* buffer = new char[length];

        file.read(buffer, length);
        file.close();



        for (size_t i = 0; i < length; i++){
            uint8_t byte = buffer[i];
            if (byte == 0xff){
                if (i+1 < length && (static_cast<uint8_t>(buffer[i]) & 0xe0) == 0xe0)
                frames++;
            }
            // for (uint8_t b = 0; b < 8; b++){
            //     std::cout << ((static_cast<uint8_t> (buffer[i]) >> b) && 0b1);
            // }std::cout << " ";
        }
        tag_v1 tag1(buffer, length);
        tag_v2 tag2(buffer, length);
        tag1.print_tag();
        tag2.print_tag();
        
        std::cout << "Frames: "<< frames << " " << sizeof(tag_v1) << " " << sizeof(tag_v2) << std::endl;
        delete[] buffer;
    }

    return 0;
}