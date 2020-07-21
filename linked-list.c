//Name: Mohammed Alhamadah
//Description: CSEC201 lab4 part2
//Purpose: creating a linked list

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
struct Node{
    int data;
    struct Node *next;
};
struct List{
    struct Node *head;
    int size;
};
struct List *intialize(){
    struct List *list = (struct List *)malloc(sizeof(struct List));
    list->head = NULL;
    list->size = 0;
    return list;
}

void print_oldest_helper(struct Node *pNode);

void add(struct List *list, int data) {
    struct Node *newnode = (struct Node *) malloc(sizeof(struct Node));
    newnode->data = data;
    newnode->next = list->head;
    list->head = newnode;
    list->size += 1;
}

void print(struct List *list){
    struct Node *curr = list->head;

    while(curr != NULL){
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

int delete(struct List *list, int data){
    struct Node *curr = list->head;
    struct Node *prev = NULL;

    while(curr != NULL){
        if(curr->data==data){
            if(prev==NULL){ //special case - data is found in the head node
                list->head = curr->next;
            }
            else{
                prev->next = curr->next; //general case
            }
            printf("%d is removed\n",data);
            list->size -=1;
            return 1;
        }
        prev = curr;
        curr = curr->next;
    }
    printf("%d is not found\n",data);
    return 0;
}

int delete_pos(struct List *list, int pos){
    struct Node *curr = list->head;
    struct Node *prev = NULL;
    int curr_pos =0;         // int to track the current position

    while(curr != NULL){

        if(curr_pos==pos){      // if the current position is equal to the input position delete node
            if(prev==NULL){         //special case - data is found in the head node
                list->head = curr->next;
            }
            else{
                prev->next = curr->next; //general case
            }
            printf("Data at position %d is removed\n",pos);
            list->size -=1;
            return 1;
        }
        prev = curr;
        curr = curr->next;
        curr_pos +=1;        // increment current position

    }
    printf("%d is not a valid index\n",pos);
    return 0;
}

int update(struct List *list, int pos,int newdata){
    struct Node *curr = list->head;
    int curr_pos =0;        // int to track the current position

    while(curr != NULL){

        if(curr_pos==pos){       // if the current position is equal to the input position change data with new data
            curr->data = newdata;
            printf("Data at position %d is updated\n",pos);
            return 1;
        }
        curr = curr->next;
        curr_pos +=1;     // increment current position

    }
    printf("%d is not a valid index\n",pos);
    return 0;
}

int find(struct List *list, int data){
    struct Node *curr = list->head;
    int count =0;         // int to track the number of occurrences of data in the list

    while(curr != NULL){
        if(curr->data == data){
            count+=1;         //increment count
        }
        curr = curr->next;
    }
    return count;
}

void print_oldest(struct List *list){
    struct Node *curr = list->head;  //assigned the variable curr to the head of the list
    print_oldest_helper(curr);   // pass curr to the helper function
    printf("\n");

}

void print_oldest_helper(struct Node *node) {     // helper function to reverse print
    if(node==NULL){
        return;
    }
    print_oldest_helper(node->next);   // call the function with the next node
    printf("%d ",node->data);
}



int main() {
    struct List *list = intialize();
    add(list,10);
    add(list,20);
    add(list,30);
    add(list,40);
    add(list,50);
    add(list,60);
    add(list,60);
    add(list,60);
    add(list,60);
    add(list,100);
    add(list,100);


    print(list); // return 0 if failed, 1 if success
    printf("\n");

    printf("---delete function---\n");

    delete_pos(list,0);
    print(list);
    printf("\n");

    delete_pos(list,7);
    print(list);
    printf("\n");

    delete_pos(list,12);
    print(list);
    printf("\n");

    printf("---update function---\n");
    update(list,0,1000);
    print(list);
    printf("\n");

    update(list,4,1000);
    print(list);
    printf("\n");

    update(list,12,1000);
    print(list);
    printf("\n");

    printf("---find function---\n");
    int count = find(list,60);
    printf("60 was found %d times\n",count);
    print(list);
    printf("\n");

    int count2 = find(list,23);
    printf("23 was found %d times\n",count2);
    print(list);
    printf("\n");

    printf("---reverse print function---\n");
    printf("reversed linked list: ");
    print_oldest(list);
    return 0;
}
