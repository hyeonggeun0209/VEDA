#include <stdio.h>
#include <unistd.h>

int main() {
	
	while(1) {
		
		printf(".");

		sleep(1);
		
		fflush(stdout);
	}

	return 0;


}
