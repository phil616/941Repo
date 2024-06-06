// a simple circle queue with array impl
/**
 * 1. enqueue
 * 2. outqueue
 * 3. peek
 * 4. is empty
 * 5. is full
*/

#include <stdio.h>
#define MAX 10
typedef struct{
    int queue[MAX];
    int front;
    int rear;
}Queue;

Queue q;

