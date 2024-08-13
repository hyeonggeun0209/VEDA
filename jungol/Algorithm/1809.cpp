#include<iostream>
#include<stack>
using namespace std;
#define MAX 80001

int N;
int H[MAX];

void input(){
    cin >> N;
    for(int i=0; i<N; i++) cin >> H[i];
}

void find(){
    int ans = 0;

    stack<int> st;
    for(int i=0; i<N; i++){
        while(!st.empty() && st.top() <= H[i]) st.pop();
        ans += st.size();
        st.push(H[i]);
    }
    cout << ans;
}

int main(){
    input();
    find();
}