#include <iostream>
using namespace std;

class Power {
private:
    int kick;
    int punch;
public:
    Power(int kick=0, int punch=0) {
        this->kick = kick;
        this->punch = punch;
    }
    void show();
    Power operator + (int op2);
};

void Power::show() {
    cout << "kick = " << kick << ", " << "punch = " << punch << endl;
}

Power Power::operator+(int op2) {
    Power tmp;
    tmp.kick = this->kick + op2;
    tmp.punch = this->punch + op2;
    return tmp;
}

int main() {
    Power a(3,5), b;
    a.show();
    b.show();
    b = a + 2;
    a.show();
    b.show();

    return 0;
}