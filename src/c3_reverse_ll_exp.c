/**
 * https://www.acwing.com/problem/content/description/33/
 * 
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
*/
#include <stdio.h>
#include <malloc.h>

struct ListNode
{
    int val;
    struct ListNode *next;
};

void print(struct ListNode* head){
    struct ListNode* p = NULL;
    p = head;
    while(p != NULL){
        printf("%d ",p->val);
        p = p->next;
    }
}
struct ListNode* create(int val){
    struct ListNode *newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (newNode == NULL){
        printf("alloc failed\n");
        exit(-1);
    }
    newNode->val = val;
    newNode->next = NULL;
    return newNode;
}

struct ListNode* reverseList(struct ListNode* head){
    // type here
}

int main(){
    //..
}