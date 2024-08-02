#include <iostream>
using namespace std;

int getExp(int base, int exp) {
    int value = 1;
    for(int i = 0; i < exp; i++) 
        value = value * base;
    return value;
}

int main() {
    int v = getExp(2, 3);
    cout << "2의 3승은 " << v << endl;
    
    int e = getExp(2, -3);
    cout << "2의 -3승은 " << e << endl;

    return 0;
}