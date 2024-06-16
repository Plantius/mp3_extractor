#ifndef TAGS
#define TAGS

#include <iostream>
#include <vector>

const uint8_t len_v1 = 128;
const uint8_t len_v2 = 10;

struct audio_frame
{
    
};

struct tag_frame
{
    tag_frame(char* buffer, const size_t offset);
    void print_frame();
    // HEADER
    char identifier[4] = {};
    uint32_t size = 0;
    char flags[2] = {};
    
    // BODY
    std::vector<char> body;

    size_t frame_size = 0;
};



class tag_v1
{
    private:
        char identifier[3];
        char song_name[30];
        char artist[30];
        char album[30];
        char year[4];
        char comment[30];
        char genre;
    public:
        tag_v1() : identifier(), song_name(), artist(),
                   album(), year(), comment(), genre() {};
        tag_v1(char* buffer, const size_t length) : identifier(), song_name(), artist(),
                   album(), year(), comment(), genre() {set_tag(buffer, length);};

        bool set_tag(char* buffer, const size_t length);
        void print_tag();
};

class tag_v2
{
    private:
        char identifier[3];
        char version[2];
        bool unsync;
        bool ext_head;
        bool exp;
        uint32_t size;
        std::vector<tag_frame> frames;
    public:
        tag_v2() : identifier(), version(), unsync(false),
                   ext_head(false), exp(false), size(0), frames() {};
        tag_v2(char* buffer, const size_t length) : identifier(), version(), unsync(false),
                   ext_head(false), exp(false), size(0), frames() {set_tag(buffer, length);};

        bool set_tag(char* buffer, const size_t length);

        void print_tag();
};




#endif