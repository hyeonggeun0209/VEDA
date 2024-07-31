#include <stdio.h>

void add(int n) {
    int i, j;
    for (i = n; i > 0; i--) {
        for (j = i; j > 0; j--) printf("*");
        printf("\n");
    }
    for (i = 1; i <= n; i++) {
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