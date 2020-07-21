#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Block{
    int height;
    int data;
    unsigned char *prevHash;
    struct Block *prevBlock;

};

struct Blockchain{
    struct Block *head;
    int size;
};

#define DIGEST_SIZE 4 //The size of SSHA output in bytes
#define BLOCK_SIZE sizeof(struct Block) // Block size in bytes

unsigned char* toString(struct Block *blk);
unsigned char* SSHA(const unsigned char* str, size_t size);
int match(unsigned char* msg1, unsigned char * msg2, int size);
