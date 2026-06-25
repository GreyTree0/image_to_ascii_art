#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>


/**
 * Struct for an RGB tripplet.
 * (3 bytes per tripplet)
**/
typedef struct {
	uint8_t r;
	uint8_t b;
	uint8_t g;
} color;


color colors_add(color c1, color c2);


#endif
