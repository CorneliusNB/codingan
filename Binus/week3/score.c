#include <stdio.h>
int main(int argc, char *argv[]) {
  int score;
  printf("Masukkan nilai ujian kamu");
  scanf("%d", &score);
  getchar();
  if (score > 0) {
    printf("Score kamu positif\n");
    printf("Terima kasih\n");
  } else if (score == 0) {
    printf("score kamu nol");
  } else if (score >= 65) {
    printf("lulus");
  } else if (score < 65) {
    printf("tidak lulus");
  } else if (score > 96) {
    printf("perfect");
  } else if (score <= 90) {
    printf("good");
  }
  return 0;
}
