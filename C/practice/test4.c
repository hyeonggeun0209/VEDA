#include<stdio.h>

void func(int(*fp)(int, int), int a, int b) {
	int res;
	res = fp(a,b);
	printf("출력 : %d\n", res);
	
}

int sum(int a, int b) {
	return (a + b);
}

int mul(int a, int b) {
	return (a * b);
}

int sub(int a, int b) {
	return (a - b);
}

int div(int a, int b) {
	return (a / b);
}

int main(void) {
	int a, b;
    char c;
	printf("입력 : ");
	scanf("%d %c %d",&a,&c, &b);
	
	switch(c) {
		
		case '+': func(sum, a, b); break;
		case '-':	func(sub, a, b); break;
		case '*':	func(mul, a, b); break;
        case '/':	func(div, a, b); break;
		
	}
	return 0;
	
}