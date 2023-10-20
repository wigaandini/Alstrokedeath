#include <stdio.h>
#include "matrix.h"

int main(){
   Matrix m;
   readMatrix(&m, 3, 3);

   // print matrix
   displayMatrix(m);

   // count val on row
   int n = CountNumRow(m, 0, 1);
   printf("%d\n",n);
}