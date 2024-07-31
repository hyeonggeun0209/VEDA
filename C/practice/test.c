#include<stdio.h>

void swap(char **ppa, char **ppb) {

	char *pt;
	pt = *ppa;
	*ppa = *ppb;
	*ppb = pt;
	
}

int main(void) {
	
	char *pa = "success";
	char *pb = "failure";
	
	printf("%s %s\n", pa, pb);
	
	swap(&pa, &pb);
	
	printf("%s %s", pa, pb);
	
	return 0;
}