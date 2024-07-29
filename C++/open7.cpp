#include <iostream>
#include <string>
using namespace std;

class Histogram {
private:
    string str;
public:
    Histogram(string s);
    Histogram& operator << (string s);
    Histogram& operator << (char c);
    void operator ! ();
};

Histogram::Histogram(string s) {
    str = s;
}

Histogram& Histogram::operator <<(string s) {
    str += s;
    return *this;
}
void Histogram::operator!() {
    cout << str << endl << endl;
    char c, d;
    int cnt = 0;
    int arr[26] = {0,};

    for (int i = 0; i < str.length(); i++) {
        c = str[i];
        if(isalpha(c)) {
            d = tolower(c);
            arr[d-97]++;
            cnt++;
        }
    }

    cout << "총 알파벳 수 " << cnt << endl;

    for (int i = 0; i < 26; i++) {
        cout << (char) (i + 97) << " : ";
        for (int j = 0; j < arr[i]; j++) {
            cout << "*";
        }
        cout << endl;
    }
}

Histogram& Histogram::operator <<(char c) {
    str += c;
    return *this;
}

int main() {
    Histogram song("Wise men say, \nonly fools rush in But I can't help, \n");
    song << "falling" << " in love with you." << "- by ";
    song << 'k' << 'i' << 't';
    !song;

    return 0;
}