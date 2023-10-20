#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"
#include "listdin.h"

int main(){
    ListDin l1, l2, l3;
    IdxType i, j;
    boolean eq = false;
    
    CreateListDin(&l1, 200);
    readList(&l1);
    CreateListDin(&l2, 200);
    readList(&l2);
    CreateListDin(&l3, 200);

    copyList(l2, &l3);

    for(i=0; i<listLength(l1); i++){
        eq = false;
        j = 0;
        while(!eq && j<listLength(l3)){
            if(ELMT(l1,i) == ELMT(l3,j)){
                eq = true;
            }
            j++;
        }
        if(!eq){
            insertLast(&l3,ELMT(l1,i));
        }
    }

    expandList(&l3, 200);
    sort(&l3, true);
    printf("%d\n", listLength(l3));
    printList(l3);
    printf("\n");
    return 0;
}