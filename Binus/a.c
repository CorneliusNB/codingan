#include<stdio.h>
#include<string.h>
	int main(){
		int amount = 0;
		printf("How many sets?");scanf("%d", &amount);getchar();
		start_of_program:
		char arr[100];
		printf("Enter your data: ");scanf("%s", arr);getchar();
		printf("Reversed: ");
		for(int i = strlen(arr) - 1; i >= 0; i--){
			printf("%c", arr[i]);
		}
		amount--;
		if(amount > 0){
			goto start_of_program;

	}
	return 0;
	}		
