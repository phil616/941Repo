/*
p57 3.3.3
bidirectional linked list

bidirectional linked list operations:
1~4: curd
5: get length
6: delete
*/

#include <stdio.h>
#include <malloc.h>
typedef int datatype;
struct bidirectional_node{
    datatype data;
    struct bidirectional_node *next;
    struct bidirectional_node *prev;
};
typedef struct bidirectional_node node;

node* create(){
    node* new_node = NULL;
    new_node = (node*)malloc(sizeof(node));
    if (new_node == NULL){
        printf("error when alloc\n");
        return NULL;
    }
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}


void head_insertion(node* h,datatype data){
    node* new_node = NULL;
    new_node = create();
    // reassign new node and protect main chain
    new_node->next = h->next;
    new_node->prev = h;
    new_node->data = data;
    // insert to chain
    if (new_node->next != NULL)
        new_node->next->prev = new_node;
    h->next = new_node;
}
void tail_insertion(node *h,datatype data){
    node *p;
    p = h;
    while(p->next != NULL){
        p = p->next;
    }
    // p is the last node; p.n = NULL, p,d p.p
    node *new_node = NULL;
    new_node = create();
    new_node->next = p->next;  // which is nullptr
    new_node->prev = p;       
    new_node->data = data;

    p->next = new_node;
    
}

void get_length(node* h){
    int counter = 0;
    if (h->next == NULL){
        printf("current ll is %d\n",counter);
        return;
    }
    node *p = NULL;
    p = h;
    while(p != NULL){
        p=p->next;
        counter++;
    }
    printf("current ll is %d\n",counter - 1);
}
void delete_by_idx(node *h, int idx){
    int i;
    node* p = NULL;
    p = h->next;
    // p is elem waiting for deleted
    for(i = 0;i < idx; i++){
        if(p == NULL){
            printf("invaild\n");
            return;
        }
        p = p->next;
    }
    p->prev->next = p->next;
    p->next->prev = p->prev;
    free(p);
}

void delete_by_elem(node* h, datatype data){
    node *p = NULL;
    p = h;
    while(p->next != NULL && p->data != data){
        p=p->next;
    }
    if(p == NULL){
        printf("elem not found\n");
        return;
    }
    printf("elem found %d\n",p->data);
    // delete p
    p->prev->next = p->next;
    if(p->next == NULL){  // if there is no null judge, empty ptr will raise unexpectable error
        free(p);
        return;
    }
    p->next->prev = p->prev;
    free(p);
}
void delete_all(node *h){
    node *p = NULL;
    p = h->next;  // do not delete head node;
    node *sential = NULL;
    while(p->next != NULL){
        sential = p;
        p = p->next;
        free(sential);
    }
}

void is_loop(node *h){
    node* p = h;
    while(p->next != NULL){
        if(p->next == h){
            printf("loop ll detected\n");
            return;
        }
        p = p->next;
    }
    printf("no loop detected\n");
}

void traval(node* h){
    node* p = h->next;
    while(p != NULL){
        printf("current elem at %p is %d\n",p,p->data);
        p = p->next;
    }
}

int main(){
    node* head = NULL;
    head = create();
    head->data = -1;
    tail_insertion(head,0);
    tail_insertion(head,0);

    tail_insertion(head,1);
    tail_insertion(head,2);
    tail_insertion(head,3);
    
    tail_insertion(head,4);

    head_insertion(head,-1);
    head_insertion(head,-2);

    delete_by_idx(head,2);
    traval(head);
    delete_by_elem(head,3);
    delete_by_elem(head,4);
    traval(head);
    delete_all(head);
    free(head);
    //all done
}