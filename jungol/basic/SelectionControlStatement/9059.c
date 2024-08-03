#include <stdio.h>

void add() {
    int i, j, n;

    for (i = 1; i <= 5; i++) {
        for (j = 5; j > i; j-- ) printf(" ");
        for (j = 1; j <2* i; j++) printf("*");
        printf("\n");
    }
}

int main() {

    add();

    return 0;
}