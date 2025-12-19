#include<stdio.h>
int differenceOfSums(int n, int m) {
    int arr[1001] = {0};
    int num1 = 0;
    int num2 = 0;
    for(int i = 0; i < n; i++){
        arr[i] = i + 1;
    }

    for(int i = 0; i <= n; i++){
        if(arr[i] % m == 0){
            num2 += arr[i];
        } else {
            num1 += arr[i];
        }
    }
    return num1 - num2;  
}