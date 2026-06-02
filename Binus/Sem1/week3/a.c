#include <stdio.h>
int main(int argc, char *argv[]) {
  int x, y, z = 0;
  scanf("%d %d %d", &x, &y, &z);
  getchar();

  int t1 = z - x;
  int t2 = y - z;

  if (t1 == t2 && t1 >= 0) {
    printf("%d\n", t1);
  } else {
    printf("-1\n");
  }
  return 0;
}
