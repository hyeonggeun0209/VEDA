#include <stdio.h>

int main() {
    int n,m, i, j;
    scanf("%d %d", &n, &m);

    if ( n > m) {
        for (i = 1; i <= 9 ; i++) {
            for (j = n; j >= m; j--) {
                printf("%d * %d =%3d   ",  j , i, j*i);
            }
            printf("\n");
        }
    } else {
        for (i = 1; i <= 9 ; i++) {
            for (j = n; j <= m; j++) {
                printf("%d * %d =%3d   ",  j , i, j*i);
            }
            printf("\n");
        }
    }


    return 0;
}