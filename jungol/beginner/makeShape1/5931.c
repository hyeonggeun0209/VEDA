#include<stdio.h>

void fill(int n, int (*arr)[100]) {
    int i,j;

    for (i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
                arr[i][j] = i+1;
        }
    }

    for (i = 0; i < n; i ++) {
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

    fill(n,arr);
    
    return 0;
}