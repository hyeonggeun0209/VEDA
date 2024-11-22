#include <iostream>
using namespace std;

template <class T> 
T *remove(T src[], T sizeSrc, T minus[], T sizeMinus, T& retSize) {
    int i, j;
    T *ret = new T[sizeSrc];
    for (i = 0; i < sizeSrc; i++) {
        for (j = 0; j < sizeMinus; j++) {
            if(src[i] == minus[j]) {
                break;
            }
        }
        if(j == sizeMinus) {
            ret[retSize] = src[i];
            retSize++;
        }
    }
    return ret;
}

int main() {
    int m = 0;
    int& n = m;
    int src[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int minus[] = {1, 5, 4, 9};
    int sizeS = sizeof(src)/sizeof(src[0]);
    int sizeM = sizeof(minus)/sizeof(minus[0]);
    
    // cout << sizeS << endl;
    // cout << sizeM <<endl;

    int *a = remove(src, sizeS, minus, sizeM, n);

    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
}