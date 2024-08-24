#include <stdio.h>

int main(int argc, char** argv) {
	
	int n;
	FILE *in1, *in2, *out;
	char buf[BUFSIZ];

	if(argc != 4) {
		fprintf(stderr, "Usage : fappend file1 fil2 file3\n");
		return -1;
	}

	if((in1 = fopen(argv[1], "r")) == NULL) {
		perror(argv[1]);
		return -1;
	}
	
	if((in2 = fopen(argv[2], "r")) == NULL) {
		perror(argv[2]);
		return -1;
	}

	if((out = fopen(argv[3], "a")) == NULL) {
		perror(argv[2]);
		return -1;
	}

	while((n = fread(buf, sizeof(char), BUFSIZ, in1)) > 0)
		fwrite(buf, sizeof(char), n, out);

	while((n = fread(buf, sizeof(char), BUFSIZ, in2)) > 0)
		fwrite(buf, sizeof(char), n, out);


	fclose(out);
	fclose(in1);
	fclose(in2);

	return 0;
}
