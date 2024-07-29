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
    bool operator ! ();
};

void Power::show() {
    cout << "kick = " << kick << ", " << "punch = " << punch << endl;
}

bool Power::operator!() {
    if(kick == 0 && punch == 0) return true;
    else return false;
}

int main() {
    Power a(0,0), b(5,5);
    if(!a) cout << "a's power is 0" << endl;
    else cout << "a's power is not 0" << endl;
    if(!b) cout << "b's power is 0" << endl;
    else cout << "b's power is not 0" << endl;

    return 0;
}