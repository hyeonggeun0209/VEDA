#include <iostream>
#include <fstream>
using namespace std;

int main() {
    // 소스 파일과 목적 파일 이름
    const char* srcFile = "/Users/jinurung/VEDA/C++/study/12.C++_file_io/desert.jpg";
    const char* destFile = "/Users/jinurung/VEDA/C++/study/12.C++_file_io/desert.jpg";

    // 소스 파일 열기
    ifstream fsrc(srcFile, ios::in | ios::binary); // 바이너리 I/O
    if(!fsrc) {
        cout << srcFile << "열기 오류" << endl;
        return 0;
    }

    ofstream fdest(destFile, ios::out | ios::binary); // 바이너리 I/O
    if(!fdest) {
        cout << destFile << "열기 오류" << endl;
        return 0;
    }

    char buf[1024];
    while(!fsrc.eof()) {
        fsrc.read(buf, 1024);
        int n = fsrc.gcount();
        fdest.write(buf, n);
    }

    cout << srcFile << "을" << destFile << "로 복사 완료" << endl;
    fsrc.close();
    fdest.close();

    return 0;
}