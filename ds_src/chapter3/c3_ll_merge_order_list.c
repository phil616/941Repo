/**
 * given two linked list which are ordered,
 * 1 > 2 > 4 > 5 > 6
 * 1 > 2 > 3 > 5 > 7 > 8
 * - different length
 * - different step
 * - expected merge to one list and remain corrent order
*/
//...

#include <stdio.h>
#include <malloc.h>

struct LinkedNode
{
    struct LinkedNode *next;
    int data;
};
typedef struct LinkedNode node;

node *init(int map[],int l){
    node *head = NULL;
    head = (node*)malloc(sizeof(node));
    head->data = map[0];
    node *p = head;
    int i;
    for(i = 1; i < l; i++){
        p->next = (node*)malloc(sizeof(node));
        p->next->data = map[i];
        p = p->next;
        p->next = NULL;
    }
    return head;
}

node* solve(node* d,node *s){
    // ...
}

int main(){
    int one[5] = {1,2,3,8,9};
    int two[3] = {2,4,8};
    node * h1 = init(one,5);
    node * h2 = init(two,3);
    node * r = solve(h1,h2);
    while(r != NULL){
        printf("%d\n",r->data);
        r = r->next;
    }

}