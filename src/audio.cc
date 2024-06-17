#include "audio.h"

audio::audio(char* buffer, const size_t size) : tag1(), tag2(), t1(false), 
                                                        t2(false), frames()
{   
    if (strncmp(reinterpret_cast<char*>(&buffer[size-len_v1]), "TAG", 3) == 0){
        tag1 = tag_v1(buffer, size); 
        t1 = true;
    }

    if (strncmp(reinterpret_cast<char*>(buffer), "ID3", 3) == 0){
        tag2 = tag_v2(buffer, size);
        t2 = true;
    }
}


bool 
audio::get_frames(char* buffer, const size_t size)
{
    size_t offset = t2 ? tag2.get_size() + len_v2 : 0;
    int count = 0;
    for (size_t i = offset; i < size; i+=sizeof(uint32_t)){
        uint32_t temp = *reinterpret_cast<uint32_t*> (&buffer[i]);  
        std::cout << i << "\t\t";  
        print_bits<uint32_t>(temp);        
    }
    std::cout << count << std::endl;
    return true;
}
