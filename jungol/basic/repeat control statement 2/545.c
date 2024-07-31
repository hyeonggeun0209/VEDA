#include <stdio.h>

int main() {
    int i;
    int cnt3 = 0, cnt5 = 0;
    int arr[10] = {0,};

    for (i = 0; i < 10; i++) {
        scanf("%d ",&arr[i]);
        if(arr[i] % 3 == 0) cnt3++;
        if(arr[i] % 5 == 0) cnt5++;

    }

    printf("Multiples of 3 : %d\n", cnt3);
    printf("Multiples of 5 : %d", cnt5);

    return 0;
}