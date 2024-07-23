#include<stdio.h>

void print_str(char **ppa, int cnt) {

	int i;
	
	for(i=0;i<cnt;i++) {
	
		printf("%s ", ppa[i]);
	
	}
	
}

int main(void) {
	
	char *ptr_ary[] = {"eagle", "tiger", "lion", "squirrel"};
	int count;
	
	count = sizeof(ptr_ary)/sizeof(ptr_ary[0]);
	print_str(ptr_ary, count);
	
	
	return 0;
}