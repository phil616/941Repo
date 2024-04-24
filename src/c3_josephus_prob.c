//Josephus permutation
/**
 * 
 *  北理工题目：
    N 个人围成一圈顺序编号，从 1 号开始按 1、2、3 顺序报数，报 3 者退出圈外，
    其余的人再从 1、2、3  开始报数，报 3 的人再退出圈外，依次类推。
    请按退出顺序输出每个退出人的原序号。
    要求使用环行链表编程。
 * 
 *  一般形式
 * N个人围成一圈，从第一个开始报数，第M个将被杀掉，
 * 最后剩下一个，其余人都将被杀掉。
 * 例如N=6，M=5，被杀掉的顺序是：5，4，6，2，3。
 * n = LEN
 * m = k (params int k)
 * compile option -D LEN=8
*/ 

#include <stdio.h>
#include <malloc.h>
#ifndef LEN
#define LEN 6
#endif
#ifndef M
#define M 3
#endif
//...

typedef struct Node {
    struct Node* next;
    int data;
} node;

node *init(){
    // return head -> node -> node... node(n)->next == head
    node *hmap[LEN] = {NULL};
    for(int i = 0;i < LEN; i++){

        hmap[i] = (node*)malloc(sizeof(node));
        hmap[i]->data = i + 1;
        hmap[i]->next = NULL;
        i?i,hmap[i-1]->next = hmap[i]:0;
        printf("%d\n",hmap[i]->data);
    }
    hmap[LEN-1]->next = hmap[0];
    return hmap[0];
}

void solve(node* head,int k){
    int length = LEN - 1;
    node *p = head;
    node *sentinel = NULL;
    int idx = 1;
    while(length > 1){
        if (idx == k){
            idx = 1;
            sentinel->next = p->next;
            printf("%d has been killed\n",p->data);
            length --;
            free(p);
            p = sentinel->next;
        }
        idx++;
        sentinel = p;
        p=p->next;
    }
    printf("last survive = %d\n",sentinel->data);
}
int main(){
    node *h = init();
    solve(h,3);
    // all done
}