#include <stdio.h>

FILE *fp;

int main() {
	
	fp = fopen("data.txt", "w");

	fprintf(fp, "1+2=%d", 1+2);

	fclose(fp);

	return 0;
}


