#include <stdio.h>
int main(int argc, char *argv[]) {
  int N = 0;
  scanf("%d", &N);
  int arr[N];
  int arr2[N];
  int arr3[N];
  for (int i = 0; i < N; i++) {
    arr[i] = 0;
    arr2[i] = 0;
    arr3[i] = 0;
  }

  for (int i = 0; i < N; i++) {
    scanf("%d", &arr[i]);
  }
  for (int i = 0; i < N; i++) {
    scanf("%d", &arr2[i]);
  }
  for (int i = 0; i < N; i++) {
    arr3[arr[i]] = arr2[i];
  }
  for (int i = 0; i < N; i++) {
    printf("%d", arr3[i]);
    if (i < N - 1) {
      printf(" ");
    }
  }
  printf("\n");
  return 0;
}
