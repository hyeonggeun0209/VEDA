#include <stdio.h>

int main() {
    int n;
    scanf("%d ", &n);

    while(n != -1) {
        if(n % 3 == 0) {
            printf("%d\n", n / 3);
        }
        scanf("%d ", &n);
    }

    return 0;
}