#include <iostream>
#include<fstream>
using namespace std;

int main() {
    const char* firstFile = "/Users/jinurung/VEDA/C++/study/12. C++ file io/student.txt";
    const char* secondFile = "/Users/jinurung/VEDA/C++/study/12. C++ file io/text.txt";

    fstream fout(firstFile, ios::out | ios::app);
    if(!fout) {
        cout << firstFile << "열기 오류";
        return 0;
    }

    fstream fin(secondFile, ios::in);
    if(!fin) {
        cout << secondFile << "열기 오류";
        return 0;
    }

    int c;
    while((c = fin.get()) != EOF) {
        fout.put(c);
    }

    fin.close();
    fout.close();

    return 0;
}