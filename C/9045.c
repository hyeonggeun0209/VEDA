#include <stdio.h>

int main() {
    int n;

    do {
        printf("1. 입력하기\n2. 출력하기\n3. 삭제하기\n4. 끝내기\n작업할 번호를 선택하세요. ");
        scanf("%d", &n);
        switch (n) {
        case 1: 
            printf("\n입력하기를 선택하였습니다.\n");
            break;
        case 2:
            printf("\n출력하기를 선택하였습니다.\n");
            break;
        case 3:
            printf("\n삭제하기를 선택하였습니다.\n");
            break;
        case 4:
            printf("\n끝내기를 선택하였습니다.\n");
            break;
        default:
            printf("\n잘못 입력하였습니다.\n");
            break;
        }
        printf("\n");
    } while (n != 4);

    return 0;
}