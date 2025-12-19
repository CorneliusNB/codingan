#include <stdio.h>

int addDigits(int num) {
  if (num == 0) {
    return 0;
  }
  if (num % 9 == 0) {
    return 9;
  }
  return num % 9;
}

int main(int argc, char const *argv[]) {
  printf("%d", addDigits(388));
  return 0;
}
