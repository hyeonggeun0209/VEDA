#include <iostream>
#include <vector>
using namespace std;

int main() {
    int ans = 0;
    vector<int> a = {6,1,6,6,7,6,6,7};
    int n = a.size()/2;
    int b[100] = {0};

    for(int i = 0; i < a.size(); i++) {
        b[a[i]]++;
    }
    for(int j = 0; j < 100; j++) {
        if(b[j] > n) cout << j << endl;
    }
    return 0;
}