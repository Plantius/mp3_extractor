#include "audio.h"

audio::audio(char* buffer, const size_t length) : tag1(), tag2(), frames()
{
    tag1 = tag_v1(buffer, length); 
    tag2 = tag_v2(buffer, length);
}
