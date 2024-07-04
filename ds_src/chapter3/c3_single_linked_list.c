/*
p52 single linked list

single node operations:
1. add
2. delete
3. update
4. search
5. get length
6. enloop
7. is loop
8. delete all
*/

#include <stdio.h>
#include <malloc.h>

typedef int datatype;
struct node{
    datatype data;
    struct node* next;
};
typedef struct node node;

node* create(){
    // will return a new node
    node* newnode = NULL;
    newnode = (node *)malloc(sizeof(node));
    if (newnode == NULL){
        printf("malloc failed");
        return NULL;
    }
    newnode->next = NULL;
    return newnode;
}

void tail_insertion(datatype data,node* head){
    node* newnode = NULL;
    newnode = create();
    newnode->data = data;

    node* p = head;
    while(p->next != NULL){
        p = p->next;
    }
    p->next = newnode;

}

void head_insertion(datatype data,node* head){
    node* p = NULL;
    p = head;
    node* newnode = create();
    newnode->data = data;
    newnode->next = p->next;
    p->next = newnode;
}
void traval(node* head){
    node* p = head;
    p = p->next;  // skip head aka sentinel
    while(p != NULL){
        printf("element: %d\n",p->data);
        p = p->next;
    }
}
void delete_by_idx(int idx,node* head){
    int counter = 0;
    node* p = NULL;
    node* sentinal = NULL;
    p = head; // the fronter elem of waiting for deleted
    for(;counter < idx; counter ++){
        p=p->next;
    }
    if (p == NULL){
        printf("no element here");
        return;
    }
    sentinal = p->next;
    p->next = p->next->next;
    free(sentinal);
}
void delete_by_item(datatype elem,node* head){
    node *p = NULL;
    p = head;  // fronter elem of waiting for delete
    while(p->next != NULL && p->next->data != elem){
        p=p->next;
    }
    node* sential = p->next;
    p->next = p->next->next;
    free(sential);
}
void count_node(node *head){
    int counter = 0;
    node *p = NULL;
    p = head;
    while(p != NULL){
        p = p->next;
        counter ++;
    }
    printf("current linked list length %d, without head sential %d\n",counter,counter-1);
}
void enloop(node* head){
    // enloop will make dead loop when traval
    node *p = NULL;
    p = head;
    while(p->next != NULL){
        p = p->next;
    }
    p->next = head;
}
void isloop(node* head){
    if (head==NULL){
        printf("invaild head node\n");
        return;
    }
    if(head->next != NULL && head->next == head){
        printf("LOOP detected and it is a empty loop linked list\n");
        return;
    }
    node* p = NULL;
    node* sential = NULL;
    p = sential = head;
    p = p->next;
    while(p != sential){
        p = p->next;
        if(p == NULL){
            printf("no loop detected\n");
            return;
        }
    }
    printf("LOOP detected!\n");
    
}
void delete_all(node* head){
    node *p = NULL;
    node *sential = NULL;
    p = head->next; // has to be exist , otherwise can not deal with it
    head->next = NULL;
    while(p != NULL){
        sential = p;
        p = p->next;
        //printf("elemt %d are waiting for delete\n",sential->data);
        free(sential);
    }

}
int main(){
    node* head = NULL;
    head = create();
    head->data = -1;
    tail_insertion(0,head);
    tail_insertion(0,head);
    tail_insertion(1,head);
    tail_insertion(2,head);
    tail_insertion(3,head);
    tail_insertion(4,head);
    head_insertion(-1,head);
    head_insertion(-2,head);
    delete_by_idx(2,head);
    delete_by_item(3,head);
    delete_by_item(4,head);
    count_node(head);
    traval(head);

    isloop(head);
    enloop(head);
    isloop(head);

    node* empty_loop_ll = NULL;
    empty_loop_ll = create();
    empty_loop_ll -> next = empty_loop_ll;
    isloop(NULL);

    isloop(empty_loop_ll);

    node *newlist = create();
    tail_insertion(2,newlist);
    tail_insertion(3,newlist);
    traval(newlist);
    delete_all(newlist);
    
    traval(newlist);
    //all done
}