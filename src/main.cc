#include <iostream>
#include <fstream>
#include "audio.h"

int main(int argc, char const *argv[]) 
{
    std::ifstream file("/home/niels/projects/mp3_wave_extractor/spotifydown.com - Luchtballon.mp3", std::ifstream::binary);

    if (file){
        file.seekg(0, std::ios::end);
        size_t length = file.tellg();
        file.seekg(0, std::ios::beg);
        char* buffer = new char[length];

        file.read(buffer, length);
        file.close();

        audio data(buffer, length);
        data.get_tag2().print_tag();
        data.get_tag1().print_tag();
        
        delete[] buffer;
    }

    return 0;
}