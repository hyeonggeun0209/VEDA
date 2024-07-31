#include <stdio.h>

int main() {
    int n;
    int odd_cnt = 0;
    int even_cnt = 0;

    scanf("%d ", &n);

    while(n != 0) {
        if(n % 2 == 0) even_cnt++;
        else odd_cnt++;
        scanf("%d ", &n);
    }

    printf("odd : %d\n", odd_cnt);
    printf("even : %d\n", even_cnt);

    return 0;
}