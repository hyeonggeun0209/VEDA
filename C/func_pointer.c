#include<stdio.h>

void func(int(*fp)(int, int)) {
	
	int a,b;
	int res;
	
	printf("enter 2 number : ");
	scanf("%d %d",&a,&b);
	res = fp(a,b);
	printf("result : %d\n", res);
	
}

int sum(int a, int b) {
	
	return (a + b);
}

int mul(int a, int b) {
	
	return (a * b);
}
int max(int a, int b){
	
	if(a>b) return a;
	else	return b;
}

int main(void) {
	int sel;
	
	printf("1:sum, 2:mul, 3:max\n");
	printf("enter number : ");
	scanf("%d", &sel);
	
	switch(sel) {
		
		case 1: func(sum); break;
		case 2:	func(mul); break;
		case 3:	func(max); break;
		
	}
	
	return 0;
	
}