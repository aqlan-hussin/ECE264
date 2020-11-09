#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "answer10.h"
int main(int argc, char *argv[])
{
    FILE *in = NULL; 
    FILE *out1 = NULL;
    FILE *out2 = NULL;
    FILE *out3 = NULL;
    
    if(argc != 5)
    {
        return EXIT_FAILURE;
    }
    
    if(!(in = fopen(argv[1], "rb")))
    {
    	Error("input file couldn't be opened.");
    	return EXIT_FAILURE;
    }
    if(!(out1 = fopen(argv[2], "wb")))
    {
        Error("output file 1 couldn't be opened.");
        fclose(in);
        return EXIT_FAILURE;
    }
    if(!(out2 = fopen(argv[3], "wb")))
    {
        Error("output file 2 couldn't be opened.");
        fclose(in);
    	fclose(out1);
        return EXIT_FAILURE;
    }
    if(!(out3 = fopen(argv[4], "wb")))
    {
        Error("output file 3 couldn't be opened.");
        fclose(in);
    	fclose(out1);
    	fclose(out2);
        return EXIT_FAILURE;
    }
    
   	Encode(in, out1, out2, out3);

    fclose(in);
    fclose(out1);
    fclose(out2);
    fclose(out3);
    
    return EXIT_SUCCESS;
}