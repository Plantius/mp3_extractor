#include "audio.h"

audio::audio(const char* buffer, const size_t length) : tag1(), tag2(), t1(false), 
                                                        t2(false), frames()
{   
    if (strncmp(&buffer[length-len_v1], "TAG", 3) == 0){
        tag1 = tag_v1(buffer, length); 
        t1 = true;
    }

    if (strncmp(&buffer[0], "ID3", 3) == 0){
        tag2 = tag_v2(buffer, length);
        t2 = true;
    }
}


bool 
audio::get_frames(const char* buffer, const size_t length)
{
    uint32_t offset = t2 ? tag2.get_size() + len_v2 : 0;


}
