#include <stdio.h>

int main() {

    int a,b;

    scanf("%d %d", &a,&b);

    if(a > b) {
        printf("입력받은 수 중 큰 수는 %d이고 작은 수는 %d입니다.\n",a,b);
    } else printf("입력받은 수 중 큰 수는 %d이고 작은 수는 %d입니다.\n",b,a);
    
    return 0;
}
