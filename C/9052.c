#include <stdio.h>

int main() {
    int i , sum = 0;
    int n, m;
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf("%d ",&m);
        sum += m;
    }

    printf("avg : %.1f\n",(double) sum/n);
    if((double) sum/n >= 80) printf("pass");
    else printf("fail");

    return 0;
}