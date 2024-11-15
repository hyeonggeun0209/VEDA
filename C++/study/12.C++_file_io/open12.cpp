#include <iostream>
#include <time.h>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
#include <string.h>
#include <algorithm>
#define MAX 30000
using namespace std;

class HangMan{
    string filename;
public:
    HangMan(string filename){
        this->filename = filename;
    }
    void start();
};

void HangMan::start(){
    cout << "-----------------------------" << endl;
    cout << "지금부터 행맨게임을 시작합니다." << endl;
    cout << "-----------------------------" << endl;
    string textList[MAX];

    
    ifstream file;
    file.open(filename);
    string text;
    int i=0;
    
    while (getline(file,text)) {
     
        textList[i++] = text;
    }
    

    char ch[100];
    
    while (1) {
        int n= rand()%25413;
        string test_t = textList[n];
        int k2;
        int k1 = rand()%(test_t.length()-1);
        while (1) {
            k2 = rand()%(test_t.length()-1);
            if(k2 == k1) continue;
            else break;
        }
        
       
        strcpy(ch,test_t.c_str());
        ch[k1] = '-';
        ch[k2] = '-';
   
        cout << ch;
        int j=0;
        while(1){
            char ans;
            cout << ">>";
            cin >> ans;
            if(j==4){
                char yorn;
                cout << "5번 실패했습니다." << endl;
                cout << test_t << endl;
                cout << "Next? (Y/N)";
                cin >> yorn;
                j=0;
                if( yorn == 'y')
                    break;
                else if(yorn == 'n') exit(0);
            }
            
            
        
            if(ans == test_t[k1]){
                ch[k1] = test_t[k1];
                j++;
                cout << ch;
            }
            else if(ans == test_t[k2]){
                ch[k2] = test_t[k2];
                j++;
                cout << ch;
            }
            else{
                 j++;
                cout << ch;
            
            }
               
            if(test_t == ch){
                cout << endl;
                char yorn;
                j=0;
                cout << "Next? (Y/N)";
                cin >> yorn;
                if( yorn == 'y')
                    break;
                else if(yorn == 'n') exit(0);
            }   
        }
    }
}

int main(){
    srand((unsigned)time(0));
    HangMan a("/Users/jinurung/VEDA/C++/study/12.C++_file_io/words.txt");
    a.start();
    
   return  0;
}