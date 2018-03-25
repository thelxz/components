#include "bits.h"
#include <string>
#include <bitset>

using std::string;
using std::bitset;

Bits::Bits(unsigned int width){
    this-> bit_data.reset();
    this-> set_width(width);
}

void Bits::set_bit_mask(unsigned int width){
    switch (width) {
    case 8:
        bit_mask = (0xFF);
        break;
    case 16:
        bit_mask = 0xFFFF;
        break;
    case 32:
        bit_mask = 0xFFFFFFFF;
        break;
    case 64:
        bit_mask = 0xFFFFFFFFFFFFFFFF;
        break;
    default:
        break;
    }
}

void Bits::set_width(unsigned int width){
    set_bit_mask(width);
    bit_data = bit_data & bit_mask;
    this->width = width;
}

void Bits::set_bit(unsigned int bit_num){
    bit_data.set(bit_num);
    bit_data &= bit_mask;
}

void Bits::clear_bit(unsigned int bit_num){
    bit_data.reset(bit_num);
    bit_data &= bit_mask;
}

void Bits::reverse_bit(unsigned  int bit_num){
    bit_data.flip(bit_num);
    bit_data &= bit_mask;
}

void Bits::set_bits(unsigned  int bit_start, unsigned  int bit_end){
    unsigned int i;
    for (i = bit_start; i<= bit_end; i++){
       bit_data.set(i);
    }
    bit_data &= bit_mask;
}

void Bits::clear_bits(unsigned  int bit_start, unsigned  int bit_end){
    unsigned int i;
    for (i = bit_start; i<= bit_end; i++){
       bit_data.reset(i);
    }
    bit_data &= bit_mask;
}

void Bits::reverse_bits(unsigned  int bit_start, unsigned int bit_end){
    unsigned int i;
    for (i = bit_start; i<= bit_end; i++){
       bit_data.flip(i);
    }
    bit_data &= bit_mask;
}

void Bits::clear_all(){
    bit_data.reset();
    bit_data &= bit_mask;
}

void Bits::set_all(){
    bit_data.set();
    bit_data &= bit_mask;
}
void Bits::reverse_all(){
    bit_data.flip();
    bit_data &= bit_mask;
}

/*             shift operate
 *
 */
void Bits::shift_arithmetic_right(unsigned  int bit_num){
    bit_num = bit_num % width;
    if (bit_data[width-1] == 0){
        bit_data = (bit_data >> bit_num);
    }
    else{
        bit_data = (bit_data >> bit_num);
        this->set_bits(width-bit_num, width-1);
    }

}

void Bits::shift_logic_right(unsigned  int bit_num){
    bit_num = bit_num % width;
    bit_data = (bit_data >> bit_num);
    bit_data &= bit_mask;
}

void Bits::shift_logic_left(unsigned  int bit_num){
    bit_num = bit_num % width;
    bit_data = (bit_data << bit_num);
    bit_data &= bit_mask;
}

void Bits::shift_rotate_right(unsigned int bit_num){
    bit_num = bit_num % width;
    int temp;
    for (;bit_num>0;bit_num--){
        temp = bit_data[0];
        bit_data >> 1;
        bit_data[width-1] = temp;
    }
}

string Bits::get_hex_string(){
    char buff[100];
    sprintf(buff,"%llX",bit_data.to_ullong());
    return string(buff);
}

string Bits::get_dec_unsigned_string(){
    char buff[100];
    sprintf(buff,"%llu",bit_data.to_ullong());
    return string(buff);
}

string Bits::get_dec_signed_string(){
    char buff[100];
    if (bit_data[width-1] == 0){
        sprintf(buff,"%lld", bit_data.to_ullong());
    }
    else{
        sprintf(buff,"%lld", (bit_data | ~ bit_mask).to_ullong());
    }
    return string(buff);
}

string Bits::get_oct_string(){
    char buff[100];
    sprintf(buff,"%llo",bit_data.to_ullong());
    return string(buff);
}

string Bits::get_bin_string(){
    return bit_data.to_string();
}

uint64_t Bits::get_data(){
    return bit_data.to_ullong();
}

void Bits::set_data(uint64_t data){
    bit_data = data;
    bit_data &= bit_mask;
}
