#include <stdio.h>
#include <stdlib.h>
#include "charmachine.h"
#include "wordmachine.h"

int main(){
    int max = 0;
    int temp;
    STARTWORD();
    while(!EndWord){
        temp = currentWord.Length;
        if(temp >= max){
            max = temp;
        }
        ADVWORD();
    }
    printf("%d\n", max);
    return 0;
}
