#include <stdio.h>

void swapA(int *n, int *m) {

}

void swapV(int n, int m) {

}

int main() {
    int n, m;
    n = 2;
    m = 9;
    printf("%d %d", n, m);

    swap(&n, &m);

    printf("%d %d", n, m);

    swap(n, m);


    return 0;
}