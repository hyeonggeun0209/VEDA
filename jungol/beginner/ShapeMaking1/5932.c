#include<stdio.h>

void fill(int n, int (*arr)[100]) {
    int i,j;

    for (i = 0; i < n; i++) {
        if(i % 2 == 0) {
            for(j = 0; j < n; j++) {
                arr[i][j] = j+1;
            }
        } else {
            for(j = n-1; j >= 0; j--) {
                arr[i][j] = n-j;
            }
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