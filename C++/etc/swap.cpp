#include <iostream>
#include <cstdio>
using namespace std;

void swapR(int &n, int &m) {
    int temp;
    temp = n;
    n = m;
    m = temp;
}

void swapA(int *n, int *m) {
    int temp;
    temp = *n;
    *n = *m;
    *m = temp;
}

void swapV(int n, int m) {
    int temp;
    temp = n;
    n = m;
    m = temp;
}
int main() {
    int n, m;
    n = 2, m = 9;
    cout << "original : " << n << " " << m << endl;

    n = 2, m = 9;
    swapV(n, m);
    cout << "call by value : " << n << " " << m << endl;

    n = 2, m = 9;
    swapR(n, m);
    cout << "call by reference : " << n << " " << m << endl;

    n = 2, m = 9;
    swapA(&n, &m);  
    cout << "call by address : " << n << " " << m << endl;

    return 0;
}