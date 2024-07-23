#include <stdio.h>

void find(int n, int *arr) {
    int i;
    int div, mul = 0;

    for (i = 0; i < n; i++) {
        if (n % arr[i] == 0) div += arr[i];
        else if (arr[i] % n == 0) mul += arr[i];
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

    find(m, arr);

    return 0;
}