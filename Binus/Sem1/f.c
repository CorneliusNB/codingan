#include<stdio.h>

	float love(int a, int b, int c, int d){
		return (float)a/1 +(float)b/2 + (float)c/3 +(float)d/4 +  (float)b/2 +(float)c/3 + (float)d/4 +(float)c/3 +  (float)c/3 +(float)d/4 + (float)c/3 +(float)b/2 +  (float)d/4 +(float)c/3 + (float)b/2 +(float)a/1;
	}

	int main(){
		float ans[4]={0};
		int a, b, c, d;
		for(int i = 0; i<3; i++){
		scanf("%d %d %d %d", &a, &b, &c, &d);
		ans[i] += love(a, b, c, d);
	}
		for(int i = 0; i<3; i++){
			printf("%.2f\n", ans[i]);
	}
	return 0;
	}
