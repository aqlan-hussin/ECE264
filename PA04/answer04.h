#ifndef ANSWER10_H
#define ANSWER10_H

#define CHAR_RANGE  257     /* max number of character values */
#define FAKE_EOF    256     /* special value to signify end-of-file */
#define CHAR_BITS   8

/* Huffman tree structure */
typedef struct htree
{
    struct htree *left;
    struct htree *right;
    int letter;
    int freq;
} htree;

/* compare two Huffman trees based on frequency, descending order */
int CmpTrees(const void *a, const void *b);


/* create a new string with given letter concatenated on to the prefix */
char *Concat(char *prefix, char letter);


/* print specified error message and quite */
void Error(const char *msg);


/* build and return a Huffman tree based on a frequency table */
htree *BuildTree(int frequencies[]);

/* deallocate given Huffman tree */
void FreeTree(htree *tree);


/* traverse the Huffman tree to build up a table of encodings */
void TraverseTree(htree *tree, char **table, char *prefix, FILE *out1, FILE *out2);


/* build a table of Huffman encodings given a set of frequencies */
char **BuildTable(int frequencies[], FILE *out1, FILE *out2);


/* deallocate table of Huffman encodings */
void FreeTable(char *table[]);


/* output the Huffman header for an encoded file */
void WriteHeader(FILE *out1, FILE *out2, int frequencies[]);


/* write the given bit encoding to the output file */
void WriteBits(const char *encoding, FILE *out);


/* create a Huffman encoding for the file in and save the encoded version to
 * out */
void Encode(FILE *in, FILE *out1, FILE *out2, FILE *out3);

#endif
