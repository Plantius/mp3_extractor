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

tag_v2_header::tag_v2_header() : identifier(), version(), flag(), size(0)
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
    // for (size_t i = 0; i < len_v1; i++){
    //     if (i <= 2)
    //         this->identifier[i%sizeof(this->identifier)] = buffer[size-len_v1+i];
    //     if (i >= 3 && i <= 32)
    //         this->song_name[(i-3)%sizeof(this->song_name)] = buffer[size-len_v1+i];
    //     if (i >= 33 && i <= 62)
    //         this->artist[(i-33)%sizeof(this->artist)] = buffer[size-len_v1+i];
    //     if (i >= 63 && i <= 92)
    //         this->album[(i-63)%sizeof(this->album)] = buffer[size-len_v1+i];
    //     if (i >= 93 && i <= 96)
    //         this->year[(i-93)%sizeof(this->year)] = buffer[size-len_v1+i];
    //     if (i >= 97 && i <= 126)
    //         this->comment[(i-97)%sizeof(this->comment)] = buffer[size-len_v1+i];
    //     if (i == 127)
    //         this->genre = buffer[size-len_v1+i];
    // }
 
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
    // for (uint8_t i = 0; i < len_v2; i++){
    //     if (i <= 2)
    //         this->identifier[i%sizeof(this->identifier)] = buffer[i];
    //     if (i >= 3 && i <= 4)
    //         this->version[(i-3)%sizeof(this->version)] = buffer[i];
    //     if (i == 5){
    //         this->unsync = buffer[i] & 0b1;
    //         this->ext_head = (buffer[i] >> 1) & 0b1;
    //         this->exp = (buffer[i] >> 2) & 0b1;
    //     }
    // }
    // for (uint8_t i = sizeof(this->size); i > 0; i--)
    //     this->size |= ((buffer[6 + i-1] & 0xfe) << (sizeof(this->size)-i)*8);


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


tag_frame::tag_frame(char* buffer, const size_t offset)
{
    this->header = reinterpret_cast<tag_frame_header*>(&buffer[offset]);
    this->header->size = swap_endian<uint32_t>(this->header->size);
    // identifier
    // for (size_t i = 0; i < sizeof(this->identifier); i++)
    //     this->identifier[i] = buffer[offset + i];
    // size
    // for (uint8_t i = sizeof(this->header->size); i > 0; i--){
    //     this->header->size |= ((static_cast<uint8_t>(buffer[offset + sizeof(this->header->identifier) + i - 1]) & 0xff) << (sizeof(this->header->size)-i)*8);
    // }
    // // flags
    // for (size_t i = 0; i < sizeof(this->flags); i++)
    //     this->flags[i] = buffer[offset + sizeof(this->identifier) + sizeof(this->size) + i];
    // body

    for (size_t i = 0; i < this->header->size; i++)
        body.push_back(buffer[offset + sizeof(tag_frame_header) + i]);

    this->frame_size = sizeof(tag_frame_header) + this->body.size();
}


void
tag_frame::print_frame()
{   
    for (auto i : this->header->identifier)
        std::cout << i;
    std::cout << ", " << this->header->size << ", " << this->header->flags << ", ";
    // for (auto i: body)
    //     std::cout << i;
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