#include "audio.h"

audio::audio(char* buffer, const size_t length) : tag1(), tag2(), t1(false), 
                                                        t2(false), frames()
{   
    if (strncmp(reinterpret_cast<char*>(&buffer[length-len_v1]), "TAG", 3) == 0){
        tag1 = tag_v1(buffer, length); 
        t1 = true;
    }

    if (strncmp(reinterpret_cast<char*>(buffer), "ID3", 3) == 0){
        tag2 = tag_v2(buffer, length);
        t2 = true;
    }
}


bool 
audio::get_frames(char* buffer, const size_t length)
{
    uint32_t offset = t2 ? tag2.get_size() + len_v2 : 0;
    int count = 0;
    for (uint8_t i = offset; i < length; i+=sizeof(uint32_t)){
        uint32_t* temp = reinterpret_cast<uint32_t*> (buffer[i]);            
    }
    std::cout << count << std::endl;
    return true;
}
