#include <iostream>
using namespace std;

int getExp(int base, int exp) {
    if(base <= 0 || exp <= 0)
        throw "음수 사용 불가";
    int value = 1;
    for(int i = 0; i < exp; i++) 
        value = value * base;
    return value;
}

int main() {
    int v = 0;
    try {
        v = getExp(2, 3);
        cout << "2의 3승은 " << v << endl;
        
        v = getExp(2, -3);
        cout << "2의 -3승은 " << v << endl;
    }
    catch(const char* s) {
        cout << "예외 발생 !!" << s << endl;
    }

    return 0;
}