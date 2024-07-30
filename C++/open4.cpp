#include <iostream>
#include <string>
using namespace std;

class Player {
private:
    string name;
public:
    string getName() { return name;}
    void setName(string name) { this->name = name;}
};

class WordGame {
private:
    string word;
    Player* p;
    int num;
public:
    WordGame();
    ~WordGame();
    void getPlayers();
    void start();
    string getWord() { return this->word;}
    void setWord(string str) {  this->word = str;}
    bool compWord(string str);
};

WordGame::WordGame() {
    getPlayers();
    start();
}

WordGame::~WordGame() {
    cout << "게임을 종료합니다." << endl;
    delete [] p;
}

void WordGame::getPlayers() {
    cout << "끝말 잇기 게임을 시작합니다" << endl;
    cout << "게임에 참가하는 인원은 몇명입니까? ";
	cin >> num;
	p = new Player[num];
    string name;
    for (int i = 0; i < num; i++) {
        cout << "참가자의 이름을 입력하세요. 빈칸 없이 >> " ;
        cin >> name;
        p[i].setName(name);
    }
}

void WordGame::start() {
    int cnt = 0;
    string s;
    word = "아버지";
    cout << "시작하는 단어는 " << word <<"입니다." << endl;
    while (true) {
        cout << p[cnt%num].getName() << " >> ";
        cin >> s;
        if (compWord(s)) {
            setWord(s);
        } else {
            cout << "틀린 단어입니다." << endl;
            break;
        }
        // cout << "단어는 " << word <<"입니다." << endl;
    }
}

bool WordGame::compWord(string s) {
    int i = word.size();
    if(word.at(i-3) == s.at(0) && word.at(i-2) == s.at(1) && word.at(i-1) == s.at(2)) return true;
    else return false;
}

int main() {
    WordGame game;

    return 0;
}

