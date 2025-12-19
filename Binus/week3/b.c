#include <stdio.h>
int main(int argc, char *argv[]) {
  int t;
  int y = 1;
  scanf("%d", &t);
  getchar();
start_of_program:;

  char word[6] = "ashiap";
  int arr[6] = {0};
  scanf("%d %d %d %d %d %d", &arr[0], &arr[1], &arr[2], &arr[3], &arr[4],
        &arr[5]);

  printf("Case #%d: ", y);
  for (int i = 0; i < 6; i++) {
    for (int x = 0; x < arr[i]; x++) {
      printf("%c", word[i]);
    }
  }
  printf("\n");
  t--;
  y++;
  if (t != 0) {
    goto start_of_program;
  }
  return 0;
}
