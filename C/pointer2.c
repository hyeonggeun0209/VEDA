#include<stdio.h>

void print_ary(int p,int n,int m) {

	int i,j;
	
	for(i=0;i<n;i++){
	
		for(j=0;j<m;j++) {
			
			printf("%d ", ((int (*)[m]) p)  [i][j]);
			//printf("%d ",((int *)p)[j]);
		
		}
		printf("\n");
	}
	
}

int main(void) {
	
	int ary[2][5] = {{0,1,2,3,4}, {5,6,7,8,9}};
	
	print_ary(ary,2,5);
	
	return 0;
	
}