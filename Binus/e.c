#include<stdio.h>
	int main(){
		float x, y;
		scanf("%d %d", &x, &y);
		double z = (y / x) * 100;
		printf("%.4lf%%\n", z);
		return 0;
	}
