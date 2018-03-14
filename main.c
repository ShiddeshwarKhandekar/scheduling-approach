#include<stdio.h>
#include<stdlib.h>
typedef struct node node;
struct node{
        int data;
        int priority;
        node* link;
};

int main(){
        int c;
        int num = 1;
        printf("Enter elements");
        scanf("%d",&c);
        node *p,*ptr,*start;
        start = (node*)malloc(sizeof(node));
        start->link = NULL;
        start->data = c;
        ptr = start;
        //n = n->link;
        while(num != 0){
                node* b = (node*)malloc(sizeof(node));
                ptr->link = b;
                b->link = NULL;
                scanf("%d",&num);
                ptr->data = num;
                ptr = ptr->link;
        }
        ptr->link = NULL;
        ptr = start;
        //printf("%d",start->data);
        while(ptr != NULL){
                printf("%d",ptr->data);
                ptr = ptr->link;
        }
}
