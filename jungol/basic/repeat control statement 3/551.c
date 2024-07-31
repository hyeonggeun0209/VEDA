#include <stdio.h>

void add(int n) {
    int i, j;

    for (i = 0; i < n; i++) {
        for (j = 0; j < i; j++ ) printf(" ");
        for (j = n; j > i; j--) printf("*");
        printf("\n");
    }
}

int main() {
    int n;
    scanf("%d", &n);

    add(n);

    return 0;
}