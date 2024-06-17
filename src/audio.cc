#include "audio.h"

audio::audio(char* buffer, const size_t size) : tag1(), tag2(), t1(false), 
                                                        t2(false), frames()
{   
    if (strncmp(reinterpret_cast<char*>(&buffer[size-len_v1]), "TAG", 3) == 0){
        tag1 = tag_v1(buffer, size); 
        t1 = true;
    }

    if (strncmp(reinterpret_cast<char*>(buffer), "ID3", 3) == 0){
        tag2 = tag_v2(buffer, size);
        t2 = true;
    }
}


bool 
audio::get_frames(char* buffer, const size_t size)
{
    size_t offset = t2 ? tag2.get_size() + len_v2 : 0;
    uint32_t temp = 0, count = 0, c = 0;
    audio_frame frame;

    std::cout << "\t\t\t" << "coeme ghc s cbit l m frame sync " << std::endl;
    for (size_t i = offset; i < size; i+=sizeof(uint32_t)){
        temp = *reinterpret_cast<uint32_t*> (&buffer[i]);  
        temp = swap_endian<uint32_t>(temp);
        if ((((temp >> 21) & 0x7ff) == 0x7ff) && (((temp >> 12) & 0xf) != 0xf) && 
            (((temp >> 10) & 0x3) != 0x3)){
            frame.mpeg = static_cast<MPEG>((temp >> 19) & 0b11);
            frame.layer = static_cast<LAYER>((temp >> 17) & 0b11);
            frame.crc = static_cast<CRC>((temp >> 16) & 0b1);
            if (frame.crc == CRC::p)
                frame.crc_sum = *reinterpret_cast<uint16_t*> (&buffer[i+4]);
            frame.bitrate = static_cast<BITRATE>((temp >> 12) & 0b1111);
            frame.sampling_rate = static_cast<SAMPLING_RATE>((temp >> 10) & 0b11);
            frame.padding = static_cast<PADDING>((temp >> 9) & 0b1);
            frame.channel = static_cast<CHANNEL>((temp >> 6) & 0b11);
            frame.mode_extension = static_cast<MODE_EXTENSION>((temp >> 4) & 0b11);
            frame.copyright = static_cast<COPYRIGHT>((temp >> 3) & 0b1);
            frame.original = static_cast<ORIGINAL>((temp >> 2) & 0b1);
            frame.emphasis = static_cast<EMPHASIS>((temp) & 0b11);
            frame.size = static_cast<uint32_t>((144 * br[int(frame.bitrate)] / sr[int(frame.sampling_rate)]) + int(frame.padding));
            this->frames.push_back(frame);
            if (frame.size != 960){
                std::cout << frame.size << "\t" << i << "\t\t";  
                print_bits<uint32_t>(temp);
            }
            count++;
        }        
    }
    std::cout << "COUNT: " << double((count -c) * 0.026) << std::endl;
    return true;
}