#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    vector<string> v = {"[403]James", "[404]Azad,Louis,Andy", "[101]Azad,Guard"};
    for(int i = 0; i < v.size(); i++) {
        string s = v[i];
        string num = "";
        string names = "";
        bool isNum = false;
        for(int j = 0; j < s.length(); j++) {
            if(s[j] == '[') {
                isNum = true;
            }
            else if(s[j] == ']') {
                isNum = false;
            }
            else if(isNum) {
                num += s[j];
            }
            else {
                names += s[j];
            }
        }
        // Replace commas with spaces
        for(int k = 0; k < names.length(); k++) {
            if(names[k] == ',') {
                names[k] = ' ';
            }
        }
        cout << num << " " << names << endl;
    }
    return 0;
}