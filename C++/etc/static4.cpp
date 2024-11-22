#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

class UpAndDownGame {
public:
    static int number;
    static int askNum(int n) {
        if(number == n) return 1;
        else if(number < n) return 2;
        else return 3;
    }
};

class Person {
    char* name;
public:
    Person(const char* name);
    char* call() { return this->name; }
};

Person::Person(const char* name) {
    int len = strlen(name);
    this->name = new char [len+1];
    strcpy(this->name, name);
}

int UpAndDownGame::number = 0;

int main() {
    srand((unsigned)time(0));
    int n = rand();
    UpAndDownGame::number = n % 100;
    int a = 0, b = 99;
    int cnt = 0;
    
    Person person1("강인수");
    Person person2("오은경");
    Person *p;

    cout << "Up & Down 게임을 시작합니다." << endl;
    cout << "답은 "<< a << "과 " << b << "사이에 있습니다." << endl;

    while(true) {
        p = (cnt % 2 == 0) ? &person1 : &person2;
        cout << p->call() << ">>";
        cin >> n;
        if (UpAndDownGame::askNum(n) == 1) {
            cout << p->call() <<"이/가 이겼습니다!!";
            break;
        } else if(UpAndDownGame::askNum(n) == 2) {
            b = n;
            cout << "답은 "<< a << "과 " << b << "사이에 있습니다." << endl;
        } else {
            a = n;
            cout << "답은 "<< a << "과 " << b << "사이에 있습니다." << endl;
        }
        cnt++;
    }
    return 0;
}
