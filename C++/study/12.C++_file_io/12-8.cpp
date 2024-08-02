#include <iostream>
#include <fstream>
using namespace std;

int main() {
    const char* file = "/Users/jinurung/VEDA/C++/study/12.C++_file_io/text.txt";

    ifstream fin;
    fin.open(file, ios::in | ios::binary);
    if(!fin) {
        cout << "파일 열기 오류";
        return 0;
    }

    int count = 0;
    char s[32]; // 블록 단위로 읽어들일 버퍼
    while (!fin.eof()) {
        fin.read(s, 32); // 최대 32바이트를 읽어 배열 s에 저장
        int n = fin.gcount(); // 실제 읽은 바이트 수 알아냄
        cout.write(s, n); // 버퍼에 있는 n 개의 바이트를 화면에 출력
        count += n;
    }

    cout << "읽은 바이트 수는 " << count << endl;
    fin.close();
    
    return 0;
}