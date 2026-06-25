#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "ascii_converter.h"
#include "image_parser.h"

bool is_char_in(char c, char* cmp) {
	for (int i = 0; i < sizeof(cmp); ++i) {
		if (c == cmp[i]) return 1;
	}
	return 0;
}

int main() {
	
	char path[60]; 
	char gscale = '0';
	bool grayscale;

	printf("Path to JPEG: ");
	fgets(path, sizeof(path), stdin);
	
	path[strcspn(path, "\n")] = 0; // Removes the railing \n.
	
	printf("Grayscale? Y/n ");
	scanf("%c", &gscale);
	
	if (is_char_in(gscale, "nN")) grayscale = 0;
	else grayscale = 1;
	
	dim size = get_jpeg_size(path);
	int component_size = grayscale ? 1 : 3;
	printf("%d, %d\n", size.width, size.height);
	
	int jpeg_array_size = size.width * size.height * component_size;
	uint8_t* tmp = malloc(jpeg_array_size);
	if (tmp == NULL) {
		printf("main() error: Could not allocate memory for decompress jpeg.");
		return 0;
	
	}
	uint8_t* image_buffer = tmp;

	jpeg_to_array(image_buffer, path, /*grayscale*/ 1);
	
	/*
	for(int i = 0; i < jpeg_array_size; ++i) {
		char c = grayscale_to_ascii(image_buffer[i], 0);

		printf("%c", c);
		if (i % size.width == 0 && i != 0) printf("\n");
	}
	*/

	array_to_jpeg(image_buffer, "/home/edvin/Pictures/compressed_image.jpeg", size, 1);


	
}
