#include <stdio.h>

int main() {
    int arr[100];
    int i = 0;
    
    do {
        scanf("%d", &arr[i]);
    } while (arr[i++] != 0);
    i--;
    for(int j = 0; j < i; j++)
        if(j%2 == 1) printf("%d ", arr[j]);

    return 0;
}