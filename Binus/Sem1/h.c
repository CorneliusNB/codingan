#include<stdio.h>
	int main(){
		float a, b, c = 0;
		scanf("%f %f %f",&a,&b,&c);
		float res = a * (20.0/100.0) + b * (30.0/100.0) + c * (50.0/100.0);
		printf("%.2f\n", res);
	}	
