#include <stdio.h>
#define MAX 10
/*
ADT:
1. enqueu
2. outqueue
3. peek
4. is full
5. is empty
*/
typedef struct{
    int queue[MAX];
    int rear;
    int front;
}Q;

void init(Q *q){
    q->front = 0;
    q->rear = 0;
}
int isFull(Q *q){

}

void enqueue(Q *q, int elem){
    
}