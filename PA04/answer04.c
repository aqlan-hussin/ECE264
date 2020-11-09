#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "answer04.h"

/* compare two Huffman trees based on frequency, descending order */
int CmpTrees(const void *a, const void *b)
{
    const htree **x = (const htree **) a; 
    const htree **y = (const htree **) b;
    if((*x)->freq == (*y)->freq) 
    {
    	return 0;
    }
    /*else 
    {
    	return ((*x)->freq < (*y)->freq) ? 1 : -1;
    }*/
    if((*x)->freq < (*y)->freq) 
    {
        return 1;
    }
    return -1;    
}

/* create a new string with given letter concatenated on to the prefix */
char *Concat(char *prefix, char letter)
{
    char *result = (char *)malloc(strlen(prefix) + 2);
    sprintf(result, "%s%c", prefix, letter);
    return result;
}

/* print specified error message and quite */
void Error(const char *msg)
{
    fprintf(stderr, "Error: %s\n", msg);
    exit(1);
}

/* build and return a Huffman tree based on a frequency table */
htree *BuildTree(int frequencies[])
{
    int i, len = 0;
    htree *queue[CHAR_RANGE];
    
    /* create trees for each character, add to the queue */
    for(i = 0; i < CHAR_RANGE; i++)
    {
        if(frequencies[i])
        {
            htree *toadd = (htree *)calloc(1, sizeof(htree));
            toadd->letter = i;
            toadd->freq = frequencies[i];
            //printf("%c %d\n", i, frequencies[i]);
            queue[len++] = toadd;
        }
    }
    
    while(len > 1)
    {
        htree *toadd = (htree *)malloc(sizeof(htree));
        
        /* sort - smallest frequency trees are last */
        qsort(queue, len, sizeof(htree *), CmpTrees);
        
        /* dequeue two lowest frequency trees, build new tree from them */
        toadd->left = queue[--len];
        toadd->right = queue[--len];
        toadd->freq = toadd->left->freq + toadd->right->freq;
        
        queue[len++] = toadd; /* insert back in the queue */
    }
    
    return queue[0]; /* last tree in the queue is the full Huffman tree */
}

/* deallocate given Huffman tree */
void FreeTree(htree *tree)
{
    if(tree)
    {
        FreeTree(tree->left);
        FreeTree(tree->right);
        free(tree);
    }
}

/* traverse the Huffman tree to build up a table of encodings */
void TraverseTree(htree *tree, char **table, char *prefix, FILE *out1, FILE *out2)
{
    if(!tree->left && !tree->right)
    { 
    	table[tree->letter] = prefix;
        fprintf(out1, "%c:%s\n", tree->letter, prefix);
        fprintf(out2, "%d%c", 1, tree->letter);
    }
    else
    {
        if(tree->left) TraverseTree(tree->left, table, Concat(prefix, '0'), out1, out2);
        if(tree-> right) TraverseTree(tree->right, table, Concat(prefix, '1'), out1, out2);
        fprintf(out2, "%d", 0);
        free(prefix);
    }
}

/* build a table of Huffman encodings given a set of frequencies */
char **BuildTable(int frequencies[], FILE *out1, FILE *out2)
{
    static char *table[CHAR_RANGE];
    char *prefix = (char *)calloc(1, sizeof(char));
    htree *tree = BuildTree(frequencies);
    TraverseTree(tree, table, prefix, out1, out2);
    FreeTree(tree);
    
    return table;
}

/* deallocate table of Huffman encodings */
void FreeTable(char *table[])
{
    int i;
    for(i = 0; i < CHAR_RANGE; i++) if(table[i]) free(table[i]);
}

/* output the Huffman header for an encoded file */
void WriteHeader(FILE *out1, FILE *out2, int frequencies[])
{
    int i; 
    //int count = 0;
    
    //for(i = 0; i < CHAR_RANGE; i++) if(frequencies[i]) count++;
    //fprintf(out, "%d\n", count);
    
    for(i = 0; i < CHAR_RANGE-1; i++) 
    {
        //if(frequencies[i]) {fprintf(out2, "%d%c", 1, (char)(i));}
        //if(!frequencies[i]) {fprintf(out2, "%d", 0);}
    }
}


/* write the given bit encoding to the output file */
void WriteBits(const char *encoding, FILE *out)
{
    /* buffer holding raw bits and number of bits filled */
    static int bits = 0, bitcount = 0;
    
    while(*encoding)
    {
        /* push bits on from the right */
        bits = bits * 2 + *encoding - '0';
        bitcount++;
        
        /* when we have filled the char, output as a single character */
        if(bitcount == CHAR_BITS)
        {
            fputc(bits, out);
            bits = 0;
            bitcount = 0;
        }
        
        encoding++;
    }
}



/* create a Huffman encoding for the file in and save the encoded version to
 * out */
void Encode(FILE *in, FILE *out1, FILE *out2, FILE *out3)
{
    int c, frequencies[CHAR_RANGE] = { 0 };
    char **table;
    
    
    while((c = fgetc(in)) != EOF) 
    {
        frequencies[c]++;
        //printf("%c",(char)c);
    }
    
    frequencies[FAKE_EOF] = 1;
    rewind(in);
    
    table = BuildTable(frequencies, out1, out2);
    WriteHeader(out1, out2, frequencies);
    
    
    while((c = fgetc(in)) != EOF)
        WriteBits(table[c], out3);
    
    /* use FAKE_EOF to indicate end of input */
    WriteBits(table[FAKE_EOF], out3);
    
    /* write an extra 8 blank bits to flush the output buffer */
    WriteBits("0000000", out3);

    
    FreeTable(table);
}
