#include <stdio.h>
#include <stdlib.h>
#include "answer07.h"

/* Determine the dimensions of the maze contain in file. */
/* The maze will always be of the correct format */
/* the number of rows is to be stored at location pointed to by nrow */ 
/* the number of ncol is to be stored at location pointed to by ncol */

void Find_maze_dimensions(FILE *fptr, int *nrow, int *ncol)
{
  //*nrow = *ncol = 0;
   	int ch;

   	int rtv = fseek(fptr, 0, SEEK_SET);
	if (rtv == -1) {
	  printf("fseek fail\n");
	  return;
	}

	while (! feof(fptr)) {
	  ch = fgetc(fptr);
	  if (ch == '\n') {
	    nrow++;
	  }
	}

	rtv = fseek(fptr, 0, SEEK_SET);
	if (rtv == -1) {
	  printf("fseek fail\n");
	  return;
	}

	do {
		ch = fgetc(fptr);
		ncol++;
	} while(ch != '\n');

	return;
}

/* Determine the column location of the top opening */
/* you may assume that the maze is of the correct format */

int Find_opening_location(FILE *fptr)
{
   	int ch;

   	int rtv = fseek(fptr, 0, SEEK_SET);
	if (rtv == -1) {
	  printf("fseek fail\n");
	  return EXIT_FAILURE;
	}

	while (! feof(fptr)) {
	  ch = fgetc(fptr);
	    if (ch == ' ') {
	      printf("The opening is at column %ld.\n", ftell(fptr)-1);
	      return ftell(fptr)-1;
	    }
	  
	}

   	return 0;
}

/* Count the number of locations that are PATH */
/* A location is PATH if it is a space, ' ', or PATH */
/* you may assume that the maze is of the correct format */

int Count_path_locations(FILE *fptr)
{
   	int ch;
   	int path = 0;

   	int rtv = fseek(fptr, 0, SEEK_SET);
	if (rtv == -1) {
	  printf("fseek fail\n");
	  return EXIT_FAILURE;
	}

	while (! feof(fptr)) {
		ch = fgetc(fptr);
		if (ch == ' ') {
			path++;
		}
	}

	printf("There are %d locations that are PATH\n", path);
   	return path;
}

/* Return the type of location: WALL or PATH */
/* The location is specified by its row-column coordinates. */
/* The coordinates are specified by row and col */
/* you may assume that these coordinates are always valid */
/* you may assume that the maze is of the correct format */

char Get_location_type(FILE *fptr, int row, int col) {
   	
   	char ch;
	int nrow = 0;
	int ncol;
	int element = 0;

	int rtv = fseek(fptr, 0, SEEK_SET);
	if (rtv == -1) {
	  printf("fseek fail\n");
	  return EXIT_FAILURE;
	}

	while (! feof(fptr)) {
	  ch = fgetc(fptr);
	  if (ch == '\n') {
	    nrow++;
	  }
	  else {
	    element++;
	  }
	}

	ncol = element / nrow;

   	rtv = fseek(fptr, ((ncol+1)*row+col), SEEK_SET);
	if (rtv != 0) {
	  printf("fseek fail\n");
	  return EXIT_FAILURE;
	}

	ch = fgetc(fptr);
	if (ch == ' ') {
		printf("At location (%d,%d), we have PATH.\n",row,col);
	}

	else {
	  printf("At location (%d,%d), we have WALL.\n",row,col);
	}

   	return ch;
}
 
/* Given a filename, re-represent the maze in the file pointer fptr */
/* in a single line */
/* The return value should be the number of characters written into the */
/* the new file */
/* if the writing to a file fails, you should return -1 */ 
/* you may assume that the maze is of the correct format */

int Represent_maze_in_one_line(char *filename, FILE *fptr)
{
   	int ch;
   	int count = 0;
	FILE *fptr1;
	fptr1 = fopen(filename,"w");

	if (fptr1 == NULL) {
	  printf("fopen fail\n");
	  return EXIT_FAILURE;
	}

   	int rtv = fseek(fptr, 0, SEEK_SET);
	if (rtv == -1) {
	  printf("fseek fail\n");
	  return EXIT_FAILURE;
	}

	while (! feof(fptr)) {
	  ch = fgetc(fptr);
	  if (ch != '\n') {
	    fputc(ch,fptr1);
	    count++;
	  }
	}

	fclose(fptr1);

   	return count;
}
