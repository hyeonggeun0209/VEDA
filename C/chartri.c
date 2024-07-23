#include <stdio.h>

int main() {
    int n;
    int i, j,a;
    int b = 0;
    char m = 'A';
    char arr[100][100] = {0};

    scanf("%d", &n);

    for (i = 0; i < n ; i++) {
        a = i;
        for (j = n-1; j >= b; j--) {
            if(m == '[') m = 'A';
            arr[a++][j] = m++;
        }
        b++;
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if(arr[i][j] == 0) {
                printf("  ");
            } else printf("%c ",arr[i][j]);
        }
        printf("\n");
    }

    return 0;
}