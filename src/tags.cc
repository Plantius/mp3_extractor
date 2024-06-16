#include "tags.h"


bool 
tag_v1::set_tag(char* buffer, const size_t length)
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
tag_v2::set_tag(char* buffer, const size_t length)
{
    if (length < len_v2)
        return false;

    for (size_t i = 0; i < len_v2; i++){
        if (i <= 2)
            this->identifier[i%sizeof(this->identifier)] = buffer[i];
        if (i >= 3 && i <= 4)
            this->version[(i-3)%sizeof(this->version)] = buffer[i];
        if (i == 5){
            this->unsync = (buffer[i] >> 7) & 0b1;
            this->ext_head = (buffer[i] >> 6) & 0b1;
            this->exp = (buffer[i] >> 5) & 0b1;
        }if (i >= 6 && i <= 9)
            this->size |= ((buffer[i] << (i-6)%sizeof(this->size)) & 0b01111111); 
    }
    while (size_t j = 0; j < )
    for (size_t j = 0; j < this->size; j++){

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
              << this->unsync << ", " << this->ext_head  << ", " << this->exp << ", " << this->size 
              << std::endl;
}