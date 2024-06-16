#ifndef AUDIO_H
#define AUDIO_H

#include "tags.h"

struct audio_frame
{

};

class audio
{
    private:
        tag_v1 tag1;
        tag_v2 tag2;
        std::vector<audio_frame> frames;
    public:
        audio() : tag1(), tag2(), frames() {};
        audio(char* buffer, const size_t length);

        tag_v1 get_tag1() {return tag1;};
        tag_v2 get_tag2() {return tag2;};


};



#endif