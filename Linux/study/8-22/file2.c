#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int fd;

int main() {

	fd = open("data2.txt", O_WRONLY|O_CREAT);

	printf("fd is %d\n", fd);

	write(fd, "hello", 6);

	close(fd);

	return 0;


}
