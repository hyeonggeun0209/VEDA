#include <stdio.h>

int main() {

    int n;
    int i, j, k;

    scanf("%d", &n);

    if (n > 100 || n % 2 == 0 || n < 0) printf("INPUT ERROR!");
    else {
        for(i = 0; i < n; i++ ) {
            if(i <= n/2) {
                for(j = 0; j < i; j++) {
                    printf(" ");
                }
                for(k = n/2; k >= i; k--) {
                    printf("*");
                }
                printf("\n");
            } else {
                for(j = 0; j < n/2 ; j++) {
                    printf(" ");
                }
                for(k = n/2; k <= i; k++) {
                    printf("*");
                }
                printf("\n");
            }
        }
    }

    return 0;
}