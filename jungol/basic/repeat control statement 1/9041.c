#include <stdio.h>

int main() {
    int n;
    printf("점수를 입력하세요. ");
    scanf("%d", &n);

    while(0 <= n && n <= 100) {
        if(80 <= n) printf("축하합니다. 합격입니다.\n");
        else printf("죄송합니다. 불합격입니다.\n");
        printf("점수를 입력하세요. ");
        scanf("%d", &n);
    }

    return 0;
}