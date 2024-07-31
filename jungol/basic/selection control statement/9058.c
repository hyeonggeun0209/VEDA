#include <stdio.h>

void add(int n) {
    int i, j;

    for (i = 1; i <= n; i++) {
        for(j = n; j > i; j-- ) printf(" ");
        for (j = 0; j < i; j++) printf("*");
        printf("\n");
    }
}

int main() {
    int n;
    scanf("%d", &n);

    add(n);

    return 0;
}