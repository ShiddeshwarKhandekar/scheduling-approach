#include<stdio.h>
#include<stdlib.h>
#include<>
typedef struct node node;
struct node{
        int data;
        int priority;
        node* link;
};
node* newNode(int data, int priority){
        node* temp = (node*)malloc(sizeof(node));
        temp->data = data;
        temp->priority = priority;
        temp->link = NULL;
        return temp;
}
void push(node** head,int data ,int priority){
        node* start = (*head);
        node* temp = newNode(data,priority);
        if((*head)->priority > priority){
                temp->link = (*head);
                (*head) = temp
        }
}
int main(){

}
