#include <stdio.h>
int main(int argc, char *argv[]) {
  int x;
  int f;
  scanf("%d", &x);
  for (int i = 1; i <= 100; i++) {
    if (x % i == 0) {
      f = i;
    }
  }

  printf("%d", f);

  return 0;
}
