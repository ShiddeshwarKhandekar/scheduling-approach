#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
typedef struct node node;
struct node{
        char name;
        float priority;
        float arrival_time;
        float brust_time;
        float waiting_time;
        node* link;
};
float runnig_time = 0;
int num = 0;
void pop(node **head);
void setRunnigTime(node **head);
void setWaitingTime(node **head);
void setPriority(node **head);
void sort(node** head, node* new_node);
void priority_sort(node **head){
        node *sorted = NULL;
        node *temp = *head;
        while (temp->link != NULL)
        {
            node *tempn = temp->link;
            sort(&sorted, temp);
            temp = tempn;
        }
        if(temp->link == NULL){
                sort(&sorted, temp);
        }
        *head = sorted;
}
void sort(node** head, node* new_node){
        node* temp;
        if (*head == NULL || (*head)->priority < new_node->priority)
        {
            new_node->link = *head;
            *head = new_node;
        }
        else
        {
            temp = *head;
            while (temp->link !=NULL){
                    if(temp->link->priority > new_node->priority)
                    {
                       temp = temp->link;
                    }
                    else if(temp->link->priority == new_node->priority){
                            if(temp->link->brust_time < new_node->brust_time){
                                    temp = temp->link;
                            }
                            else{
                                    break;
                            }
                    }
                    else{
                            break;
                    }
            }
            new_node->link = temp->link;
            temp->link = new_node;
        }
}
void setRunnigTime(node **head){
        bool loop = true;
        node *temp = *head;
        while(loop){
                        if(runnig_time >= (*head)->arrival_time){
                                runnig_time = runnig_time + (*head)->brust_time;
                                pop(&(*head));
                                loop = false;
                                return;
                        }
                        else{
                                runnig_time++;
                                loop = true;
                        }
        }
        return;
}
void setWaitingTime(node **head){
        node *temp = *head;
        while(temp->link != NULL){
                temp->waiting_time = runnig_time - temp->arrival_time;
                if(temp->waiting_time < 0){
                        temp->waiting_time = 0;
                }
                temp = temp->link;
        }
        setPriority(&(*head));
        return;
}
void setPriority(node **head){
        node *temp = *head;
        while(temp->link != NULL){
                if(temp->arrival_time <= runnig_time){
                        temp->priority = 1 +(temp->waiting_time/temp->brust_time);
                }
                else{
                        temp->priority = 0;
                }
                temp = temp->link;
        }
        priority_sort(&(*head));
        return;
}
void newNode(node* p, char name,int priority,int arrival_time,int brust_time){
        node* b = malloc(sizeof(node));
        b->name = name;
        b->priority = priority;
        b->arrival_time = arrival_time;
        b->brust_time = brust_time;
        b->link = p->link;
        p->link = b;
        //p = p->link;
}
void push(node** head,char name,int priority,int arrival_time,int brust_time){
        node *temp = *head;
        if(arrival_time >= 0){
                if(arrival_time < (*head)->arrival_time )
                {
                        node* b = malloc(sizeof(node));
                        b->name = name;
                        b->priority = priority;
                        b->arrival_time = arrival_time;
                        b->brust_time = brust_time;
                        b->link = temp;
                        (*head) = b;
                }
                else{
                        while((temp)->arrival_time < arrival_time){
                                if((temp->link)->arrival_time < arrival_time){
                                        temp = temp->link;
                                }
                                else{
                                        break;
                                }
                        }
                        if((temp) == NULL){
                                node* b = malloc(sizeof(node));
                                b->name = name;
                                b->priority = priority;
                                b->arrival_time = arrival_time;
                                b->brust_time = brust_time;
                                (temp) = b;
                                b->link = NULL;
                        }
                        else{
                                newNode((temp), name, priority, arrival_time, brust_time);
                        }

                }
        }
}
void pop(node **head){
        /*printf("Process %c is processed\n waiting time: %f\n",(*head)->name,(*head)->waiting_time);
        printf("Arrival time: %f \nBrust time: %f\n Runnig time: %f\n",(*head)->arrival_time,(*head)->brust_time,runnig_time);*/
        num++;
        if(num == 1)
                printf("\n\tProcess\t Arrival\t Brust Time\t Waiting Time \n");
        printf("\n\t%c\t%f\t%f\t%f",(*head)->name,(*head)->arrival_time,(*head)->brust_time,(*head)->waiting_time);
        (*head) = (*head)->link;
        if((*head) == NULL){
                printf("head->link == NULL\n");
                return;
        }
        else{
                setWaitingTime(&(*head));
        }
        return;
}
int main(){
        int num = 0;
        char name;
        int priority;
        int arrival_time;
        int brust_time;
        int next;
        node* link;
        bool loop = true;
        printf("Enter Elements \n");
        node *start,*p;
        p = malloc(sizeof(node));
        p->name = 'p';
        p->priority = -1;
        p->arrival_time = 100000;
        p->brust_time = -1;
        p->link = NULL;
        start = p;
        while(loop){
                printf("Press 1 for next element 0 to stop: ");
                scanf("%d",&next);
                if(next == 0){
                        loop = false;
                }
                else{
                        num++;
                        printf("Enter name:");
                        scanf("%s",&name);
                        printf("Enter arrival_time:");
                        scanf("%d",&arrival_time);
                        printf("Enter brust_time:");
                        scanf("%d",&brust_time);
                        push(&start, name, 0, arrival_time, brust_time);
                        loop = true;
                }
        }
        while(start->link != NULL){
                setRunnigTime(&start);

        }
}
