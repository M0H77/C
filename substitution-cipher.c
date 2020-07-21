//
//Author: Mohammed Alhamadah
//Description: CSEC201 lab3 part2
//Purpose: substitution cipher
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int main() {
    FILE *myFile;
    char filename[1000] = "";

    printf("Enter filename: ");
    scanf("%s",filename);
    getchar();

    myFile = fopen(filename, "r");
    if (myFile == NULL) {                  //check if the file opened with no errors
        printf("Error Reading File\n");
        exit(0);
    }

    char *array= (char *)malloc(1000);     //array of chars to store the cipher from file
    char *ciphertext = (char *)malloc(1000); // array of chars to store ciphered string

    int index = 0;
    while (!feof (myFile))               //store data from file and ignore spaces and new lines
    {
        char c = fgetc (myFile);
        if (!isspace (c))
            array [index++] = c;
    }
    fclose(myFile);                     // close file


    char *mystr = (char *)malloc(50);   //array of chars to store the user string
    size_t length=50;

    printf("Enter string: ");          // prompt the user for a string
    getline(&mystr,&length,stdin);



    for(unsigned long i=0; i<strlen(mystr); i++){        // replace string using the cipher

        //array = 'aAbBcCd...zZAaBbCc...' so loop on even values of j only and if equal replace with j+1
        for(unsigned long j=0; j<strlen(array)-2; j=j+2){
            if((mystr[i] >= 'A' && mystr[i] <= 'Z')||(mystr[i] >= 'a' && mystr[i]<= 'z')) {   //check if char is a letter
                if (mystr[i] == array[j]) {
                    ciphertext[i] = array[j + 1];
                }
            }
            else{
                ciphertext[i] = mystr[i];
            }
        }
    }
    printf("output is: %s\n", ciphertext);        //print the string to the screen
    return 0;
}


// gcc -ggdb -std=c99 -Wall -Wextra -pedantic -o untitled1 main.c




