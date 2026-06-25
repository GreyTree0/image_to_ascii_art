#ifndef ASCII_CONVERTER_H
#define ASCII_CONVERTER_H

#include "image_parser.h"

/** 
 * Takes an rgb value and converts it to an ascii character, of equal opacity.
**/
char rgb_to_ascii(color c);


/**
 * Takes a grayscale value and convertes it to an ascci character, of equal opacity.
 * Set 'noise_stength' to zero for no noise. 
**/
char grayscale_to_ascii_noise(uint8_t stregth, unsigned int noise_strength);

char grayscale_to_ascii(uint8_t stregth);





#endif
