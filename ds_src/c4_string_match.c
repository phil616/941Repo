/*
p87 string's match algorithm
*/


#include <stdio.h>

int len(char src[]){
    int i = 0;
    while(src[i] != '\0')
        i++;
    return i;
}

int plain_match(char src[], char pattern[]){
    // src = "hello world"
    // pattern = "llo"
    /*
    pseudo:
    while src's each char
        match pattern
        match src
            if all match
                return idx
            else
                idx++
    */
    int idx = 0;
    int success = -1;
    int reg = 0;
    for(idx = 0;idx < len(src) - len(pattern);idx++){
        reg = 0;
        while(src[reg + idx] == pattern[reg]){
            if(reg == len(pattern) - 1)
                return idx + 1;
            reg++;
        }
    }
    return success;
}


int main(){
    char string[255];
    scanf("%s",string);
    char pattern[5] = "cccc";
    int idx = plain_match(string,pattern);
    printf("%d",idx);
}