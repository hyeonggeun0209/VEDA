#include <stdio.h>

int main() {
    int n;
    char m = 'A';
    int i, j;
    char arr[100][100] = {0};
    scanf("%d", &n);

    for (i = n-1; i >= 0; i--) {
        for (j = n-1; j >= 0; j--) {
            if(m == '[') {
                m = 'A';
            }
            arr[j][i] = m++;
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