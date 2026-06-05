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
    } else {
      return;
    }
  }

int extractMax(MaxHeap *heap){
  int maxVal = heap->data[0];
  heap->data[0] = heap->data[maxSize-1];
  heap->size--;

  int curridx = 0;
  while(2*curridx+1 < heap->size){
    int leftidx = 2*curridx+1;
    int rightidx = 2*curridx+2;
    int largestidx = leftidx;
    if(rightidx < heap->size && heap->data[rightidx] > heap->data[eftidx]){
      largestidx = rightidx;
    }
    if(heap->data[curridx] >= heap->data[largestidx]){
      break;
    }

    swap(&heap->data[curridx], &heap->data[largestidx]);
    curridx = largestidx;
  }
  return maxVal  
}




  
}

