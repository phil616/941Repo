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

node* create();
void pop(node* s);
void push(datatype data,node *s);
datatype peek(node *s);
void clear(node *s);
int isEmpty(node *s);

int main(){

}

