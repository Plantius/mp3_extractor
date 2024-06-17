#include "tags.h"


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
    this->header->size = swap_endian<uint32_t>(this->header->size) & 0x7F7F7F7F;

    while (temp < this->header->size){
        tag_frame frame(buffer, temp);
        if (frame.frame_size == len_v2)
            break;
        temp += frame.frame_size;
        
        this->frames.push_back(frame);
    }

    return true;
}


tag_frame::tag_frame(char* buffer, const size_t offset) : header(nullptr), body(), frame_size(0)
{
    // Header
    this->header = reinterpret_cast<tag_frame_header*>(&buffer[offset]);
    this->header->size = swap_endian<uint32_t>(this->header->size);
    // Body
    this->body.assign(&buffer[offset + sizeof(tag_frame_header)], this->header->size);
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
            std::cout << char(toascii(i));
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
    for (auto i : this->frames)
        i.print_frame();
}