#include <stdlib.h>
#include <stdio.h>

#include "bmp.h"

/* check whether a header is valid
 * assume that header has been read from fptr
 * the position of the indicator of fptr is not certain
 * could be at the beginning of the file, end of the file or 
 * anywhere in the file
 * note that the check is only for this exercise/assignment
 * in general, the format is more complicated
 */

int Is_BMP_Header_Valid(BMP_Header* header, FILE *fptr) {
  // Make sure this is a BMP file
  if (header->type != 0x4d42) {
     return FALSE;
  }
  // skip the two unused reserved fields

  // check the offset from beginning of file to image data
  // essentially the size of the BMP header
  // BMP_HEADER_SIZE for this exercise/assignment
  if (header->offset != BMP_HEADER_SIZE) {
     return FALSE;
  }
      
  // check the DIB header size == DIB_HEADER_SIZE
  // For this exercise/assignment
  if (header->DIB_header_size != DIB_HEADER_SIZE) {
     return FALSE;
  }

  // Make sure there is only one image plane
  if (header->planes != 1) {
    return FALSE;
  }
  // Make sure there is no compression
  if (header->compression != 0) {
    return FALSE;
  }

  // skip the test for xresolution, yresolution

  // ncolours and importantcolours should be 0
  if (header->ncolours != 0) {
    return FALSE;
  }
  if (header->importantcolours != 0) {
    return FALSE;
  }
  
  // Make sure we are getting 24 bits per pixel
  // or 16 bits per pixel
  // only for this assignment
  if (header->bits != 24 && header->bits != 16) {
    return FALSE;
  }

  // fill in extra to check for file size, image size
  // based on bits, width, and height
  int padding = ((header->bits/8) * (header->width)) % 4; 
  
  if (header->imagesize != (header->height) * ((header->width)*(header->bits)/8 + padding)) {
    return FALSE;
  }

  if (header->size != header->imagesize + BMP_HEADER_SIZE) {
    return FALSE;
  }

  return TRUE;
}

/* The input argument is the source file pointer. 
 * The function returns an address to a dynamically allocated BMP_Image only 
 * if the file * contains a valid image file 
 * Otherwise, return NULL
 * If the function cannot get the necessary memory to store the image, also 
 * return NULL
 * Any error messages should be printed to stderr
 */
BMP_Image *Read_BMP_Image(FILE* fptr) {

  // go to the beginning of the file
  int rtv = fseek(fptr, 0, SEEK_SET);
  if (rtv == -1) {
    printf("fseek fail\n");
    return NULL;
  }

   BMP_Image *bmp_image = NULL;

  //Allocate memory for BMP_Image*;
   bmp_image = malloc(sizeof(BMP_Image));
   if (bmp_image == NULL) {
    fprintf(stderr, "Error allocating memory\n");
    return NULL;
   }

  //Read the first 54 bytes of the source into the header
   if (fread(&bmp_image->header, BMP_HEADER_SIZE, 1, fptr) != 1) {
    return NULL;
   }




  // if read successful, check validity of header
   if (Is_BMP_Header_Valid(&bmp_image->header, fptr) == FALSE) {
    fprintf(stderr, "Input file not in expected format\n");
    return NULL;
   }




  // Allocate memory for image data
   bmp_image->data = malloc(bmp_image->header.imagesize);
   if (bmp_image->data == NULL) {
    fprintf(stderr, "Error allocating memory\n");
    return NULL;
   }


 
  // read in the image data
   if (fread(bmp_image->data, bmp_image->header.imagesize, 1, fptr) != 1) {
    return NULL;
   }


  return bmp_image;
}

/* The input arguments are the destination file pointer, BMP_Image *image.
 * The function write the header and image data into the destination file.
 * return TRUE if write is successful
 * FALSE otherwise
 */
int Write_BMP_Image(FILE* fptr, BMP_Image* image) 
{
   // go to the beginning of the file
  int rtv = fseek(fptr, 0, SEEK_SET);
  if (rtv == -1) {
    printf("fseek fail\n");
    return FALSE;
  }
   // write header
  if (fwrite(&image->header, BMP_HEADER_SIZE, 1, fptr) != 1) {
    return FALSE;
  }

   // write image data
  if (fwrite(image->data, image->header.imagesize, 1, fptr) != 1) {
    return FALSE;
  }

   return TRUE;
}

/* The input argument is the BMP_Image pointer. The function frees memory of 
 * the BMP_Image.
 */
void Free_BMP_Image(BMP_Image* image) {
  free(image->data);
  free(image);
  return;

}

// Given a BMP_Image, create a new 16-bit image that is newImage from a given 
// 24-bit image
//
BMP_Image *Convert_24_to_16_BMP_Image(BMP_Image *image) {
  BMP_Image *newImage = (BMP_Image *)malloc(sizeof(BMP_Image));
  //If memory allocation failed
  if (newImage == NULL)
    return NULL;
  
  //context variables
  int width = image->header.width;
  int height = image->header.height;
  
  //padding will only be 0 or 2
  int padding = width * 2 % 4;
  
  //input padding
  int inputPadding = width * 3 % 4 ? 4 - width * 3 % 4 : 0;
  
  //Setting new image header to the same information as input image header
  newImage->header = image->header;
  
  //Changing bits from 24 to 16
  newImage->header.bits = 16;
  
  //Setting new imagesize
  newImage->header.imagesize = height * (width * 2 + padding);
  
  //Setting new size
  newImage->header.size = newImage->header.imagesize + BMP_HEADER_SIZE;
  
  int i, j, k; //counters
  uint16_t pixel = 0;
  uint16_t r = 0;
  uint16_t g = 0;
  uint16_t b = 0;
  
  //Initializing newImage->data
  newImage->data = (unsigned char *)malloc(newImage->header.imagesize);
  
  //width of a row in image->data
  int inputBitWidth = width * 3 + inputPadding;
  
  for (i = 0; i < height; i++) {
    k = i * (width * 2 + padding);
    for (j = i * inputBitWidth; (j + 2) < (i + 1) * inputBitWidth; j += 3) {
      //Resetting all 16 bits of pixel to 0
      pixel = 0;
      r = 0;
      g = 0;
      b = 0;
      /*Getting rgb values from image and making them 5 bits
       *Shifting over by 10/5/0 (r/g/b) so that when bitwise OR
       *is used, no data is lost. */
      b = image->data[j] >> 3 << BLUE_BIT;
      g = image->data[j + 1] >> 3 << GREEN_BIT;
      r = image->data[j + 2] >> 3 << RED_BIT;
      //Since pixel is all zeroes, bitwise OR will just import all the asserted values
      pixel = b | g | r;
      
      //since newImage->data is an array of unsigned char (8 bits),
      //need to split each 16 bit pixel into two before writing to the array
      newImage->data[k++] = (unsigned char)pixel;
      newImage->data[k++] = (unsigned char)(pixel >> 8); //adds zeroes
    }
    
    if(padding){
      newImage->data[k++] = 0;
      newImage->data[k] = 0;
    }
  }
  
  return newImage;
}

// Given a BMP_Image, create a new 24-bit image that is newImage from a given 
// 16-bit image
//
BMP_Image *Convert_16_to_24_BMP_Image(BMP_Image *image) {
  BMP_Image *newImage = (BMP_Image *)malloc(sizeof(BMP_Image));
  //If memory allocation failed
  if (newImage == NULL)
    return NULL;
  
  //context variables
  int width = image->header.width;
  int height = image->header.height;
  
  //padding
  int padding = width * 3 % 4 ? 4 - width * 3 % 4 : 0;
  
  //input padding will only be 0 or 2
  int inputPadding = width * 2 % 4;
  
  //Setting new image header to the same information as input image header
  newImage->header = image->header;
  
  //Changing bits from 24 to 16
  newImage->header.bits = 24;
  
  //Setting new imagesize
  newImage->header.imagesize = height * (width * 3 + padding);
  
  //Setting new size
  newImage->header.size = newImage->header.imagesize + BMP_HEADER_SIZE;
  
  int i, j, k; //counters
  uint16_t pixel = 0;
  unsigned char r = 0;
  unsigned char g = 0;
  unsigned char b = 0;
  
  //Initializing newImage->data
  newImage->data = (unsigned char *)malloc(newImage->header.imagesize * sizeof(unsigned char));
  
  //width of a row in image->data
  int inputBitWidth = width * 2 + inputPadding;
  
  for (i = 0; i < height; i++) {
    k = i * (width * 3 + padding);
    for (j = i * inputBitWidth; (j + 1) < (i + 1) * inputBitWidth; j += 2) {
      //Resetting all bits of r/g/b to 0
      pixel = 0;
      r = 0;
      g = 0;
      b = 0;
      
      //Creating 16 bit pixel
      pixel = image->data[j + 1];
      pixel <<= 8;
      pixel |= image->data[j];
      
      //getting the 5 bit values
      b = (BLUE_MASK & pixel);
      g = (GREEN_MASK & pixel) >> 5;
      r = (RED_MASK & pixel) >> 10;
      
      //Getting rgb values from image and making them 8 bits
      newImage->data[k++] = ((b * 255) / 31); //b
      newImage->data[k++] = ((g * 255) / 31); //g
      newImage->data[k++] = ((r * 255) / 31); //r
    }
    //padding counter
    int pc = 0;
    
    while(pc < padding){
      newImage->data[k + pc] = 0;
      pc++;
    }
  }
  
  return newImage;
}


