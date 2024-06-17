#include "tags.h"

tag_v1_header::tag_v1_header() : identifier(), song_name(), artist(),
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

tag_v2_header::tag_v2_header() : identifier(), version(), flag(0), size(0)
{
    memset(this->identifier, 0, sizeof(this->identifier));
    memset(this->version, 0, sizeof(this->version));
}

bool 
tag_v1::set_tag(char* buffer, const size_t size)
{
    if (size < len_v1)
        return false;
    this->header = reinterpret_cast<tag_v1_header*>(&buffer[size - len_v1]);
    return true;
}

bool 
tag_v2::set_tag(char* buffer, const size_t size)
{
    if (size < len_v2)
        return false;
    size_t temp = len_v2;
    this->header = reinterpret_cast<tag_v2_header*>(buffer);
    this->header->size = swap_endian<uint32_t>(this->header->size);

    while (temp < this->header->size){
        tag_frame frame(buffer, temp);
        if (frame.frame_size == len_v2)
            break;
        frame.print_frame();
        temp += frame.frame_size;
        
        this->frames.push_back(frame);
    }

    return true;
}


tag_frame::tag_frame(char* buffer, const size_t offset) : header(nullptr), body(), frame_size(0)
{
    this->header = reinterpret_cast<tag_frame_header*>(&buffer[offset]);
    this->header->size = swap_endian<uint32_t>(this->header->size);
    
    for (size_t i = 0; i < this->header->size; i++)
        this->body.push_back(buffer[offset + sizeof(tag_frame_header) + i]);

    this->frame_size = sizeof(tag_frame_header) + this->header->size;
}


void
tag_frame::print_frame()
{   
    for (auto i : this->header->identifier)
        std::cout << i;
    std::cout << ", " << this->header->size << ", " << this->header->flags << ", ";
    
    if (this->frame_size < 10000) {
        for (auto i : this->body)
            std::cout << i;
    }    
    std::cout << std::endl;
}
void 
tag_v1::print_tag()
{
    std::cout << this->header->identifier << ", " << this->header->song_name << ", " 
              << this->header->artist << ", " << this->header->album << ", " << this->header->year 
              << ", " << this->header->comment << ", " << this->header->genre 
              << std::endl;
}

void 
tag_v2::print_tag()
{
    std::cout << this->header->identifier << ", " << this->header->version << ", " 
              << this->header->flag << ", " << this->header->size 
              << std::endl;
}