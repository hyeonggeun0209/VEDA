#include <stdio.h>

int main() {
    int i, j, cnt = 1;
    char c = 'a';

    for (i = 1; i <= 4; i++) {
        for (j = 0; j < i; j++) printf("%c ", c++);
        for (j = i; j < 5; j++) printf("%d ", cnt++); 
        printf("\n");
    }

    return 0;
}