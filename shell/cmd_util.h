#ifndef _CMD_UTIL_H_
#define _CMD_UTIL_H_


// char/string processing prototypes.


#include <stdint.h>
#include <avr/pgmspace.h>

//Returns 1 if supplied character is letter or digit.
uint8_t is_regular_char(char x);
//The same if only digit.
uint8_t is_digit(char x);
//Returns length of string in RAM
uint8_t str_len(uint8_t* str);
//Returns length of string in FLASH
uint8_t str_len_pgm(uint8_t* pgm_str);
//Compares str in RAM with pgm_str in flash
//returns 1 if they are equal.
uint8_t str_equal_pgm(uint8_t* str,uint8_t* pgm_str);
//Converts numeric string to 16-bit integer.
//NO ERROR HANDLING, so, say, 70000 will be succesfully 
//converted, but, of course, to incorrect value.
uint16_t str_to_uint16(uint8_t *s_num);

#endif
