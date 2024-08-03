#include <stdio.h>

int main() {
    int i, cnt = 0;
    int arr[10] = {0,};

    for (i = 0; i < 10; i++) {
        scanf("%d ",&arr[i]);
        if(arr[i] % 2 == 0) cnt++;
    }

    printf("입력받은 짝수는 %d개입니다.", cnt);

    return 0;
}