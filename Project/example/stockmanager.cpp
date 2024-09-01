#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "stock.h"
#include "stockmanager.h"

StockManager::StockManager()
{
   ifstream file;
   file.open("stocklist.txt");
   if(!file.fail()) {
       while(!file.eof()) {
           vector<string> row = parseCSV(file, ',');
           if(row.size()) {
               int id = atoi(row[0].c_str());
               Stock* c = new Stock(id, atoi(row[1].c_str()), row[2]);
               StockList.insert( { id, c } );
           }
       }
   }
   file.close( );
}

StockManager::~StockManager()
{
   ofstream file;
   file.open("stocklist.txt");
   if(!file.fail()) {
      for (const auto& v : StockList) {
          Stock* c = v.second;
          file << c->id() << ", ";
          file << c->getQuantity() << ", ";
          file << c->getSection() << endl;
      }
   }
   file.close( );
}

void StockManager::inputStock( )
{
    string pid, quantity, section;
    cout << "product id : "; cin >> pid;
    cout << "quantity : "; cin >> quantity;
    cout << "section : "; cin.ignore(); getline(cin, section, '\n'); //cin >> section;

    int id = makeId( );
    Stock* c = new Stock(id, atoi(quantity.c_str()), section);
    StockList.insert( { id, c } );
}

Stock* StockManager::search(int id)
{
    return StockList[id];
}

void StockManager::deleteStock(int key)
{
    StockList.erase(key);
}

void StockManager::modifyStock(int key)
{
    Stock* c = search(key);
    cout << "  ID  |    Section Name   |   Quantity "<< endl;
    cout << setw(5) << setfill('0') << right << c->id() << " | " << left;
    cout << setw(12) << setfill(' ') << c->getQuantity() << " | ";
    cout << setw(12) << c->getSection() << endl;

    string pid, quantity, section;
    // cout << "product id : "; cin >> pid;
    cout << "quantity : "; cin >> quantity;
    cout << "section : "; cin.ignore(); getline(cin, section, '\n'); //cin >> address;

    c->setQuantity(quantity);
    c->setSection(section);
    StockList[key] = c;
}

void StockManager::displayInfo()
{
    cout << endl << "  ID  |     Section Name     |     Quantity" << endl;
    for (const auto& v : StockList) {
         Stock* c = v.second;
         cout << setw(5) << setfill('0') << right << c->id() << " | " << left;
         cout << setw(12) << setfill(' ') << c->getSection() << " | ";
         cout << setw(12) << c->getQuantity() << endl;
    }
}

int StockManager::makeId( )
{
    if(StockList.size( ) == 0) {
        return 0;
    } else {
        auto elem = StockList.end();
        int id = (--elem)->first;
        return ++id;
    }
}

vector<string> StockManager::parseCSV(istream &file, char delimiter)
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


bool StockManager::displayMenu()
{
    int ch, key;
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                 Stock Manager                 " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "  1. Display Stock List                     " << endl;
    cout << "  2. input Stock                            " << endl;
    cout << "  3. Delete Stock                           " << endl;
    cout << "  4. Modify Stock                           " << endl;
    cout << "  5. Quit Stock Manager                       " << endl;
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
            inputStock();
            break;
        case 3:
            displayInfo();
            cout << "   Choose Key : ";
            cin >> key;
            deleteStock(key);
            break;
        case 4:
            displayInfo();
            cout << "   Choose Key : ";
            cin >> key;
            modifyStock(key);
            break;
        case 5:
            return false;
    }
    return true;
}