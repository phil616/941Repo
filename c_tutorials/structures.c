#include <stdio.h>

// the way define a struct

typedef struct AS{
    int a;
    int b;
}A;

typedef int Interger;

int addrParam(int *a){
    // the params execepts the address of the variable
    printf("*a is %d\n", *a);
}

// array params
void arrayParam(int a[]){
    printf("a[0] is %d\n", a[0]);
}

int main(){
    Interger b = 20;
    Interger a = 10;
    printf("a is %d\n", a);
    addrParam(&a);
    struct AS s;
    A as;
    as.a = 100;
    printf("as.a is %d\n", as.a);
    s.a = 10;
    printf("s.a is %d\n", s.a);
    int arr[10];
    arr[0] = 1;

    arrayParam(arr);
}