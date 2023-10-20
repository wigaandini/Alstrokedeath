#include "boolean.h"
#include <stdio.h>
#include "prioqueueutime.h"

#define Nil -1
/* Konstanta untuk mendefinisikan address tak terdefinisi */

/* Definisi elemen dan address */
typedef struct {
    int time;  /* [1..100], waktu dengan nilai 1..100 (1 adalah waktu adalah terendah) */
    char info;  /* elemen karakter */
} infotype;
typedef int address;   /* indeks tabel */
/* Contoh deklarasi variabel bertype PrioQueueTime : */
/* Versi I : tabel dinamik, Head dan Tail eksplisit, ukuran disimpan */
typedef struct {
    infotype * T;   /* tabel penyimpan elemen */
    address HEAD;  /* alamat penghapusan */
    address TAIL;  /* alamat penambahan */
    int MaxEl;     /* Max elemen queue */
} PrioQueueTime;
/* Definisi PrioQueueTime kosong: HEAD=Nil; TAIL=Nil. */
/* Catatan implementasi: T[0] tidak pernah dipakai */

/* ********* AKSES (Selektor) ********* */
/* Jika e adalah infotype dan Q adalah PrioQueueTime, maka akses elemen : */
#define Time(e)     (e).time
#define Info(e)     (e).info
#define Head(Q)     (Q).HEAD
#define Tail(Q)     (Q).TAIL
#define InfoHead(Q) (Q).T[(Q).HEAD]
#define InfoTail(Q) (Q).T[(Q).TAIL]
#define MaxEl(Q)    (Q).MaxEl
#define Elmt(Q,i)   (Q).T[(i)]

/* ********* Prototype ********* */
boolean IsEmpty (PrioQueueTime Q){
    return (Head(Q) == Nil && Tail(Q) == Nil);
}
/* Mengirim true jika Q kosong: lihat definisi di atas */
boolean IsFull (PrioQueueTime Q){
    return (MaxEl(Q) = NBElmt(Q));
}
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxEl */
int NBElmt (PrioQueueTime Q){
    if(isEmpty(Q)){
        return 0;
    }
    else if(Tail(Q) >= Head(Q)){
        return (Tail(Q) - Head(Q) + 1);
    }
    else{
        return (MaxEl(Q) - Head(Q) + Tail(Q) + 1);
    }
}
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */

/* *** Kreator *** */
void MakeEmpty (PrioQueueTime * Q, int Max){
    (*Q).T = (infotype*) malloc((Max+1)* sizeof(infotype));
    if((*Q).T != NULL){
        Head(*Q) = Nil;
        Tail(*Q) = Nil;
        MaxEl(*Q) = Max+1;
    }
    else{
        MaxEl(*Q) = 0;
    }
}
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxEl=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */

/* *** Destruktor *** */
void DeAlokasi(PrioQueueTime * Q){
    Head(*Q) = Nil;
    Tail(*Q) = Nil;
    MaxEl(*Q) = 0;
    free((*Q).T);    
}
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxEl(Q) diset 0 */

/* *** Primitif Add/Delete *** */
void Enqueue (PrioQueueTime * Q, infotype X){
    int i, j;
    int idx;
    infotype temp;

    if(isEmpty(*Q)){
        Head(*Q) = 0;
        Tail(*Q) = 0;
        InfoTail(*Q) = X;
    }
    else{
        if(Tail(*Q) == MaxEl-1){
            Tail(*Q) = 0;
        }
        else{
            Tail(*Q) ++;
        }
        InfoTail(*Q) = X;
        i = Tail(*Q);
        if (i == 0){
            j = MaxEl(*Q)-1;
        }
        else{
            j = i-1;
        }
        while(i != Head(*Q) && (Time((Elmt(*Q,i))) < Time(Elmt(*Q,j))){
            temp = Elmt(*Q,i);
            Elmt(*Q,i) = Elmt(*Q,j);
            Elmt(*Q,j) = temp;
            i = j;
            if (i == 0){
                j = MaxEl(*Q)-1;
            }
            else{
                i--;
            }
        }
    }
}
/* Proses: Menambahkan X pada Q dengan aturan priority queue, terurut membesar berdasarkan time */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X disisipkan pada posisi yang tepat sesuai dengan prioritas,
        TAIL "maju" dengan mekanisme circular buffer; */
void Dequeue (PrioQueueTime * Q, infotype * X){
    *val = InfoHead(*q);
    if (NBElmt(*Q) == 1){
        Head(*Q) = Nil;
        Tail(*Q) = Nil;
    }
    else {
        if (Head(*Q) = MaxEl(*Q) - 1){
            Head(*Q) = 0;
        }
        else {
            Head(*Q)++;
        }
    }
}
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer;
        Q mungkin kosong */

/* Operasi Tambahan */
void PrintPrioQueueTime (PrioQueueTime Q){
    infotype val;
    PrioQueueTime new;
    new = Q;
    if(!isEmpty(Q)){
        while(!isEmpty(new)){
            Dequeue(&new, &val);
            printf("<%d> <%c>\n", Time(val), Info(val));
        }
    }
    printf("#\n");
}
/* Mencetak isi queue Q ke layar */
/* I.S. Q terdefinisi, mungkin kosong */
/* F.S. Q tercetak ke layar dengan format:
<time-1> <elemen-1>
...
<time-n> <elemen-n>
#
*/


// Nadil
#include "boolean.h"
#include "prioqueuetime.h"
#include <stdlib.h>
#include <stdio.h>

/* ********* AKSES (Selektor) ********* */
/* Jika e adalah infotype dan Q adalah PrioQueueTime, maka akses elemen : */
/*
#define Time(e)     (e).time
#define Info(e)     (e).info
#define Head(Q)     (Q).HEAD
#define Tail(Q)     (Q).TAIL
#define InfoHead(Q) (Q).T[(Q).HEAD]
#define InfoTail(Q) (Q).T[(Q).TAIL]
#define MaxEl(Q)    (Q).MaxEl
#define Elmt(Q,i)   (Q).T[(i)]
*/

/* ********* Prototype ********* */
boolean IsEmpty(PrioQueueTime Q)
/* Mengirim true jika Q kosong: lihat definisi di atas */
{
    return (Head(Q) == Nil) && (Tail(Q) == Nil);
}
boolean IsFull(PrioQueueTime Q)
    /* Mengirim true jika tabel penampung elemen Q sudah penuh */
    /* yaitu mengandung elemen sebanyak MaxEl */
{
    return MaxEl(Q) == NBElmt(Q);
}
int NBElmt(PrioQueueTime Q)
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */
{    
    if (IsEmpty(Q)){
        return 0;
    }
    else {
        if ((Tail(Q) - Head(Q)) >= 0){
            return Tail(Q) - Head(Q) + 1;
        }
        else {
            return MaxEl(Q) - (Head(Q) - (Tail(Q) + 1));
        }
    }
}

/* *** Kreator *** */
void MakeEmpty(PrioQueueTime *Q, int Max)
    /* I.S. sembarang */
    /* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
    /* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
    /* atau : jika alokasi gagal, Q kosong dg MaxEl=0 */
    /* Proses : Melakukan alokasi, membuat sebuah Q kosong */
{
    (*Q).T = (infotype *)malloc((Max) * sizeof(infotype));
    if ((*Q).T == NULL) {
        MaxEl(*Q) = 0;
    }
    else {
        Head(*Q) = Nil;
        Tail(*Q) = Nil;
        MaxEl(*Q) = Max;
    }
}

/* *** Destruktor *** */
void DeAlokasi(PrioQueueTime *Q)
    /* Proses: Mengembalikan memori Q */
    /* I.S. Q pernah dialokasi */
    /* F.S. Q menjadi tidak terdefinisi lagi, MaxEl(Q) diset 0 */
{
    Head(*Q) = Nil;
    Tail(*Q) = Nil;
    MaxEl(*Q) = 0;
    free((*Q).T);
}

/* *** Primitif Add/Delete *** */
void Enqueue(PrioQueueTime *Q, infotype X)
    /* Proses: Menambahkan X pada Q dengan aturan priority queue, terurut mengecil berdasarkan time */
    /* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
    /* F.S. X disisipkan pada posisi yang tepat sesuai dengan prioritas,
            TAIL "maju" dengan mekanisme circular buffer; */
{
    boolean found;
    int idx;
    int i, j;
    infotype temp;

    // ALGORITMA
    if (IsEmpty(*Q)) {
        Head(*Q) = 0;
        Tail(*Q) = 0;
        InfoTail(*Q) = X;
    }
    else {
        Tail(*Q) = Tail(*Q) == MaxEl(*Q) - 1 ? 0 : Tail(*Q) + 1;
        InfoTail(*Q) = X;
        i = Tail(*Q);
        j = i == 0 ? MaxEl(*Q) - 1 : i - 1;
        while (i != Head(*Q) && Time(Elmt(*Q, i)) < (Time(Elmt(*Q, j)))) {
            temp = Elmt(*Q, i);
            Elmt(*Q, i) = Elmt(*Q, j);
            Elmt(*Q, j) = temp;
            i = j;
            j = i == 0 ? MaxEl(*Q) - 1 : i - 1;
        }
    }
}
void Dequeue(PrioQueueTime *Q, infotype *X)
    /* Proses: Menghapus X pada Q dengan aturan FIFO */
    /* I.S. Q tidak mungkin kosong */
    /* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer;
            Q mungkin kosong */
{
    if (NBElmt(*Q) == 1) {
        *X = InfoHead(*Q);
        Head(*Q) = Nil;
        Tail(*Q) = Nil;
    }
    else {
        *X = InfoHead(*Q);
        Head(*Q) = (Head(*Q) == MaxEl(*Q) - 1) ? 0 : Head(*Q) + 1;
    }
}

/* Operasi Tambahan */
void PrintPrioQueueTime(PrioQueueTime Q)
    /* Mencetak isi queue Q ke layar */
    /* I.S. Q terdefinisi, mungkin kosong */
    /* F.S. Q tercetak ke layar dengan format:
    <time-1> <elemen-1>
    ...
    <time-n> <elemen-n>
    #
    */
{
    infotype val;
    PrioQueueTime temp;
    temp = Q;
    if (!IsEmpty(Q)) {
        while (!IsEmpty(temp)) {
            Dequeue(&temp, &val);
            printf("%d %c\n", Time(val), Info(val));
        }
    }
    printf("#\n");
}