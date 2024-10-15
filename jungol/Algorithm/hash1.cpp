#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int main() {
    vector<int> nums = {3,3,3,2,2,4};
    vector<int> ans;
    int count = 0;

    while(ans.size() != nums.size()/2 && count != nums.size()) {
        if(find(ans.begin(), ans.end(), nums.at(count)) == ans.end() ) {
            ans.push_back(nums.at(count));
        }
        count++;
    }
    cout << ans.size() << endl;
    return 0;
}