#include <stdio.h>

int main() {

    int n, i;
    int odd = 0, even = 0;

    for (i = 0; i < 10; i++) {
        scanf("%d ", &n);
        if(n % 2 == 0) even++;
        else odd++;
    }

    printf("even : %d\n", even);
    printf("odd : %d", odd);

    return 0;
}