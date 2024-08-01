#include <stdio.h>
#include <unistd.h>

int main() {
    for (int i = 0; i <=100; i++) {
        printf("\r%3d%%", i);
        fflush(stdout);
        sleep(1);
    }
    printf("\n");
    return 0;
}