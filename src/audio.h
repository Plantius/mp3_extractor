#ifndef AUDIO_H
#define AUDIO_H

#include "tags.h"
#include "standard.h"

struct audio_frame
{

};

class audio
{
    private:
        tag_v1 tag1;
        tag_v2 tag2;
        bool t1, t2;
        std::vector<audio_frame> frames;
    public:
        audio() : tag1(), tag2(), t1(false), t2(false), 
                  frames() {};
        audio(const char* buffer, const size_t length);

        bool get_frames(void* buffer, const size_t length);



        bool valid_tag1() {return t1;};
        bool valid_tag2() {return t2;};
        tag_v1 get_tag1() {return tag1;};
        tag_v2 get_tag2() {return tag2;};
};

#endif