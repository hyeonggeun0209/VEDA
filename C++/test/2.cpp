#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    vector<int> ans;
    int n = 1;
    string s = "aaa";
    for(int i = 0; i < s.length(); i++) {
        if(i+1 == s.length()) {
            ans.push_back(n); 
            continue;
        } 
        if(s[i] == s[i+1]) {
            n++;
        }
        else {
            ans.push_back(n);
            n = 1;
        }
    }
    if (ans.size() > 1) { 
        ans[0] += ans[ans.size() - 1];
        ans.pop_back();
    }
    sort(ans.begin(), ans.end());

    for(int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }

    return 0;
}