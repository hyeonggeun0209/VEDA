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
	
	int(*func_array[3])(int, int)  = {sum, mul, max};
	
	printf("0:sum, 1:mul, 2:max\n");
	printf("enter number : ");
	scanf("%d", &sel);

	func(func_array[sel]);
	
	return 0;
	
}