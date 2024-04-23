/*
p61 linked stack
a stack datastructure for linked list

top of stack is head node

 NOT FINISHED YET
*/

#include <stdio.h>
#include <malloc.h>

typedef int datatype;
struct linked_stack_node
{
    struct linked_stack_node* next;
    datatype data;
};
typedef struct linked_stack_node node;

node* create(){
    node* new = (node*)malloc(sizeof(node));
    new->next = NULL;
    return new;
}
node* pop(node* s){
    node* p = NULL;
    if (s->next != NULL){
        p = s->next;
        free(s);
    }
    return p;
}
node* push(datatype data,node *s){
    node* new = create();
    new->data = data;
    new->next = s;
    return new;
}
datatype peek(node *s){
    return s->data;
}
void clear(node *s){
    node *p = NULL;
    p = s;
    node* sentinel = s;
    while(p != NULL){
        sentinel = p;
        p = p->next;
        free(sentinel);
    }
}
int isEmpty(node *s){
    if (s->next != NULL){
        return 0;
    }else{
        return 1;
    }
}

int main(){
    node * stack = NULL;
    stack = push(1,stack);
    stack = push(2,stack);
    printf("top = %d\n",peek(stack));

    // all done
}

