#include<stdio.h>

int main() {
    long int N;
    scanf("%ld", &N);

    // Calculating the total damage
    long int total_damage = 100 * N + 50 * (N - 1) * N / 2;

    printf("%ld\n", total_damage);
    return 0;
}

