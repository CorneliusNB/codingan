#include <stdio.h>
#include<string.h>

void swap(char *x, char *y){
    char temp = *x;
    *x = *y;
    *y = temp;
}



int partition(char array[], int low, int high){
    int pivot_value = array[high];
    int i = low;
    for(int j = low; j < high; j++){
        if(array[j] <= pivot_value){
            swap(&array[i], &array[j]);
            i++;
        }
    }
    swap(&array[i], &array[high]);
    return i;
}

void quicksort_recursion(char array[], int low, int high){
    if(low < high){
        int pivot_index = partition(array, low, high);
        quicksort_recursion(array, low, pivot_index - 1);
        quicksort_recursion(array, pivot_index + 1, high);
    }
}

void quicksort(char array[], int length){
    quicksort_recursion(array, 0, length - 1);
}

int main(){
    int t, y;
    scanf("%d %d", &t, &y);

    char arr[201][201];

    for(int i = 0; i < t; i++){
        scanf("%s", arr[i]);   
        quicksort(arr[i], y);           
    }

    for(int i = 0; i < t; i++){
        for(int z = 0; z<t-1; z++){
            if(strcmp(arr[z], arr[z+1]) < 0){
                char temp[201];
                strcpy(temp, arr[z]);
                strcpy(arr[z], arr[z+1]);
                strcpy(arr[z+1], temp);
            }
        }
    }




    for(int i = 0; i < t; i++){
        printf("%s", arr[i]);
        printf("\n");
    }

    return 0;
}
