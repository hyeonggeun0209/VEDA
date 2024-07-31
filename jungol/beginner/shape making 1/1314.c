#include <stdio.h>

int main() {
    int n;
    char m = 'A';
    int i, j;
    char arr[100][100] = {0};
    scanf("%d", &n);

    for (i = 0; i <n ; i++) {
        if(i % 2 == 0) {
            for (j = 0; j < n; j++) {
                if(m == '[') m = 'A';
                arr[j][i] = m++;
            }
        } else {
            for (j = n-1; j >= 0; j--) {
                if(m == '[') m = 'A';
                arr[j][i] = m++;
            }
        }
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%c ",arr[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}