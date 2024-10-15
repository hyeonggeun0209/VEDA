#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int main() {
    vector<string> v = {"123","456","789"};
    sort(v.begin(), v.end());

    for(int i = 0; i < v.size() - 1; i++) {
        if(v[i] == v[i+1].substr(0, v[i].size()))
        cout << "false";
    }
    cout << "true";
    return 0;
}