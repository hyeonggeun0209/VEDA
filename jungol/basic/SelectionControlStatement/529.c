#include <stdio.h>

int main() {

    int a,b,fi;
    scanf("%d %d", &a,&b);

    fi = b+100-a;
    printf("%d\n",fi);
    if(fi > 0) {
        printf("Obesity");
    }
    
    return 0;
}
