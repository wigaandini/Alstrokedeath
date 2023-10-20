#include <stdio.h>
#include <stdlib.h>
#include "charmachine.h"
#include "wordmachine.h"

int main(){
    // STARTWORD();
    // int i = 0;
    // while(!EndWord){
    //     LowerCase();
    //     for(i = 0; i < currentWord.Length; i++){
    //         printf("%c", currentWord.TabWord[i]);
    //     }
    //     printf(" ");
    //     ADVWORD();
    // }
    // printf("\n");
    // return 0;

    STARTWORD();
    int i = 0;
    while(!EndWord){
        LowerCase();
        for(i = 0; i < currentWord.Length; i++){
            printf("%c", currentWord.TabWord[i]);
        }
        if(currentChar == MARK){
            break;
        }
        else{
            printf(" ");
        }
        ADVWORD();
    }
    printf(".\n");
    return 0;
}