#include<stdio.h>

int main() {

    int a, b;
    int i, j, k, n;
    while (1) {
        scanf("%d %d", &a, &b);
        
        if((a > 9 || a < 2) || (b > 9 || b < 2)) {
            printf("INPUT ERROR!\n");
            continue;
        } else {
            if((a-b) > 0) {
                for(i=1;i<10;i++){
                    for(j=a;j>=b;j--) {
                        printf("%d * %d =%3d   ",j,i,j*i);
                    }
                    printf("\n"); 
                }
            } else {
                for(i=1;i<10;i++){
                    for(j=a;j<=b;j++) {
                        printf("%d * %d =%3d   ",j,i,j*i);
                    }
                    printf("\n"); 
                }
            }
            break;
        }
    }
        
    return 0;
    
}
