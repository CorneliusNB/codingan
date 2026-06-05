#include <stdio.h>

int numberOfEmployeesWhoMetTarget(int *hours, int hoursSize, int target) {
  int num = 0;
  for (int i = 0; i < hoursSize; i++) {
    if (hours[i] >= target) {
      num++;
    }
  }
  return num;
}
