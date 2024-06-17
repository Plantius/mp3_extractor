#include <iostream>
#include <fstream>
#include "audio.h"

int main(int argc, char const *argv[]) 
{
    char* filename = const_cast<char*>("/home/niels/projects/mp3_wave_extractor/spotifydown.com - Luchtballon.mp3");
    if (argc > 1 && strcmp(argv[1], ""))
        filename = const_cast<char*>(argv[1]);
    std::ifstream file(filename, std::ifstream::binary);

    if (file){
        file.seekg(0, std::ios::end);
        size_t length = file.tellg();
        file.seekg(0, std::ios::beg);
        char* buffer = new char[length];

        file.read(buffer, length);
        file.close();

        audio data(buffer, length);

        if (data.valid_tag1())
            data.get_tag1().print_tag();
        if (data.valid_tag2())
            data.get_tag2().print_tag();
        data.get_frames(buffer, length);
        delete[] buffer;
    }

    return 0;
}