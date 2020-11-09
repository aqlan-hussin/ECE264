#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"

int main(int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "Wrong number of arguments\n");
		return EXIT_FAILURE;
	}

	FILE* input = fopen(argv[1], "r");
	if (input == NULL) {
		fprintf(stderr, "Can't open input file\n");
		return EXIT_FAILURE;
	}

	BMP_Image* image = Read_BMP_Image(input);

	if (image == NULL) {
		fprintf(stderr, "Can't read image from file\n");
		fclose(input);
		return EXIT_FAILURE;
	}
	
	BMP_Image *outputImage;

	if (image->header.bits == 24) {
		outputImage = Convert_24_to_16_BMP_Image_with_Dithering(image);
	}

	if (image->header.bits == 16) {
		outputImage = Convert_16_to_24_BMP_Image(image);
	}

	FILE* output = fopen(argv[2], "w");
	if (output == NULL) {
		fprintf(stderr, "Can't open file for output\n");
		fclose(input);
		return EXIT_FAILURE;
	}
	

	if (Write_BMP_Image(output, outputImage) == FALSE) {
		fprintf(stderr, "Error writing to output file\n");
		fclose(input);
		fclose(output);
		return EXIT_FAILURE;
	}

	Free_BMP_Image(image);
	Free_BMP_Image(outputImage);
	fclose(input);
	fclose(output);
	
	return EXIT_SUCCESS;
}