#pragma once
#include<cstdint>
//The opcode extractor
inline uint8_t get_opcode(uint16_t instruction){
    return instruction>>12;
}

inline uint16_t sign_extend(uint16_t x,int bit_count){
    int neg=(x>>(bit_count-1))&1;//&1 to ignore stray bits
    if(neg)return x|(0xFFFF<<bit_count);
    else return x;
}

inline uint16_t swap16(uint16_t x){
    return (x<<8)|(x>>8);
}