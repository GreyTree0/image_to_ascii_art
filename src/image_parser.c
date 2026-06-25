//#define HAVE_PROTOTYPES
#include "image_parser.h"

int jpeg_to_array(uint8_t* buffer, char* jpeg_path, bool grayscale) {
	
	struct jpeg_error_mgr err;
	struct jpeg_decompress_struct cinfo;


	FILE* file_ptr = fopen(jpeg_path, "rb");

	if (file_ptr == NULL) {
		printf("jpeg_to_rgb_array() error: Unable to read file at: %s\n", jpeg_path);
		return 0;
	}

	cinfo.err = jpeg_std_error(&err);
	jpeg_create_decompress(&cinfo);
	
	jpeg_stdio_src(&cinfo, file_ptr);

	int header_result = jpeg_read_header(&cinfo, true);
	
	if (!header_result) {
		printf("jpeg_to_rgb_array() error: Lack of header data in jpeg. File: %s\n", jpeg_path);
		jpeg_destroy_decompress(&cinfo);
		fclose(file_ptr);
		return 0;
	}
	
	
	cinfo.out_color_space = grayscale ? JCS_GRAYSCALE : JCS_RGB;	
	
	jpeg_calc_output_dimensions(&cinfo);

	int row_width = cinfo.output_width * cinfo.output_components;
	JSAMPARRAY row_buffer = (*cinfo.mem->alloc_sarray) ((j_common_ptr) &cinfo, JPOOL_IMAGE, row_width, 1);

	(void) jpeg_start_decompress(&cinfo);	

	int current_row = 0;
	while(cinfo.output_scanline < cinfo.output_height) {		
			
		jpeg_read_scanlines(&cinfo, row_buffer, 1);
		
		memcpy(buffer + current_row * row_width, row_buffer[0], row_width);

		current_row++;

	}

	(void) jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	fclose(file_ptr);

	if(err.num_warnings != 0) {
		printf("jpeg_to_rgb_array() warning: JPEG at, %s, sucessfully decompressed but warning occured:\n warning number %ld", jpeg_path, err.num_warnings);
	}

	return 1;

}

dim get_jpeg_size(char* jpeg_path) {
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr err;

	FILE* file_ptr = fopen(jpeg_path, "r");

	if (file_ptr == NULL) {
		printf("get_jpeg_size() error: Unable to read file at: %s\n", jpeg_path);
		return (dim) {};
	}

	cinfo.err = jpeg_std_error(&err);
	jpeg_create_decompress(&cinfo);
	
	jpeg_stdio_src(&cinfo, file_ptr);

	int header_result = jpeg_read_header(&cinfo, true);

	if (!header_result) {
		printf("get_jpeg_size() error: Lack of header data in jpeg. File: %s\n", jpeg_path);
		jpeg_destroy_decompress(&cinfo);
		fclose(file_ptr);
		return (dim) {};
	}

	jpeg_calc_output_dimensions(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	fclose(file_ptr);

	return (dim) {cinfo.output_width, cinfo.output_height};	
}


int array_to_jpeg(uint8_t* array, char* output_path, dim image_size, bool grayscale) {
	
	struct jpeg_error_mgr err;
	struct jpeg_compress_struct cinfo;

	cinfo.err = jpeg_std_error(&err);
	jpeg_create_compress(&cinfo);

	FILE * output_file = fopen(output_path, "wb");
	
	if (output_file == NULL) {
		printf("array_to_jpeg() error: Could not open file at, %s\n", output_path);
		return 0;
	}
	jpeg_stdio_dest(&cinfo, output_file);

	cinfo.image_width = image_size.width;
	cinfo.image_height = image_size.height;
	cinfo.input_components = grayscale ? 1 : 3;
	cinfo.in_color_space = grayscale ? JCS_GRAYSCALE : JCS_RGB;
	jpeg_set_defaults(&cinfo);

	jpeg_start_compress(&cinfo, true);

	
	JSAMPROW row_pointer[1];
	int row_stride = cinfo.image_width * cinfo.input_components;

	while (cinfo.next_scanline < cinfo.image_height ) {
		
		row_pointer[0] = &array[cinfo.next_scanline * row_stride];
		jpeg_write_scanlines(&cinfo, row_pointer, 1);
		
	}

	jpeg_finish_compress(&cinfo);
	fclose(output_file);
	jpeg_destroy_compress(&cinfo);
	
	return 1;
}


