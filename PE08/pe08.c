#include <stdio.h>
#include <stdlib.h>
#include "answer08.h"
int main(int argc, char * argv[])
{
	FILE * fptr;
	int ch;
	Maze * maze = NULL;
	if (argc < 2) {
		printf("Need to provide the file's name.\n");
		return EXIT_FAILURE;
	}
	fptr = fopen(argv[1], "r");
	if (fptr == NULL) {
		printf("fopen fail.\n");
		return EXIT_FAILURE;
	}

	maze = Read_maze_from_2Dfile(fptr);
	ch = Write_maze_to_2Dfile(argv[2], maze);
	printf("%d\n", ch);
}