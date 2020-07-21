//Name: Mohammed Alhamadah
//Description: CSEC201 lab5 part2
//Purpose:  creating SSHA hash function
#include "hash.h"

//Write functions here

unsigned char* SSHA(const unsigned char* str, size_t size){
    //initialize the seed values
    unsigned char A= 123;
    unsigned char B= 45;
    unsigned char C= 67;
    unsigned char D= 89;
    unsigned char *digest = (unsigned char*)calloc(4,1); //initialize a digest pointer

    for (unsigned long i =0; i<size; i++){  //loop for each char in the string
        for(int j = 0; j<8;j++){         //8 rounds of operations for each char
            unsigned char old_A = A;
            unsigned char old_B = B;
            unsigned char g = (B & C) | (C & D);
            old_B = B <<1;
            old_A = A >>2;
            B = A;
            A = g +old_B+ str[i]%256;
            C = g +old_A +old_B + str[i]%256;
            D = old_A ^ old_B;
        }
    }
    digest[0] = A;
    digest[1] = B;
    digest[2] = C;
    digest[3] = D;
    return digest;
}


unsigned char* toString(struct Block *blk) {
    // string representation of point structure
    unsigned char *msg = (unsigned char *) calloc(BLOCK_SIZE, 1);
    memcpy(msg, blk, BLOCK_SIZE);
    return msg;
}


int match(unsigned char* msg1, unsigned char * msg2, int size){  //why the size

    if((msg1[0] != msg2[0]) || (msg1[1] != msg2[1]) || (msg1[2] != msg2[2]) || (msg1[3] != msg2[3]))
    {
        return 0;
    } else {
        return 1;
    }
}

void test_str(){
    char msg1[] = "Hello World!";
    unsigned char* digest1 = SSHA((unsigned char*)msg1, strlen(msg1));
    printf("digest1 = %d, %d, %d, %d\n", digest1[0], digest1[1], digest1[2], digest1[3]);

    char msg2[] = "Hello World!";
    unsigned char* digest2 = SSHA((unsigned char*)msg2, strlen(msg2));
    printf("digest2 = %d, %d, %d, %d\n", digest2[0], digest2[1], digest2[2], digest2[3]);

    printf("match = %d\n", match(digest1, digest2, DIGEST_SIZE));//1
}

void test_struct(){
    struct Block *block1 = (struct Block*) calloc(BLOCK_SIZE, 1);
    block1->height = 1;
    block1->data = 100;
    block1->prevHash = NULL;
    block1->prevBlock = NULL;

    struct Block *block2 = (struct Block*) calloc(BLOCK_SIZE, 1);
    block2->height = 2;
    block2->data = 100;
    block2->prevHash = SSHA(toString(block1), BLOCK_SIZE);
    block2->prevBlock = block1;

    unsigned char* digest1 = SSHA(toString(block1), DIGEST_SIZE);
    printf("digest1 = %d, %d, %d, %d\n", digest1[0], digest1[1], digest1[2], digest1[3]);


    unsigned char* digest2 = SSHA((unsigned char*)toString(block2), BLOCK_SIZE);
    printf("digest2 = %d, %d, %d, %d\n", digest2[0], digest2[1], digest2[2], digest2[3]);

    printf("match = %d\n", match(digest1, digest2, DIGEST_SIZE));//0

    free(block1);
    free(block2);
    free(digest1);
    free(digest2);
}
//int main(){

//    char msg1[] = "mypassword";
//    unsigned char* digest1 = SSHA((unsigned char*)msg1, strlen(msg1));
//    printf("digest1 = %d, %d, %d, %d\n", digest1[0], digest1[1], digest1[2], digest1[3]);
//
//
//    char msg2[] = "mypassword";
//    unsigned char* digest2 = SSHA((unsigned char*)msg2, strlen(msg2));
//    printf("digest2 = %d, %d, %d, %d\n", digest2[0], digest2[1], digest2[2], digest2[3]);
//
//
//    char msg3[] = "mypassword2";
//    unsigned char* digest3 = SSHA((unsigned char*)msg3, strlen(msg3));
//    printf("digest3 = %d, %d, %d, %d\n", digest3[0], digest3[1], digest3[2], digest3[3]);
//
//    printf("match digest1 and digest2 = %d\n", match(digest1, digest2, DIGEST_SIZE));//1
//    printf("match digest1 digest3 = %d\n", match(digest1, digest3, DIGEST_SIZE));//1

//    test_str();
//    test_struct();
//}

/*
 * When you uncomment the main function and run it,
 * the output should look like:
 *
 * digest1 = 230, 199, 23, 51
 * digest2 = 230, 199, 23, 51
 * match = 1
 * digest1 = 140, 48, 152, 94
 * digest2 = 86, 250, 148, 104
 * match = 0
 *
 */

/* If you use the seed value {A = 123, B = 45, C = 67, D = 89} in SSHA
 * you should get the same result above except the second value of digest2.
 * You may test with your own examples too.
 */

//gcc -ggdb -std=c99 -Wall -Wextra -pedantic -o lab5_part2 hash.c