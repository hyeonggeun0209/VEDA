#include<stdio.h>

void fill(int n, int (*arr)[100]) {
    int i,j;
    int num = 1;
    for (i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
                arr[j][i] = num++;
        }
    }
}

int main() {
    int n;
    int i, j;
    int arr[100][100] = {0};
    scanf("%d", &n);

    fill(n,arr);
    for (i = 0; i < n; i ++) {
        for (j = 0; j < n; j++) {
            printf("%d ",arr[i][j]);
        }
        printf("\n");
    }
    return 0;
}