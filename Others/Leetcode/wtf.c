#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

bool containsDuplicate(int* nums, int numsSize) {
   int *key = (int *)malloc(sizeof(int) * numsSize);
   int *value = (int *)malloc(sizeof(int) * numsSize);

   for (int i = 0; i < numsSize; i++)
   {
      nums[i] = key[i];
      if (value[key[i]] != 1)
      {
         value[key[i]]++;
      } else {
         return true;
      }      

   }
   


}
