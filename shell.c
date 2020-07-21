//
//Author: Mohammed Alhamadah
//Description: CSEC201 lab6 part2
//Purpose: creating a shell
//
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <ctype.h>


// takes a pointer array and split on white space
int split(char *string[256],char *args){
    int num=0;   // this will be used to store num of arguments

    string[num] = strtok(args, " ");
    while (string[num] != NULL) {
        num++;
        string[num] = strtok(NULL, " ");
    }
    return num;
}


int main() {
    char *string = (char *) malloc(50);   //array of chars to store the user string
    char str1[] = "exit\n";

    while (1) {
        char *args[256];  // array of chars to store the arguments
        char lastArg[50];   //array of chars to store ths last argument
        int k = 0;
        size_t length = 50;
        printf("hash>> ");          // prompt the user for a args
        getline(&string, &length, stdin);

        if (strcmp(string, str1) == 0) {  //if exit break
            break;
        }

        k=split(args, string);  // call split and store the num of arguments

        strncpy(lastArg, args[k - 1], strlen(args[k - 1]));   //remove newline char from the last argument
//        printf(" k= %d  k-1= %d  strlen(args[k-1])= %lu  strlen(args[k-1])-1]= %lu\n",k,k-1,strlen(args[k-1]), strlen(args[k-1])-1);
        lastArg[strlen(args[k - 1]) - 1] ='\0';    //add '\0'
        args[k - 1] = lastArg;    //reassigned the value of the last argument in the array


        pid_t pid = fork();  // spawn a new process
        if (pid < 0) {
            printf("Fork fails\n");
        }
        else if (pid == 0) {
            execvp(args[0], args);  // pass the arguments
            exit(0);
        }
        printf("\n");
        wait(&pid);

        }
    return 0;
  }

// gcc -ggdb -std=c99 -Wall -Wextra -pedantic -o lab6 lab6-part2.c
