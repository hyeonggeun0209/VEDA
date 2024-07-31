#include <stdio.h>

int main() {
    int n;
    int cnt = 0;

    scanf("%d ", &n);

    while(n != 0) {
        if(n % 3 != 0 && n % 5 != 0) {
            cnt++;
        }
        scanf("%d ", &n);
    }

    printf("%d\n", cnt);

    return 0;
}