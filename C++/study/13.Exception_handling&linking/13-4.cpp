#include <iostream>
using namespace std;

int main() {
    int n, sum, avg;
    while (true) {
        cout << "합을 입력하세요. ";
        cin >> sum;
        cout << "인원수를 입력하세요. ";
        cin >> n;
        
        try {
            if(n <= 0) // 오류 탐지
                throw n; // 예외 발생. catch(int x) 블록으로 점프
            else
                avg = sum / n;
        }
        catch(int x) {
            cout << "예외 발생!! " << x << "으로 나눌 수 없음" << endl;
            avg = 0;
            cout << endl;
            continue;
        }
        cout << "평균 = " << avg << endl << endl;
    }
}