#include <stdio.h>
#include "queue.h"

float avgElmt(Queue q){
    float sum = 0;
    int i;
    for (i = IDX_HEAD(q); i <= IDX_TAIL(q); i = (i+1)%CAPACITY){
        sum += q.buffer[i];
    }
    return (sum/length(q));
}

int main(){
    Queue q;
    int pilih;
    ElType val;
    
    CreateQueue(&q);
    do{
        scanf("%d", &pilih);
        if (pilih == 1){
            scanf("%d", &val);
            if(!isFull(q)){
                enqueue(&q, val);
            }
            else{
                printf("Qeue penuh\n");
            }
        }
        else if(pilih == 2){
            if(!isEmpty(q)){
                dequeue(&q, &val);
            }
            else{
                printf("Queue kosong\n");
            }
        }
    } while (pilih != 0);

    printf("%d\n", length(q));
    if(pilih == 0){
        if(!isEmpty(q)){
            printf("%.2f\n", avgElmt(q));
        }
        else{
            printf("Tidak bisa dihitung\n");
        }
    }
}