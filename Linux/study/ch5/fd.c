#include <stdio.h>
#include <unistd.h>

int main() {

    int a;
    close(0);
    scanf("%d", &a);                   // fd : 0 (stdin)
    close(1);
    printf("Hello World\n");        // fd : 1 (stdout)
    close(2);
    perror("Hello Error\n");        // fd : 2 (stderr)

    return 0;
}
