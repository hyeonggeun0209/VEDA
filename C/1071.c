#include <stdio.h>

void find(int n, int m, int *arr) {
    int i;
    int div = 0;
    int mul = 0;

    for (i = 0; i < n; i++) {
        if (m % arr[i] == 0) div += arr[i];
        if (arr[i] % m == 0) mul += arr[i];
    }
    printf("%d\n%d", div, mul);
}


int main() {

    int i, n, m;
    int arr[40] = {0};

    scanf("%d\n", &n);
    
    for (i = 0; i < n; i++) {
        scanf("%d ", &arr[i]);
    }

    scanf("%d",&m);

    find(n, m, arr);

    return 0;
}