//Name: Mohammed Alhamadah
//Description: CSEC201 lab5 part2
//Purpose: creating functions for Blockchain and Block data structure
#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include <time.h>
//
// Write functions here
//

struct Blockchain *initialize(){
    struct Blockchain *blockchain = (struct Blockchain *)malloc(sizeof(struct Blockchain)); //create a blkchian pointer
    blockchain->head= NULL;   //set the head to null
    blockchain->size= 0;
    return blockchain;
}



void add(struct Blockchain *blockchain, int data) {
    struct Block *newblock = (struct Block *) malloc(BLOCK_SIZE); //create a blkchian pointer
    if(blockchain->size==0){   //if the blockchain empty
        newblock->height = 1;
        newblock->prevHash=NULL;
    } else{
        newblock->height = blockchain->head->height+1;
        newblock->prevHash = SSHA(toString(blockchain->head), BLOCK_SIZE);
    }
    newblock->data = data;
    newblock->prevBlock=blockchain->head;   //set the prevBlock to the old head

    blockchain->head = newblock;     //set the head to the new block
    blockchain->size += 1;
}



void print_chain(struct Blockchain *blockchain){
    struct Block *curr = blockchain->head;

    while(curr != NULL){
        printf("[%d: %d], ",curr->height, curr->data);
        curr = curr->prevBlock;
    }
    printf("\n");
}

//attacks functions:

int delete(struct Blockchain *blockchain, int height){
    struct Block *curr = blockchain->head; //set curr to the blkchain head
    struct Block *prev_curr = NULL;    //prev_curr will track the block before curr. at the start it's null

    while(curr != NULL){
        if(curr->height==height){    // check if the block has the same height
            if(prev_curr==NULL){    //special case - data is found in the head node
                blockchain->head= curr->prevBlock;
            } else{
                prev_curr->prevBlock = curr->prevBlock; //general case
            }
            printf("Block %d is deleted\n", height);
            blockchain->size -=1;
            return 1;
        }
        prev_curr = curr;   //set prev_curr to curr
        curr = curr->prevBlock; //set curr to the next bock (prevblock)
    }
    printf("Block %d not found\n", height);
    return 0;
}


int alter_block(struct Blockchain *blockchain, int height, int data){
    struct Block *curr = blockchain->head;

    while(curr != NULL){
        if(curr->height==height){    //check if the block has the same height
            curr->data=data;

            printf("block %d is altered\n",curr->height);
            return 1;
        }
        curr = curr->prevBlock;
    }
    printf("block %d not found\n", height);
    return 0;

}


int alter_2_blocks(struct Blockchain *blockchain, int height, int data){
    struct Block *curr = blockchain->head;
    struct Block *prev_curr = NULL;

    while(curr != NULL){
        if(curr->height==height){
            if(prev_curr==NULL){   //special case data found in the head. no prevhash to alter
                curr->data=data;
                printf("Data in block %d is altered.\n",curr->height);
                printf("head case no prev block.\n");
                return 1;

            } else{    //general case
                curr->data=data;
                prev_curr->prevHash = SSHA(toString(curr), BLOCK_SIZE);  //change the hash saved in the prev_curr to the
            }                                                            //new hash of curr
            printf("Data in block %d is altered.\n",curr->height);
            printf("PrevHash in block %d is altered.\n",prev_curr->height);

            return 1;
        }
        prev_curr = curr;
        curr = curr->prevBlock;

    }
    printf("block %d not found\n", height);
    return 0;

}


void verify_chain(struct Blockchain *blockchain) {     
    struct Block *curr = blockchain->head;
    unsigned char *digest;

    if(curr->prevBlock == NULL){  //if the blockchain has only one block, exit
        return;
    }
    while(curr != NULL && curr->prevHash!=NULL){
        digest = SSHA(toString(curr->prevBlock), BLOCK_SIZE);   //compute a new hash for curr->prevBlock
       if(match(curr->prevHash,digest,DIGEST_SIZE)!=1){        //compare the hash with hash saved in curr

            printf("Verification failed at block %d\n", curr->prevBlock->height);
            return;
        }
        curr = curr->prevBlock;
    }
    printf("All blocks have been verified.\n");
}





int main(){

    struct Blockchain *blockchain = initialize();
    for (int i = 1; i<=20; i++){
        add(blockchain, 10*i);
    }
    printf("\n");
    print_chain(blockchain);
    verify_chain(blockchain);

    /* Uncomment only one of the three functions at a time*/
//    delete(blockchain, 5);
//    alter_block(blockchain, 5, 5000);
    alter_2_blocks(blockchain, 5, 5000);

    verify_chain(blockchain);
    print_chain(blockchain);


    //test
    struct Blockchain *blockchain2 = initialize();
    for (int i = 1; i<=7; i++){
        add(blockchain2, 10*i);
    }

    struct Blockchain *blockchain3 = initialize();
    for (int i = 1; i<=7; i++){
        add(blockchain3, 10*i);
    }


    struct Blockchain *blockchain4 = initialize();
    for (int i = 1; i<=7; i++){
        add(blockchain4, 10*i);
    }

    //tests cases for each function
    printf("\n");
    printf("***********************************************[+]delete function[+]***********************************************\n");
    print_chain(blockchain2);
    verify_chain(blockchain2);
    printf("\n");
    delete(blockchain2, 1);
    verify_chain(blockchain2);
    print_chain(blockchain2);
    printf("\n");
    delete(blockchain2, 5);
    verify_chain(blockchain2);
    print_chain(blockchain2);
    printf("\n");
    delete(blockchain2, 7);
    verify_chain(blockchain2);
    print_chain(blockchain2);
    printf("\n");
    delete(blockchain2, 22);
    verify_chain(blockchain2);
    print_chain(blockchain2);
    printf("\n");


    printf("***********************************************[+]alter function[+]***********************************************\n");
    print_chain(blockchain3);
    verify_chain(blockchain3);
    printf("\n");
    alter_block(blockchain3, 1,5000);
    verify_chain(blockchain3);
    print_chain(blockchain3);
    printf("\n");
    alter_block(blockchain3, 5,5000);
    verify_chain(blockchain3);
    print_chain(blockchain3);
    printf("\n");
    alter_block(blockchain3, 7,5000);
    verify_chain(blockchain3);
    print_chain(blockchain3);
    printf("\n");
    alter_block(blockchain3, 22,5000);
    verify_chain(blockchain3);
    print_chain(blockchain3);
    printf("\n");



    printf("***********************************************[+]alter 2 block function[+]***********************************************\n");
    print_chain(blockchain4);
    verify_chain(blockchain4);
    printf("\n");
    alter_2_blocks(blockchain4, 1,5000);
    verify_chain(blockchain4);
    print_chain(blockchain4);
    printf("\n");
    alter_2_blocks(blockchain4, 5,5000);
    verify_chain(blockchain4);
    print_chain(blockchain4);
    printf("\n");
    alter_2_blocks(blockchain4, 7,5000);  //bug here
    verify_chain(blockchain4);
    print_chain(blockchain4);
    printf("\n");
    alter_2_blocks(blockchain4, 22,5000);
    verify_chain(blockchain4);
    print_chain(blockchain4);
    printf("\n");

    return 0;
}



//Output
/*
 [20: 200], [19: 190], [18: 180], [17: 170], [16: 160], [15: 150], [14: 140], [13: 130], [12: 120], [11: 110], [10: 100], [9: 90], [8: 80], [7: 70], [6: 60], [5: 50], [4: 40], [3: 30], [2: 20], [1: 10],
 All blocks have been verified.
 Block 5 is deleted
 Verification failed at block 6.
 [20: 200], [19: 190], [18: 180], [17: 170], [16: 160], [15: 150], [14: 140], [13: 130], [12: 120], [11: 110], [10: 100], [9: 90], [8: 80], [7: 70], [6: 60], [4: 40], [3: 30], [2: 20], [1: 10],
*/

/*
 [20: 200], [19: 190], [18: 180], [17: 170], [16: 160], [15: 150], [14: 140], [13: 130], [12: 120], [11: 110], [10: 100], [9: 90], [8: 80], [7: 70], [6: 60], [5: 50], [4: 40], [3: 30], [2: 20], [1: 10],
 All blocks have been verified.
 block 5 is altered.
 Verification failed at block 5.
 [20: 200], [19: 190], [18: 180], [17: 170], [16: 160], [15: 150], [14: 140], [13: 130], [12: 120], [11: 110], [10: 100], [9: 90], [8: 80], [7: 70], [6: 60], [5: 5000], [4: 40], [3: 30], [2: 20], [1: 10],
 */

/*
print_chain():
 [20: 200], [19: 190], [18: 180], [17: 170], [16: 160], [15: 150], [14: 140], [13: 130], [12: 120], [11: 110], [10: 100], [9: 90], [8: 80], [7: 70], [6: 60], [5: 50], [4: 40], [3: 30], [2: 20], [1: 10],
 All blocks have been verified.
 Data in block 5 is altered.
 PrevHash in block 6 is altered.
 Verification failed at block 6.
 [20: 200], [19: 190], [18: 180], [17: 170], [16: 160], [15: 150], [14: 140], [13: 130], [12: 120], [11: 110], [10: 100], [9: 90], [8: 80], [7: 70], [6: 60], [5: 5000], [4: 40], [3: 30], [2: 20], [1: 10],
 */
//gcc -o lab5_part2 hash.c blockchain.c