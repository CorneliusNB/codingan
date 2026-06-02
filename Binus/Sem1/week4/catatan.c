#include <stdio.h>
int main(int argc, char *argv[]) {

  // single pointer
  int a = 30;
  int *ptr = &a;
  a = 50;
  printf("Nilai a: %d\n", a);
  printf("Alamat dari a: %p\n", ptr);
  printf("Isi dari ptr: %p\n", ptr);
  printf("Isi dari pointer ptr: %d\n", *ptr);

  // double pointer
  printf("\nDOUBLE POINTER\n");
  int **ptr_ptr = &ptr; // double pointer menyimpan alamat sebuah pointer
  printf("Alamat dari ptr: %p\n", &ptr);
  printf("isi dari ptr_ptr: %p\n", ptr_ptr);
  printf("isi dari pointer to pointer ptr: %d\n", **ptr_ptr);

  printf("\nINI ARRAY\n");

  return 0;
}
