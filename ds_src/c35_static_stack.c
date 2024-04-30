/*
p59 static stack
operations of stack
1. push
2. pop
3. peek
4. clear
5. isempty
*/

#include <stdio.h>
#define MAX_SIZE 10
typedef int datatype;
struct stack{
    datatype data[MAX_SIZE];
    int top;
};
static struct stack stack;
datatype pop(){
    if (stack.top == 0){
        printf("cannot pop due to empty");
        return -1;
    }
    datatype elem =  stack.data[stack.top];
    stack.top --;
    return elem;
}
void push(datatype data){
    if(stack.top == MAX_SIZE){
        printf("cannot push due the stack is full\n");
        return;
    }
    stack.data[stack.top + 1] = data;
    stack.top++;
}
datatype peek(){
    return stack.data[stack.top];
}
void clear(){
    stack.top = 0;
}
int isempty(){
    if(stack.top == 0){
        return 1;
    }else{
        return 0;
    }
}

int main(){
    push(1);
    push(2);
    printf("top is %d\n",peek());
    printf("pop elem is %d\n",pop());
    printf("top is %d\n",peek());
}