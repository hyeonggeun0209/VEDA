#include <stdio.h>

void dia_zig(int n, int (*arr)[100]) {

    int i, j;
    int num = 1;

    for(i = 0; i < n; i++) {
        if (i % 2 == 1) {
            for (j = 0; j <= i; j++) {
                arr[i-j][j] = num++;
            }
        } else {
            for (j = i; j >= 0; j--) {
                arr[i-j][j] = num++;
            }
        }
        
    }

    for(i = n; i < 2*n-1; i++) {
        if (i % 2 == 1) {
            for (j = n-1; j > 0; j--) {
                if(n <= j || n <= i-j) continue;
                else arr[j][i-j] = num++;
            }
        } else {
            for (j = n-1; j > 0; j--) {
                if(n <= i-j || n <= j) continue;
                else arr[i-j][j] = num++;
            }
        }
    }

     for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ",arr[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n;
    int arr[100][100] = {0};

    scanf("%d", &n);

    dia_zig(n, arr);


    return 0;
}