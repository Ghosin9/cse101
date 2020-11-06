/*
* ListTest.c
* Ly Phung
* lynphung
* CSE101
* 10/20/19
* Tester file for List.c
*/
#include<stdio.h>
#include<stdlib.h>
#include"List.h"

int main(int argc, char* argv[]){
   
   List A = newList();
   List B = newList();
   List C = newList();
   int X[] = {20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0};
   int i, u=-10, v=-20, equal=0;

   for(i=1; i<=20; i++){
      append(A, &X[i]);
      prepend(B, &X[i]);
   }

   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", *(int*)get(A));
   }
   printf("\n");
   for(moveFront(B); index(B)>=0; moveNext(B)){
      printf("%d ", *(int*)get(B));
   }
   printf("\n");

   moveFront(A);
   while( index(A)>=0 ){
      append(C, get(A));
      moveNext(A);
   }

   for(moveFront(C); index(C)>=0; moveNext(C)){
      printf("%d ", *(int*)get(C));
   }
   printf("\n");

   moveFront(A);
   for(i=0; i<5; i++) moveNext(A); 
   insertBefore(A, &u);            
   for(i=0; i<9; i++) moveNext(A); 
   insertAfter(A, &v);             
   for(i=0; i<5; i++) movePrev(A); 
   delete(A);                      

   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", *(int*)get(A));
   }
   printf("\n");
   for(moveBack(A); index(A)>=0; movePrev(A)){
      printf("%d ", *(int*)get(A));
   }
   printf("\n");

   printf("%d\n", length(A));
   clear(A);
   printf("%d\n", length(A));

   freeList(&A);
   freeList(&B);
   freeList(&C);

   return(0);
}