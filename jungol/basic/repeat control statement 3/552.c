#include <stdio.h>

void add(int n) {
    int i, j;

    for (i = 1; i <= n; i++) {
        for(j = 1; j < i; j++) printf(" ");
        for (j =2 * n; j >= 2* i; j--) printf("*");
        printf("\n");
    }
}

int main() {
    int n;
    scanf("%d", &n);

    add(n);

    return 0;
}