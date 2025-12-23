#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){
  char kata1[201];
  char kata2[201];
  
  // membaca input
  scanf("%s", kata1); getchar();
  scanf("%s", kata2); getchar();

  char hasil[401];
  int idh = 0; 
  
  int len1 = strlen(kata1); 
  int len2 = strlen(kata2); 
  
  // mencari prefix (awalan)
  int minlen = len1 < len2 ? len1 : len2;
  
  for(int i = 0; i < minlen; i++){
    if(tolower(kata1[i]) == tolower(kata2[i])){
      if(isupper(kata1[i])){
        hasil[idh] = tolower(kata1[i]);
      } else {
        hasil[idh] = toupper(kata1[i]);
      }
      idh++;
    } else {
      break;
    }
  }

  // cari suffix (akhiran)
  int suflen = 0; 
  int id1 = len1 - 1; 
  int id2 = len2 - 1; 

  while(id1 >= 0 && id2 >= 0){
    if(tolower(kata1[id1]) == tolower(kata2[id2])){
      suflen++;
      id1--;
      id2--;
    } else {
      break;
    }
  }

  // gabungin akhiran ke hasil
  for(int i = len1 - suflen; i < len1; i++){
    if(isupper(kata1[i])){
      hasil[idh] = tolower(kata1[i]);
    } else {
      hasil[idh] = toupper(kata1[i]);
    }
    idh++;
  }

  hasil[idh] = '\0';

  if(idh == 0){
    printf("No Output\n");
  } else {
    printf("%s\n", hasil);
  }

  return 0;
}
