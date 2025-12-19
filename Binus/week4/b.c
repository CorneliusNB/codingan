#include <stdio.h>
int main(int argc, char *argv[]) {
  int T = 0;
  scanf("%d", &T);
  getchar();
  for (int i = 0; i < T; i++) {
    int N = 0; // number of jojos friends
    int M = 0; // number of rooms in the hallway
    int Marray[M * N];
    for (int i = 0; i < M * N; i++) {
      Marray[i] = 0;
    }
    int Q = 0; // list of which friends will visit the hallway
    scanf("%d %d %d", &N, &M, &Q);
    getchar();
    for (int i = 0; i < M * N; i++) {
      scanf("%d", &Marray[i]);
      getchar();
    }
    for (int i = 0; i < N; i++) {
      int truthness = 0;
      int falseness = 0;
      for (int j = 0; j < M; j++) {
        if (Marray[j] == 0) {
          truthness += 1;
        } else {
          falseness += 1;
        }
      }
      printf("Case #%d:\n", i + 1);
      if (truthness > falseness) {
        printf("YES\n");
      } else {
        printf("NO\n");
      }
    }
  }
  return 0;
}
