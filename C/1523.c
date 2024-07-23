#include <stdio.h>

int main() {

    int n, m ;
    int i, j, k;

    scanf("%d %d", &n, &m);

    if (n > 100 || m < 1 || m > 3) {
        printf("INPUT ERROR!");
    } else if(m == 1) {
        for (i = 1; i < n+1; i++) {
            for (j = 0; j < i; j++) {
                printf("*");
            }
            printf("\n");
        }
    } else if(m == 2) {
        for (i = 0; i < n; i++) {
            for (j = n; j > i; j--) {
                printf("*");
            }
            printf("\n");
        }
    } else {
        for (i = 0; i < n; i++) {
            for (j = 0; j < n-i-1; j++) {
                printf(" ");
            }
            for (k = 0; k < 2* i + 1; k++) {
                printf("*");
            }
            printf("\n");
        }
    }

    return 0;
}