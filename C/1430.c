#include <stdio.h>

int main() {

    int x, y, z;
    int n, m, i;

    int arr[10] = {0};

    scanf("%d \n%d \n%d",&x, &y, &z);

    n = x * y * z;

    for (i = 0; i < 10; i++) {
        if(n == 0) {
            break;
        } else {
            m = n % 10;
            n = n / 10;
            arr[m]++;
        }
    }
    
    for (i = 0; i < 10; i++) {
        printf("%d\n", arr[i]);
    }

    return 0;
}