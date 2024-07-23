#include<stdio.h>

void fill(int n, int m, int (*arr)[100]) {
    int i,j;
    int num = 1;
    for (i = 0; i < n; i++) {
        if(i % 2 == 0) {
            for(j = 0; j < m; j++) {
                arr[i][j] = num++;
            }
        } else {
            for(j = m-1; j >= 0; j--) {
                arr[i][j] = num++;
            }
        }
    }
}
int main() {
    int n, m;
    int i, j;
    int arr[100][100] = {0};
    scanf("%d %d", &n, &m);

    fill(n,m,arr);
    for (i = 0; i < n; i ++) {
        for (j = 0; j < m; j++) {
            printf("%d ",arr[i][j]);
        }
        printf("\n");
    }
    return 0;
}