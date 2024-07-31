#include <stdio.h>

int main() {
    int i, j;
    int n = 6;
    for (i = 1; i <= 5; i++) {
        for (j = i+1; j <= n; j++) {
            printf("%d ", j);
        }
        printf("\n");
        n++;
    }

    return 0;
}