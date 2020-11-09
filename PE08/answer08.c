#include <stdio.h>
#include <stdlib.h>
#include "answer08.h"

// if you want to declare and define new functions, do not name them
// with a prefix "__".  The instructors will be using functions with
// such names to test your individual functions.  You should not be 
// calling a function whose name has a prefix "__" because your program
// should compile without any functions from the instructors.
// you may put your additional functions here or at the end of this file



// allocate space from heap memory for the user-defined structure Maze, and
// allocate nrow x ncol maze and store the address in the structure (in 
// maze_array)
// also assign nrow and ncol fields in the structure accordingly
// if allocation fails, return NULL
// if allocation fails, you are also responsible for freeing the memory
// allocated in this function before the failure
// may assume that nrow and ncol are > 0

Maze *Allocate_maze_space(int nrow, int ncol)
{
   	Maze * maze;
	maze = malloc(sizeof(Maze));

	if (maze == NULL) {
		return NULL;
	}

	maze->nrow = nrow;
	maze->ncol = ncol;

   	return EXIT_SUCCESS;
}

// free the memory used for the maze
// you may assume that maze is not NULL, and all memory addresses are valid

void Deallocate_maze_space(Maze *maze)
{
   return;
}

/* Read maze in a multi-line file and store the necessary information */
/* into a 2D array of characters.  The address of the 2D array and the */
/* dimensions of the 2D array should be stored in a Maze structure allocated */
/* from the heap memory */
/* if the allocation fails, should return NULL */

Maze *Read_maze_from_2Dfile(FILE *fptr)
{
   	int ch;
   	int i = 0;
   	int j = 0;
   	Maze * maze;
   	maze = malloc(sizeof(Maze));

	if (maze == NULL) {
		return NULL;
	}

   	int rtv = fseek(fptr, 0, SEEK_SET);
	if (rtv == -1) {
	  	printf("fseek fail\n");
	  	return NULL;
	}

	while (! feof(fptr)) {
		ch = fgetc(fptr);
		if (ch != '\n') {
			maze->maze_array[i][j] = ch;
	    }
	    else {
	    	i++;
	    }
		j++;
	}

	maze->nrow = i;
	maze->ncol = j;
   	return maze;
}

/* Write the maze into a multi-line file */
/* the maze has to stay intact */

int Write_maze_to_2Dfile(char *filename, const Maze *maze)
{
   	int count;
   	FILE * outfptr;
   	outfptr = fopen(filename, "w");

   	if (outfptr == NULL) {
   		return EXIT_FAILURE;
   	}

   	count = fprintf(outfptr, "%p", maze->maze_array);

   	fclose(outfptr);

   	return count;
}

/* Expand the maze from nrow x ncol to (2nrow - 1) x ncol */
/* the top half of the maze is the same as the original maze */
/* the bottom half of the maze is a reflection of the original maze */
/* You have to allocate space for a new maze */
/* the nrow and ncol fields of the new maze have to be assigned accordingly */
/* if you can't expand the maze because of memory issue, NULL should be */
/* returned */
/* the original maze has to stay intact */

Maze *Expand_maze_row(const Maze *maze)
{
   	return NULL;
}

/* Expand the maze from nrow x ncol to nrow x 2ncol - 1 */
/* the left half of the maze is the same as the original maze */
/* the right half of the maze is a reflection of the original maze */
/* moreover, you have to create an opening between the left and right halves */
/* the opening should be at the middle row of the maze */
/* the opening must also be accessible from one of the paths in the */
/* new maze */
/* to do that, you have to convert some locations that are WALL to PATH */
/* starting from the new opening to the left and to the right until you reach */
/* a location that is adjacent to a location that is PATH */
/* You have to allocate space for a new maze */
/* the nrow and ncol fields of the new maze have to be assigned accordingly */
/* if you can't expand the maze because of memory issue, NULL should be */
/* returned */
/* the original maze has to stay intact */

Maze *Expand_maze_column(const Maze *maze)
{
   	return NULL;
}

// if you want to declare and define new functions, put them here
// or at the beginning of the file

