#include <stdio.h>
int main(int argc, char const *argv[]) {
  int firstprize[8] = {0};
  int invoicenumber[8] = {0};

  printf("Enter your first prize number!\n");
  for (int i = 0; i < 8; i++) {
    scanf("%i", &firstprize[i]);
  }

  if (invoicenumber == firstprize) {
    printf("Congratulations you've won the first prize!");
  } else {
  }

  return 0;
}
