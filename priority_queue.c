#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef struct node node;
struct node{
        int data;
        //int priority;
        node* link;
};
void newNode(node* p,int data ){
        node* b = malloc(sizeof(node));
        b->data = data;
        b->link = p->link;
        p->link = b;
        //p = p->link;
}
void push(node** head,int data){
        node *temp = *head;
        if(data > (*head)->data )
        {
                //newNode(temp,data);
                node* b = malloc(sizeof(node));
                b->data = data;
                b->link = temp;
                (*head) = b;
        }
        else{
                        while((temp)->data > data){
                                if(((temp)->link)->data > data){
                                        (temp) = (temp)->link;
                                }
                                else{
                                        break;
                                }
                        }
                        if((temp) == NULL){
                                node* b = malloc(sizeof(node));
                                b->data = data;
                                (temp) = b;
                                b->link = NULL;
                        }
                        else{
                                newNode((temp), data);
                        }
        }

}
int main(){
        int c;
        int element;
        bool loop = true;
        printf("Enter element \n");
        //scanf("%d",&c);
        node *start,*p;
        p = malloc(sizeof(node));
        p->data = -1;
        p->link = NULL;
        start = p;
        while(loop){
                scanf("%d",&element);
                if(element == 0){
                        loop = false;
                }
                //newNode(p, element);
                else{
                        push(&start,element);
                }
                //p = p->link;
        }
        p = start;
        while(p->link != NULL){
                printf("%d\n", p->data);
                p = p->link;
        }
}
