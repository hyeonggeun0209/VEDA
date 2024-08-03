#include <stdio.h>

int main() {

    int a;
    printf("점수를 입력하세요. ");
    scanf("%d", &a);
    if(a >= 80) {
        printf("축하합니다. 합격입니다.");
    } else printf("죄송합니다. 불합격입니다.");
    
    return 0;
}
