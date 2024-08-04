#include <stdio.h>

int main() {
    int n;
    int i, j;
    int a = 0;
    int b = 1;
    char m = 'A';
    char arr[100][100] = {0};

    scanf("%d", &n);

    if ((1 <= n && n <= 100) && (n % 2 == 1)) {
        for (i = n/2; i >= 0 ; i--) {
            a = i;
            for (j = 0; j < b; j++) {
                if(m == '[') m = 'A';
                    arr[a++][i] = m++;
            }
            b+=2;
        }
        
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                if(arr[i][j] == 0) {
                    printf("  ");
                } else printf("%c ",arr[i][j]);
            }
            printf("\n");
        }

    } else printf("INPUT ERROR");
    
    return 0;
}