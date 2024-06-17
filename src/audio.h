#ifndef AUDIO_H
#define AUDIO_H

#include "tags.h"

enum class MPEG {v2_5 = 0b00, reserved = 0b01, v2 = 0b10, v1 = 0b11};
enum class LAYER {reserved = 0b00, lay3 = 0b01, lay2 = 0b10, lay1 = 0b11};
enum class CRC {p = 0b00, np = 0b01};
enum class BITRATE {free = 0b0000, b32 = 0b0001, b40 = 0b0010, b48 = 0b0011,
                    b56 = 0b0100, b64 = 0b0101, b80 = 0b0110,
                    b96 = 0b0111, b112 = 0b1000, b128 = 0b1001,
                    b160 = 0b1010, b192 = 0b1011, b224 = 0b1100,
                    b256 = 0b1101, b4320 = 0b1110, BAD = 0b1111};
enum class SAMPLING_RATE {s44100 = 0b00, s48000 = 0b01, s32000 = 0b10, reserved = 0b11};
enum class PADDING {fnp = 0b00, fp = 0b01};
enum class CHANNEL {stereo = 0b00, jstereo = 0b01, dual = 0b10, mono = 0b11};
enum class MODE_EXTENSION {ninten_nms = 0b00, inten_nms = 0b01, ninten_ms = 0b10, inten_ms = 0b11};
enum class COPYRIGHT {nc = 0b00, c = 0b01};
enum class ORIGINAL {co = 0b00, o = 0b01};
enum class EMPHASIS {none = 0b00, e50_15 = 0b01, reserved = 0b10, ccit_j17 = 0b11};


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
        audio(char* buffer, const size_t length);

        bool get_frames(char* buffer, const size_t length);



        bool valid_tag1() {return t1;};
        bool valid_tag2() {return t2;};
        tag_v1 get_tag1() {return tag1;};
        tag_v2 get_tag2() {return tag2;};
};

#endif