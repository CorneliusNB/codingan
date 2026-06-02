#include<stdio.h>
#include<stdlib.h>

struct MaxHeap {
  int data[50];
  int size;
};

void swap(int *a, int *b){
  int temp = *a;
  *a = *b;
  *b = temp;
}

void insert(MaxHeap *heap, int val){
  if(heap->size >= 50){
    return;
  }
  int currentidx = heap->size;
  heap->data[currentidx] = val;
  heap->size++;

  while(currentidx > 0){
    int parentidx = (currentidx - 1) /2 ;
    if(heap->data[currentidx] > heap->data[parentidx]){
      swap(&heap->data[currentidx], &heap->data[parentidx]);
    }
  }



  
}

