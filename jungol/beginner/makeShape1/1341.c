#include<stdio.h>

int main() {

    int a, b, n;
    int i, j,k;
    scanf("%d %d", &a, &b);
        
    if((a > 9 || a < 2) || (b > 9 || b < 2)) {
        printf("INPUT ERROR!\n");
    } else {
        if((a-b) > 0) {
            for(i=a;i>=b;i--){
                n=1;
                for(j=1;j<=3;j++) {
                    for(k=0;k<3;k++) {
                        printf("%d * %d =%3d   ",i,n,i*n);
                        n++;
                    }
                    printf("\n");
                }
                printf("\n");
            }
        } else {
            for(i=a;i<=b;i++){
                n=1;
                for(j=1;j<=3;j++) {
                    for(k=1;k<=3;k++) {
                        printf("%d * %d =%3d   ",i,n,i*n);
                        n++;
                    }
                    printf("\n");
                }
                printf("\n");
            }
        }
    }
    return 0;
}
