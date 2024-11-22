#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

vector<string> parseCSV(istream &file, char delimiter);
map<string, string> open();

int main() {
    map<string, string> m =open();

    cout << m.find("banana")->second << endl;

    cout << m.find("milk")->second << endl;


}

map<string, string> open() {
    map<string, string> m;
    ifstream file;
   file.open("section.csv");
   if(!file.fail()) {
       while(!file.eof()) {
           vector<string> row = parseCSV(file, ',');
           if(row.size()) {
                m.insert({ row[0], row[1]});
           }
       }
   }
   file.close( );
   return m;
}

vector<string> parseCSV(istream &file, char delimiter)
{
    stringstream ss;
    vector<string> row;
    string t = " \n\r\t";

    while(!file.eof()) {
        char c = file.get();
        if (c==delimiter || c=='\r' || c=='\n') {
            if(file.peek()=='\n') file.get();
            string s = ss.str();
            s.erase(0, s.find_first_not_of(t));
            s.erase(s.find_last_not_of(t)+1);
            row.push_back(s);
            ss.str("");
            if (c!=delimiter) break;
        } else {
            ss << c;
        }
    }
    return row;
}