#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  char string[100];
  int y = 0;
  scanf("%[^\n]", string);
  char string2[100];
  for (int i = -1; i != 0; i++) {
    string2[y++] = string[i];
  }
  printf("%s\n", string2);
}
