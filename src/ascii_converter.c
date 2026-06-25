#include "ascii_converter.h"

//const char ascii_table[34] = " `.,'-~:;*+\"^_<=>!?|/\\()[]{}%&@$#";
const char ascii_table[34] = "#$@&%}{][)(\\/|?!>=<_^\"+*;:~-',.`"; 
const int table_length = 33; // 33 characters + \0

float random_noise(int min, int max);

char rgb_to_ascii(color c) {
	return ascii_table[(int) ((float) (c.r + c.b + c.g) / 765) * table_length];
}

char grayscale_to_ascii(uint8_t strength, unsigned int noise_strength) {
	int noise_range = noise_strength * table_length / 30;
	float noise = random_noise(-noise_range, noise_range);	

	float scalar_value = (float) (strength + noise) / 255;
	return ascii_table[(int) (scalar_value * table_length)];
}

float random_noise(int min, int max) {
	float scalar = (float) rand() / (float) RAND_MAX;
	return min + scalar * (max - min);
}

