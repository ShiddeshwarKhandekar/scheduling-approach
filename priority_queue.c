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
//int num = 0;
//void push()
void pop(node **head);
void setRunnigTime(node **head);
void setWaitingTime(node **head);
void setPriority(node **head);
void sortedInsert(node** head, node* new_node);
void priority_sort(node **head){
        printf("priority sort\n");
        node *sorted = NULL;

    // Traverse the given linked list and insert every
    // node to sorted
    node *current = *head;
    while (current->link != NULL)
    {
        // Store next for next iteration
        node *next = current->link;

        // insert current in sorted linked list
        sortedInsert(&sorted, current);

        // Update current
        current = next;
    }
    if(current->link == NULL){
            sortedInsert(&sorted, current);
    }
    // Update head_ref to point to sorted linked list
    *head = sorted;
    while(sorted != NULL){
            printf("n: %c",sorted->name);
            sorted = sorted->link;
    }
}
void sortedInsert(node** head, node* new_node)
{
        printf("sorted insert\n");
    node* current;
    /* Special case for the head end */
    if (*head == NULL || (*head)->priority < new_node->priority)
    {
            //(*head)->link = new_node->link;
        new_node->link = *head;
        //new_node->link = *head;
        *head = new_node;
    }
    else
    {
        /* Locate the node before the point of insertion */
        current = *head;
        while (current->link !=NULL){
                if(current->link->priority > new_node->priority)
                {
                   current = current->link;
                }
                else if(current->link->priority == new_node->priority){
                        if(current->link->brust_time < new_node->brust_time){
                                current = current->link;
                        }
                        else{
                                break;
                        }
                }
                else{
                        break;
                }
        }
        new_node->link = current->link;
        current->link = new_node;
    }

}
void setRunnigTime(node **head){
        printf("set Runnig\n");
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
                //loop = false;
        }
        return;
}
void setWaitingTime(node **head){
        printf("set waiting\n");
        node *temp = *head;
        while(temp->link != NULL){
                temp->waiting_time = runnig_time - temp->arrival_time;
                if(temp->waiting_time < 0){
                        temp->waiting_time = 0;
                }
                printf("name: %c waiting: %f\n",temp->name,temp->waiting_time);
                temp = temp->link;
        }
        setPriority(&(*head));
        return;
}
void setPriority(node **head){
        printf("set priority\n");
        node *temp = *head;
        while(temp->link != NULL){
                if(temp->arrival_time <= runnig_time){
                        temp->priority = 1 +(temp->waiting_time/temp->brust_time);
                }
                else{
                        temp->priority = 0;
                }
                printf("name: %c priotrity: %f\n",temp->name,temp->priority);
                temp = temp->link;
        }
        priority_sort(&(*head));
        return;
}
void newNode(node* p, char name,int priority,int arrival_time,int brust_time){
        node* b = malloc(sizeof(node));
        b->name = name;
        //b->name = malloc(strlen(name));
        //strcpy(b->name,name);
        b->priority = priority;
        b->arrival_time = arrival_time;
        b->brust_time = brust_time;
        b->link = p->link;
        p->link = b;
        //p = p->link;
}
void push(node** head,char name,int priority,int arrival_time,int brust_time){
        //printf("%c\n",name);
        node *temp = *head;
        if(arrival_time >= 0){
                if(arrival_time < (*head)->arrival_time )
                {
                        //newNode(temp,data);
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
        printf("pop\n");
        printf("Process %c is processed\n waiting time: %f\n",(*head)->name,(*head)->waiting_time);
        printf("Arrival time: %f \nBrust time: %f\n Runnig time: %f\n",(*head)->arrival_time,(*head)->brust_time,runnig_time);
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
        printf("Enter element \n");
        //scanf("%d",&c);
        node *start,*p;
        p = malloc(sizeof(node));
        p->name = 'p';
        p->priority = -1;
        p->arrival_time = 100000;
        p->brust_time = -1;
        p->link = NULL;
        start = p;
        while(loop){
                printf("Press 1 for next element 0 to stop");
                scanf("%d",&next);
                if(next == 0){
                        loop = false;
                }
                //newNode(p, element);
                else{
                        num++;
                        printf("Enter name:");
                        scanf("%s",&name);
                        //printf("Enter priority:");
                        //scanf("%d",&priority);
                        printf("Enter arrival_time:");
                        scanf("%d",&arrival_time);
                        printf("Enter brust_time:");
                        scanf("%d",&brust_time);
                        push(&start, name, 0, arrival_time, brust_time);
                        loop = true;
                }
                //p = p->link;
        }
        printf("NUM %d\n",num);
        //p = start;
        while(start->link != NULL){
                printf("before\n");
                setRunnigTime(&start);
                printf("after \n");
                //p = start;
                num--;
        }
        printf("a\n");
        /*p = start;
        while(p->link != NULL){
                printf("Name: %c\n",p->name);
                printf("Priority%d\n", p->priority);
                printf("Arrival time %d\n",p->arrival_time);
                printf("Brust time %d\n",p->brust_time);
                p = p->link;
        }*/
}
