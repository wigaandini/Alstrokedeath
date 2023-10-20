// Ambillah ADT Matriks yang sudah Anda buat pada tugas pra-praktikum sebelumnya dan

// tambahkan beberapa primitif berkaitan dengan operasi berbasis baris dan kolom

// matriks sebagai berikut:


/* Operasi berbasis baris dan per kolom */
#include <stdio.h>
#include "matrix.c"

float AvgRow(Matrix m, IdxType i){
   IdxType j;
   ElType sum=0;
   for(j=0; j<COL_EFF(m); j++){
      sum += ELMT(m, i, j);
   }
   return (sum/COL_EFF(m));
}
/* Menghasilkan rata-rata dari elemen pada baris ke-i */

/* Prekondisi: i adalah indeks baris efektif dari M */


float AvgCol(Matrix m, IdxType j){
   IdxType i;
   ElType sum=0;
   for(i=0; i<COL_EFF(m); i++){
      sum += ELMT(m, i, j);
   }
   return (sum/ROW_EFF(m));
}
/* Menghasilkan rata-rata dari elemen pada kolom ke-j */

/* Prekondisi: j adalah indeks kolom efektif dari M */


void MinMaxRow(Matrix m, IdxType i, ElType * max, ElType * min){
   IdxType j;

   *min = ELMT(m, i, 0);
   *max = *min;

   for(j = 0; j < COL_EFF(m); j++){
      if(ELMT(m, i, j) < *min){
         *min = ELMT(m, i, j);
      }
      if(ELMT(m, i, j) > *max){
         *max = ELMT(m, i, j);
      }
   }
}
/* I.S. i adalah indeks baris efektif dari M, M terdefinisi */

/* F.S. max berisi elemen maksimum pada baris i dari M

min berisi elemen minimum pada baris i dari M */


void MinMaxCol(Matrix m, IdxType j, ElType * max, ElType * min){
   IdxType i;

   *min = ELMT(m, 0, j);
   *max = *min;

   for(i = 0; i < COL_EFF(m); i++){
      if(ELMT(m, i, j) < *min){
         *min = ELMT(m, i, j);
      }
      if(ELMT(m, i, j) > *max){
         *max = ELMT(m, i, j);
      }
   }
}
/* I.S. j adalah indeks kolom efektif dari M, M terdefinisi */

/* F.S. max berisi elemen maksimum pada kolom j dari M

min berisi elemen minimum pada kolom j dari M */


int CountNumRow(Matrix m, IdxType i, ElType X){
   IdxType j;
   int count=0;
   for(j=0; j<COL_EFF(m); j++){
      if (ELMT(m, i, j) == X){
         count ++;
      }
   } 
   return count; 
}
/* Menghasilkan banyaknya kemunculan X pada baris i dari M */


int CountNumCol(Matrix m, IdxType j, ElType X){
   IdxType i;
   int count=0;
   for(i=0; i<ROW_EFF(m); i++){
      if (ELMT(m, i, j) == X){
         count ++;
      }
   }
   return count;
}
/* Menghasilkan banyaknya kemunculan X pada kolom j dari M */


void RotateMat(Matrix *m){
    int row = 0, col = 0;
    int previous, current;
    int a = ROW_EFF(*m);
    int b = COL_EFF(*m);
    int i;
    while (row < a && col < b) {
        if (row + 1 == a || col + 1 == b) {
            break;
        }
        previous = ELMT(*m,row + 1,col);
        for (i = col; i < b; i++) {
            current = ELMT(*m,row,i);
            ELMT(*m,row,i) = previous;
            previous = current;
        }
        row++;
        for (i = row; i < a; i++) {
            current = ELMT(*m,i,b-1);
            ELMT(*m,i,b-1) = previous;
            previous = current;
        }
        b--;
        if (row < a) {
            for (i = b-1; i >= col; i--) {
                current = ELMT(*m,a-1,i);
                ELMT(*m,a-1,i) = previous;
                previous = current;
            }
        }
        a--;
        if (col < b) {
            for (i = a-1; i >= row; i--) {
                current = ELMT(*m,i,col);
                ELMT(*m,i,col) = previous;
                previous = current;
            }
        }
        col++;
    }
}

/* I.S. m terdefinisi dan IsSquare(m) */

/* F.S. m "di-rotasi" searah jarum jam

   untuk semua "lapisan" elemen mulai dari yang terluar

   Contoh matrix 3x3 sebelum dirotasi:

   1 2 3

   4 5 6

   7 8 9


   Contoh matrix 3x3 setelah dirotasi:

   4 1 2

   7 5 3

   8 9 6

   Contoh matrix 4x4 sebelum dirotasi:

   1 2 3 4

   5 6 7 8

   9 10 11 12

   13 14 15 16

   Contoh matrix 4x4 setelah dirotasi:

   5 1 2 3

   9 10 6 4

   13 11 7 8

   14 15 16 12

*/


// Kumpulkan file matrix.c.

int main(){
    Matrix m;
    ElType max, min;
    readMatrix(&m, 3, 3);

    // print matrix
    displayMatrix(m);

    // count val on row
    int n = CountNumRow(m, 0, 1);
    printf("%d\n",n);
    MinMaxRow(m, 0, &max, &min);
    printf("%d\n", max);
    printf("%d\n", min);

    RotateMat(&m);
    displayMatrix(m);
} 