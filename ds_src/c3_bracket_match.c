// a simple bracket matching program to verify if the bracket are balanced or not

#include<stdio.h>
#define MAX 100
#define EOS '#'
#define ERR "UNMATCH ERROR\n"
typedef struct{
    char stack[MAX];
    int top;
}S;
void init(S *s){
    s->top = -1;
}

void pop(S *s){
    printf("pop called\n");
    s->top--;
}
void push(S *s, char c){
    printf("push called\n");
    s->top++;
    s->stack[s->top] = c;
}
char peek(S *s){
    if (s->top == -1){
        return EOS;
    }
    char r = s->stack[s->top];
    printf("elem %c peek\n",r);
    return r;
}
int isEmpty(S *s){
    printf("t = %d\n",s->top);
    if(s->top == -1) return 1;
    else return 0;
}
int all(){
    int res = 0;
    S small_bra;
    S middle_bra;
    S big_bra;

    init(&small_bra);
    init(&middle_bra);
    init(&big_bra);
    char str[100];
    printf("Enter a string with bracket: ");
    scanf("%s", str);
    int i = 0;
    for(i = 0; str[i] != '\0';i++ ){
        switch (str[i]){
            case '(':
                push(&small_bra,'('); break;
            case ')':
                if(peek(&small_bra) == '('){
                    pop(&small_bra);
                }else if(peek(&small_bra) == EOS){
                    printf("No match found at %d -",i);
                    res++;
                    printf(ERR);
                }else{
                    printf(ERR);
                }
            break;
            case '[':
                push(&middle_bra,'[');
                break;
            case ']':
                if(peek(&middle_bra) == '['){
                    pop(&middle_bra);
                }else if(peek(&middle_bra) == EOS){
                    printf("No match found at %d -",i);
                    res++;
                    printf(ERR);
                }else{
                    printf(ERR);
                }
            break;
            case '{':
                push(&big_bra,'{');
                break;
            case '}':
                if(peek(&big_bra) == '{'){
                    pop(&big_bra);
                }else if(peek(&big_bra) == EOS){
                    printf("No match found at %d -",i);
                    res++;
                    printf(ERR);
                }else{
                    printf(ERR);
                }
            break;
            default:
            break;
        }
    }
    if(isEmpty(&small_bra) && isEmpty(&middle_bra) && isEmpty(&big_bra) && res == 0){
        printf("Bracket are balanced");
    }else{
        printf("not closed");
    }
}
int main(){
    all();
}