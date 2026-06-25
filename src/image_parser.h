#ifndef IMAGE_PARSER_H
#define IMAGE_PARSER_H

// skulle vara kul att skriva sin egen, men orkar inte nu. https://en.wikipedia.org/wiki/JPEG#Syntax_and_structure
// Istället är detta bara en api för libjpeg till programmet.
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
//#include "jpeg-10/jpeglib.h"
#include <jpeglib.h>
#include "color.h"

typedef struct {
	int width;
	int height;
} dim;

/**
 * Creates an array of either RGB tripplets or grayscale values, for each
 * pixel in a jpeg, locateded at jpeg_path. The buffer pointer must point
 * to an address were the decompressed image array fits. 
 * (each tripplet is 3 bytes and each grayscale value is one byte). 
**/
int jpeg_to_array(uint8_t* buffer, char* jpeg_path, bool grayscale);

/**
 * Looks the jpeg header and return the width and height of the jpeg.
**/
dim get_jpeg_size(char* jpeg_path);


// For debugging purpuses:
int array_to_jpeg(uint8_t* array, char* output_path, dim image_size, bool grayscale);

#endif
