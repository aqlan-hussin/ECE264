#include <stdio.h>
#include <stdlib.h>
#include "answer07.h"
int main(int argc, char * argv[])
{
	FILE * fptr;
	int * nrow = 0;
	int * ncol = 0;
	if (argc < 2) {
		printf("Need to provide the file's name.\n");
		return EXIT_FAILURE;
	}
	fptr = fopen(argv[1], "r");
	if (fptr == NULL) {
		printf("fopen fail.\n");
		return EXIT_FAILURE;
	}

	Find_maze_dimensions(fptr, nrow, ncol);
	int x = Find_opening_location(fptr);
	printf("x = %d\n", x);
	int path = Count_path_locations(fptr);
	printf("path = %d\n", path);
	char ch = Get_location_type(fptr, 6, 9);
	printf("ch = %c\n", ch);
	return EXIT_SUCCESS;
}
