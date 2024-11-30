#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;

int main() {
    vector<string> room = {"[403]James", "[404]Azad,Louis,Andy", "[101]Azad,Guard"};
    vector<string> a;
    char separator = ',';
    istringstream iss(room[1]);
    string str, s;
    while (getline(iss, str, separator)) {
        a.push_back(str);
    }
    separator = ']';
    istringstream iss2(a[0]);
    while (getline(iss2, str, separator)) {
        a.push_back(str);
    }
    // string subs1 = room[1].substr(1, a[3].find(']'));
    // subs1.pop_back();
    // subs1.erase(0, 1);
    // a[0] = subs1;
    for(int i = 0; i < a.size(); i++) {
        cout << a[i] << " ";
    }
    return 0;
}