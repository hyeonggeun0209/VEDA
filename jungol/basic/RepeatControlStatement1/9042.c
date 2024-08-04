#include <stdio.h>

int main() {
    int n;
    int sum = 0;
    int cnt = 0;

    scanf("%d ", &n);

    while(n != 0) {
        sum += n;
        cnt++;
        scanf("%d ", &n);
    }

    printf("입력된 자료의 개수 = %d\n", cnt);
    printf("입력된 자료의 합계 = %d\n", sum);
    printf("입력된 자료의 평균 = %.2f\n", (double) sum/cnt);

    return 0;
}