#include <stdio.h>

int main() {
    int n;
    int sum_odd = 0;
    int cnt = 0;

    scanf("%d ", &n);

    while(n != 0) {
        if(n % 2 == 1) {
            sum_odd += n;
            cnt++;
        }
        scanf("%d ", &n);
    }

    printf("홀수의 합 = %d\n", sum_odd);
    printf("홀수의 평균 = %d\n", sum_odd/cnt);

    return 0;
}