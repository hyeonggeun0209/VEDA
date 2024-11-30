#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    vector<int> num = {1, 23, 456};
    vector<string> a;
    int n = 1;
    for(int i = 0; i < num.size(); i++) {
        if(n < to_string(num[i]).size()) n =  to_string(num[i]).size();
    }
    for(int i = 0; i < num.size(); i++) {
        string s = to_string(num[i]);
        a.push_back(s.insert(0, n - s.size(), '0'));
        cout << a[i] << endl;
    }

    return 0;
}