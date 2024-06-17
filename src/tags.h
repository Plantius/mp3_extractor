#ifndef TAGS_H
#define TAGS_H

#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include "standard.h"

const uint8_t len_v1 = 128;
const uint8_t len_v2 = 10;


struct tag_v1_header
{
    tag_v1_header() : identifier(), song_name(), artist(),
                   album(), year(), comment(), genre() {};
    char identifier[3];
    char song_name[30];
    char artist[30];
    char album[30];
    char year[4];
    char comment[30];
    char genre;
};

#pragma pack(push, 1)
struct tag_v2_header
{
    tag_v2_header() : identifier(), version(), flag(0), size(0) {};
    char identifier[3];
    char version[2];
    char flag;
    uint32_t size;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct tag_frame_header
{
    tag_frame_header() : identifier(), size(0), flags() {};
    char identifier[4];
    uint32_t size;
    char flags[2];
};
#pragma pack(pop)

struct tag_frame
{
    tag_frame(char* buffer, const size_t offset);
    void print_frame();
    tag_frame_header* header;
    // BODY
    std::string body;
    size_t frame_size = 0;
};

class tags
{
public:
    virtual void print_tag() = 0;
    virtual bool set_tag(char* buffer, const size_t size) = 0;
};


class tag_v1 : public tags
{
private:
    tag_v1_header* header;
public:
    tag_v1() {};
    tag_v1(char* buffer, const size_t size) : header()
           {if (!set_tag(buffer, size)) throw -1;};

    bool set_tag(char* buffer, const size_t size);
    void print_tag();
};

class tag_v2 : public tags
{
private:
    tag_v2_header* header;
    std::vector<tag_frame> frames;
public:
    tag_v2() : header(), frames() {};
    tag_v2(char* buffer, const size_t size) : 
           header(), frames() 
           {if (!set_tag(buffer, size)) throw -1;};

    bool set_tag(char* buffer, const size_t size);
    void print_tag();
    uint32_t get_size() {return this->header->size;};
};




#endif