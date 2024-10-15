#include <string>
#include <vector>
#include <set>
#include <iostream>
using namespace std;

int main() {
    string answer = "";
    vector<string> participant = {"mislav", "stanko", "mislav", "ana"};
    vector<string> completion = {"stanko", "ana", "mislav"};
    multiset<string> s1(participant.begin(), participant.end());
    multiset<string> s2(completion.begin(), completion.end());
    multiset<string>::iterator it1;
    multiset<string>::iterator it2;

    for(it1 = s1.begin(), it2 = s2.begin(); it1 != s1.end(); it1++,it2++) {
        // cout << *it1 << endl;
        if(*it1 != *it2) {
            answer = *it1;
            break;
        }
    }
    cout << *it1;
    return 0;
}