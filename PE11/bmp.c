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
  if (header->imagesize != (header->height) * (header->width)) {
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
    return NULL;
   }




  // Allocate memory for image data
   bmp_image->data = malloc(sizeof(unsigned char)*((bmp_image->header.size)-BMP_HEADER_SIZE));
   if (bmp_image->data == NULL) {
    fprintf(stderr, "Error allocating memory\n");
    return NULL;
   }


 
  // read in the image data


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
  if (fwrite(&image->data, sizeof(unsigned char), 1, fptr) != 1) {
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

// Given a BMP_Image, create a new image that is a reflection 
// of the given image
// It could be a horizontal reflection (with the vertical mirror 
// being placed at the center of the image) 
// It could be a vertical reflection (with the horizontal mirror
// being placed at the center of the image)
// It could be a horizontal reflection followed by a vertical
// reflection (or equivalently, a vertical reflection followed by
// horizontal reflection).
// hrefl == 1 implies that a horizontal reflection should take place
// hrefl == 0 implies that a horizontal reflection should not take place
// vrefl == 1 implies that a vertical reflection should take place
// vrefl == 0 implies that a vertical reflection should not take place

BMP_Image *Reflect_BMP_Image(BMP_Image *image, int hrefl, int vrefl)
{
   // create a new image reflected from the given image
   BMP_Image *t_image = NULL;
   //int row;
   //int col;

   /*if (hrefl == 1) {
      for (row = 0; row < (image->header.height); row++) {
        for (col = 0; col < (image->header.width)/2; col++) {*/
          t_image = image;
   /*     }
      } 
   }*/

   /*if (vrefl == 1) {
      for (row = 0; row < (image->header.height)/2; row++) {
        for (col = 0; col < (image->header.width); col++) {*/
          t_image = image;
   /*     }
      }
   }*/

   return t_image;
}

