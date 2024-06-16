#include "tags.h"

tag_v1::tag_v1() : identifier(), song_name(), artist(),
                   album(), year(), comment(), genre()
{
    memset(this->identifier, 0, sizeof(this->identifier));
    memset(this->song_name, 0, sizeof(this->song_name));
    memset(this->artist, 0, sizeof(this->artist));
    memset(this->album, 0, sizeof(this->album));
    memset(this->year, 0, sizeof(this->year));
    memset(this->comment, 0, sizeof(this->comment));
    this->genre = 0;
}

tag_v2::tag_v2() : identifier(), version(), unsync(false),
                   ext_head(false), exp(false), size(0), frames()
{
    memset(this->identifier, 0, sizeof(this->identifier));
    memset(this->version, 0, sizeof(this->version));
}

tag_v1::tag_v1(const char* buffer, const size_t length) : identifier(), song_name(), artist(),
                   album(), year(), comment(), genre()
{
    if (!set_tag(buffer, length))
        throw -1;
}

tag_v2::tag_v2(const char* buffer, const size_t length) : identifier(), version(), unsync(false),
                   ext_head(false), exp(false), size(0), frames()
{
    if (!set_tag(buffer, length))
        throw -1;
}



bool 
tag_v1::set_tag(const char* buffer, const size_t length)
{
    if (length < len_v1)
        return false;

    for (size_t i = 0; i < len_v1; i++){
        if (i <= 2)
            this->identifier[i%sizeof(this->identifier)] = buffer[length-len_v1+i];
        if (i >= 3 && i <= 32)
            this->song_name[(i-3)%sizeof(this->song_name)] = buffer[length-len_v1+i];
        if (i >= 33 && i <= 62)
            this->artist[(i-33)%sizeof(this->artist)] = buffer[length-len_v1+i];
        if (i >= 63 && i <= 92)
            this->album[(i-63)%sizeof(this->album)] = buffer[length-len_v1+i];
        if (i >= 93 && i <= 96)
            this->year[(i-93)%sizeof(this->year)] = buffer[length-len_v1+i];
        if (i >= 97 && i <= 126)
            this->comment[(i-97)%sizeof(this->comment)] = buffer[length-len_v1+i];
        if (i == 127)
            this->genre = buffer[length-len_v1+i];
    }
 
    return true;
}

bool 
tag_v2::set_tag(const char* buffer, const size_t length)
{
    if (length < len_v2)
        return false;
    size_t temp = 0;

    for (size_t i = 0; i < len_v2; i++){
        if (i <= 2)
            this->identifier[i%sizeof(this->identifier)] = buffer[i];
        if (i >= 3 && i <= 4)
            this->version[(i-3)%sizeof(this->version)] = buffer[i];
        if (i == 5){
            this->unsync = (buffer[i] >> 7) & 0b1;
            this->ext_head = (buffer[i] >> 6) & 0b1;
            this->exp = (buffer[i] >> 5) & 0b1;
        }if (i >= 6 && i <= 9){
            this->size |= ((buffer[i] << (i-6)%sizeof(this->size)) & 0b01111111); 
        }
    }

    while (temp < this->size){
        tag_frame frame(buffer, temp);
        frame.print_frame();
        temp += frame.frame_size;
        
        this->frames.push_back(frame);
    }

    return true;
}



void 
tag_v1::print_tag()
{
    std::cout << this->identifier << ", " << this->song_name << ", " 
              << this->artist << ", " << this->album << ", " << this->year 
              << ", " << this->comment << ", " << this->genre 
              << std::endl;
}

void 
tag_v2::print_tag()
{
    std::cout << this->identifier << ", " << this->version << ", " 
              << this->unsync << "-" << this->ext_head  << "-" << this->exp << ", " << this->size 
              << std::endl;
}

tag_frame::tag_frame(const char* buffer, const size_t offset)
{
    size_t start = len_v2 + offset;
    // identifier
    for (size_t i = 0; i < sizeof(this->identifier); i++)
        this->identifier[i] = buffer[start + i];
    // size
    for (uint8_t i = 0; i < sizeof(this->size); i++)
        this->size |= ((buffer[start + sizeof(this->identifier) + i] << i) & 0xff);
    // flags
    for (size_t i = 0; i < sizeof(this->flags); i++)
        this->flags[i] = buffer[start + sizeof(this->identifier) + sizeof(this->size) + i];
    // body
    for (size_t i = 0; i < this->size; i++)
        body.push_back(buffer[start + sizeof(this->identifier) + sizeof(this->size) + sizeof(this->flags) + i]);

    this->frame_size = sizeof(this->identifier) + sizeof(this->size) + sizeof(this->flags) + this->body.size();
}


void
tag_frame::print_frame()
{   
    for (auto i : this->identifier)
        std::cout << i;
    std::cout << ", " << this->size << ", " << this->flags << ", ";
    for (auto i: body)
        std::cout << i;
    std::cout << std::endl;
}