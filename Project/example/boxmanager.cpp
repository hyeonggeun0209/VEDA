#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "box.h"
#include "boxmanager.h"

BoxManager::BoxManager()
{
   ifstream file;
   file.open("boxlist.txt");
   if(!file.fail()) {
       while(!file.eof()) {
           vector<string> row = parseCSV(file, ',');
           if(row.size()) {
               int id = atoi(row[0].c_str());
               Box* c = new Box(id, row[1], row[2], row[3]);
               boxList.insert( { id, c } );
           }
       }
   }
   file.close( );
}

BoxManager::~BoxManager()
{
   ofstream file;
   file.open("boxlist.txt");
   if(!file.fail()) {
      for (const auto& v : boxList) {
          Box* c = v.second;
          file << c->id() << ", " << c->getName() << ", ";
          file << c->getPhoneNumber() << ", ";
          file << c->getAddress() << endl;
      }
   }
   file.close( );
}

void BoxManager::inputBox( )
{
    string name, number, address;
    cout << "name : "; cin >> name;
    cout << "number : "; cin >> number;
    cout << "address : "; cin.ignore(); getline(cin, address, '\n'); //cin >> address;

    int id = makeId( );
    Box* c = new Box(id, name, number, address);
    boxList.insert( { id, c } );
}

Box* BoxManager::search(int id)
{
    return boxList[id];
}

void BoxManager::deleteBox(int key)
{
    boxList.erase(key);
}

void BoxManager::modifyBox(int key)
{
    Box* c = search(key);
    cout << "  ID  |     Name     | Phone Number |       Address" << endl;
    cout << setw(5) << setfill('0') << right << c->id() << " | " << left;
    cout << setw(12) << setfill(' ') << c->getName() << " | ";
    cout << setw(12) << c->getPhoneNumber() << " | ";
    cout << c->getAddress() << endl;

    string name, number, address;
    cout << "name : "; cin >> name;
    cout << "number : "; cin >> number;
    cout << "address : "; cin.ignore(); getline(cin, address, '\n'); //cin >> address;

    c->setName(name);
    c->setPhoneNumber(number);
    c->setAddress(address);
    boxList[key] = c;
}

void BoxManager::displayInfo()
{
    cout << endl << "  ID  |     Name     | Phone Number |       Address" << endl;
    for (const auto& v : boxList) {
         Box* c = v.second;
         cout << setw(5) << setfill('0') << right << c->id() << " | " << left;
         cout << setw(12) << setfill(' ') << c->getName() << " | ";
         cout << setw(12) << c->getPhoneNumber() << " | ";
         cout << c->getAddress() << endl;
    }
}

void BoxManager::addBox(Box* c)
{
    boxList.insert( { c->id(), c } );
}

int BoxManager::makeId( )
{
    if(boxList.size( ) == 0) {
        return 0;
    } else {
        auto elem = boxList.end();
        int id = (--elem)->first;
        return ++id;
    }
}

vector<string> BoxManager::parseCSV(istream &file, char delimiter)
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


bool BoxManager::displayMenu()
{
    int ch, key;
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "              Box Manager                 " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "  1. Display Box List                     " << endl;
    cout << "  2. input Box                            " << endl;
    cout << "  3. Delete Box                           " << endl;
    cout << "  4. Modify Box                           " << endl;
    cout << "  5. Quit this Program                       " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << " What do you wanna do? ";
    cin >> ch;
    switch(ch) {
        case 1: default:
            displayInfo();
            cin.ignore();
            getchar();
            break;
        case 2:
            inputBox();
            break;
        case 3:
            displayInfo();
            cout << "   Choose Key : ";
            cin >> key;
            deleteBox(key);
            break;
        case 4:
            displayInfo();
            cout << "   Choose Key : ";
            cin >> key;
            modifyBox(key);
            break;
        case 5:
            return false;
    }
    return true;
}