// calc array's location
/*
    p77 calc array's location
 */

#include <stdio.h>
#define MAX 10

int location(int array[], int ele){
    int *p = &array[0];
    int i;
    for (i = 0;i < MAX; i++){
        if (array[i] == ele){
            return (int)p + i*sizeof(int);
        }
    }
}

int main(void){

    int a[MAX] = {1,2,3,4,5};
    int s,e;
    s = (int)a;
    e = location(a, 3);
    printf("location of a is %d\n", a);
    printf("location of 3 is %d\n", e);
    printf("distance between a and 3 is %d\n", e - s);
}
