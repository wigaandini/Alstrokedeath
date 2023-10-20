/* File : prioqueue.h */
/* Representasi priority queue dengan array eksplisit dan alokasi stastik */
/* Queue terurut mengecil berdasarkan elemen score (nilai Daspro) */
/* Jika score sama, diurutkan membesar berdasarkan tKedatangan (waktu kedatangan) */

#include "boolean.h"
#include <stdlib.h>
#include <stdio.h>
#include "prioqueue20.h"

/* *** Kreator *** */
void CreatePrioQueue(PrioQueue *pq){
    IDX_HEAD(*pq) = IDX_UNDEF;
    IDX_TAIL(*pq) = IDX_UNDEF;
}
/* I.S. sembarang */
/* F.S. Sebuah pq kosong terbentuk dengan kondisi sbb: */
/* - Index head bernilai IDX_UNDEF */
/* - Index tail bernilai IDX_UNDEF */
/* Proses : Melakukan alokasi, membuat sebuah pq kosong */

boolean isEmpty(PrioQueue pq){
    return (IDX_HEAD(pq) == IDX_UNDEF && IDX_TAIL(pq) == IDX_UNDEF);
}
/* Mengirim true jika pq kosong: lihat definisi di atas */

boolean isFull(PrioQueue pq){
    return (IDX_HEAD(pq) == 0 && IDX_TAIL(pq) == CAPACITY - 1);
}
/* Mengirim true jika tabel penampung elemen pq sudah penuh */
/* yaitu jika index head bernilai 0 dan index tail bernilai CAPACITY-1 */

int length(PrioQueue pq){
    if (isEmpty(pq)){
        return 0;
    }
    else {
        return IDX_TAIL(pq) - IDX_HEAD(pq) + 1;
    }
}
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika pq kosong. */

/*** Primitif Add/Delete ***/
void enqueue(PrioQueue *pq, ElType val){
    // // ElType temp;
    // // if(isEmpty(*pq)){
    // //     IDX_HEAD(*pq) = 0;
    // //     IDX_TAIL(*pq) = 0;
    // //     TAIL(*pq) = val;
    // // }
    // // else{
    // //     if (IDX_HEAD(*pq) != 0 && IDX_TAIL(*pq) == CAPACITY - 1){
    // //         int idxH = IDX_HEAD(*pq), idxT = IDX_TAIL(*pq);
    // //         IDX_HEAD(*pq) --;
    // //         IDX_TAIL(*pq) --;
    // //         for(while idxH != 0){
    // //             temp = *pq.buffer[idxH];
    // //             *pq.buffer[idxH-1] = temp; 
    // //             idxH ++;
    // //         }
    // //         int j = IDX_TAIL(*pq);
    // //         IDX_HEAD(*pq) = 0;
    // //         IDX_TAIL(*pq) ++;
    // //         while(val.score > *pq.buffer[j].score){
    // //             temp = *pq.buffer[j];
    // //             *pq.buffer[j+1] = temp;
    // //             *pq.buffer[j] = val;
    // //             j --;
    // //         }
    // //     }
    // //     else {
    // //         IDX_TAIL(*pq) ++;
    // //         TAIL(*pq) = val;
    // //     }
    // }
    /* KAMUS */
    int i;
    ElType temp;

    /* ALGORITMA */
    if (isEmpty(*pq)) {
        IDX_HEAD(*pq) = 0;
        IDX_TAIL(*pq) = 0;
    } else {
        if (IDX_TAIL(*pq) == CAPACITY - 1) {
            for (i = IDX_HEAD(*pq); i <= IDX_TAIL(*pq); i++) {
                pq->buffer[i - IDX_HEAD(*pq)] = pq->buffer[i];
            }
            IDX_TAIL(*pq) -= IDX_HEAD(*pq);
            IDX_HEAD(*pq) = 0;
        }
        IDX_TAIL(*pq)++;
    }
    TAIL(*pq) = val;

    i = IDX_TAIL(*pq);

    while ((i > 0) && (pq->buffer[i - 1].score < pq->buffer[i].score) || ((pq->buffer[i - 1].score == pq->buffer[i].score) && (pq->buffer[i - 1].tArrival > pq->buffer[i].tArrival))) {
        temp = pq->buffer[i - 1];
        pq->buffer[i - 1] = pq->buffer[i];
        pq->buffer[i] = temp;
        i--;
    }
}
/* Proses: Menambahkan val pada pq dengan aturan FIFO */
/* I.S. pq mungkin kosong, tabel penampung elemen pq TIDAK penuh */
/* F.S. val menjadi TAIL yang baru, IDX_TAIL "mundur".
        Jika q penuh semu, maka perlu dilakukan aksi penggeseran "maju" elemen-elemen pq
        menjadi rata kiri untuk membuat ruang kosong bagi TAIL baru  */

void dequeue(PrioQueue * pq, ElType *val){
    *val = HEAD(*pq);
    if (length(*pq) == 1){
        IDX_HEAD(*pq) = IDX_UNDEF;
        IDX_TAIL(*pq) = IDX_UNDEF;
    }
    else {
        IDX_HEAD(*pq)++;
    }
}
/* Proses: Menghapus val pada q dengan aturan FIFO */
/* I.S. pq tidak mungkin kosong */
/* F.S. val = nilai elemen HEAD pd
I.S., HEAD dan IDX_HEAD "mundur"; 
        pq mungkin kosong */