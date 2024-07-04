// p49 linear list opearations:
/*
create a linear list
confirm the length of a linear list
confirm wheather a linear list is empty
get / put an element in a linear list by given speicifed posistion
get the position of an element in a linear list
delete an element in a linear list by given speicifed posistion
insert a new element in a linear list by given speicifed posistion
*/

#include <stdio.h>
#define MAX_SIZE 10
typedef struct {
    int data[MAX_SIZE];
    int size;
} LinearList;
LinearList list;
void create(){
    return;
}
int get_length(){
    return MAX_SIZE;
}
void is_empty(LinearList list){
    if(list.size == 0){
        printf("empty\n");
    }else{
        printf("not empty\n");
    }
}
void get_element(int idx){
    printf("%d\n", list.data[idx]);
}
void get_position(int data){
    int i;
    for(i = 0; i < MAX_SIZE; i++){
        if(data == list.data[i]){
            printf("%d\n", i);
            break;
        }
    }
}
void delete_element(int idx){
    int i;
    for(i = idx; i < MAX_SIZE - 1; i++){
        list.data[i] = list.data[i+1];
    }
    list.size--;
}
void insert_element(int data, int idx){
    //0 1 2 3 4
    //0 1 2 x 3 4
    int i;
    for(i = MAX_SIZE; i > idx; i--){
        list.data[i] = list.data[i-1];
    }
    list.data[idx] = data;
    list.size++;
}
void traval(){  //tested
    int i;
    for(i = 0; i < MAX_SIZE; i++){
        printf("%d = %d\n",i,list.data[i]);
    }
}
void head_insertion(int data){  //tested
    int i;
    for(i = MAX_SIZE;i > 0; i--){
        list.data[i] = list.data[i-1];
    }
    list.data[0] = data;
    list.size++;

}
void tail_insertion(int data){  // tested
    if (list.size+1 >= MAX_SIZE){
        printf("error, linear list is full, cannot insert");
        return;
    }
    list.data[list.size] = data;
    list.size++;
}
int main(){
    create();
    get_length();
    list.size = 0;
    
    tail_insertion(0);
    // 0
    tail_insertion(1);
    // 01
    tail_insertion(2);
    // 012
    head_insertion(-1);
    // -1 012
    head_insertion(-2);
    // -2 -1 0 1 2
    insert_element(0,2);
    // -2 -1 0 0 1 2
    insert_element(-1,4);
    // -2 -1 0 -1 0 1 2
    delete_element(5);
    // -2 -1 0 0 1 2
    get_position(2);// 2 is unique
    traval();
    // all done
}