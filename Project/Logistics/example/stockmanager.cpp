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
   file.open("stocklist.csv");
   if(!file.fail()) {
       while(!file.eof()) {
           vector<string> row = parseCSV(file, ',');
           if(row.size()) {
               int id = atoi(row[0].c_str());
               Stock* c = new Stock(id, row[1], atoi(row[2].c_str()));
               for(int i = 0; i < atoi(row[2].c_str()); i++) {
                    c->setP_id(atoi(row[i+3].c_str()));
               }
               StockList.insert( { id, c } );
           }
       }
   }
   file.close( );

    ifstream file2;
    file2.open("section.csv");
    if(!file2.fail()) {
       while(!file2.eof()) {
           vector<string> row = parseCSV(file2, ',');
           if(row.size()) {
                section.insert({ row[0], row[1]});
           }
       }
    }
   file2.close( );
}

StockManager::~StockManager()
{
    ofstream file;
    file.open("stocklist.csv");
    if(!file.fail()) {
        for (const auto& v : StockList) {
            Stock* c = v.second;
            file << c->id() << ", ";
            file << c->getSection() << ", ";
            file << c->getQuantity();
            for(int i = 0; i < c->getQuantity(); i++) {
                    file << ", " << c->getP_id().at(i);
            }
            file << endl;
        }
   }
   file.close( );
}
void StockManager::incrementStockQuantity(int id, const string& name) {
    for (auto& stock : StockList) {
        Stock* s = stock.second;
        vector<int> v = s->getP_id();
        if (s->getSection() == section.find(name)->second) {
            if(find(v.begin(), v.end(), id) == v.end()) {
                s->setP_id(id);
                s->incrementQuantity();
            } else { }
        }
    }
}

void StockManager::inputStock( )
{
    string section;
    int quantity = 0;
    cout << "section : "; cin.ignore(); getline(cin, section, '\n'); //cin >> section;

    int id = makeId( );
    Stock* c = new Stock(id, section, quantity);
    StockList.insert( { id, c } );
}

void StockManager::storeProduct(ProductManager& pm) {
    for(int i = 0; i < pm.getsize(); i++) {
        incrementStockQuantity(pm.search(i)->id(), pm.search(i)->getName());
    }
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

    string pid, section;
    int quantity;
    cout << "quantity : "; cin >> quantity;
    cout << "section : "; cin.ignore(); getline(cin, section, '\n'); //cin >> address;

    c->setQuantity(quantity);
    c->setSection(section);
    StockList[key] = c;
}

void StockManager::displayInfo()
{
    cout << endl << "  ID  |    Section Name    |    Quantity   |   p_id" << endl;
    for (const auto& v : StockList) {
         Stock* c = v.second;
         cout << setw(5) << setfill('0') << right << c->id() << " | " << left;
         cout << setw(12) << setfill(' ') << right << c->getSection() << "       | ";
         cout << setw(9) << setfill(' ') << right << c->getQuantity() << "     | ";
         cout << setw(3) << setfill(' ');
         for(int i=0; i < c->getP_id().size(); i++) {
            if(i > 4){
                break;
            }           
            cout << c->getP_id().at(i) << " ";
         }
         cout << endl;
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

void StockManager::find_id(ProductManager& pm) {
    int id;
    cout << "input product id : ";
    cin >> id;
    if(pm.getsize() == 0) {
        cout << "No Product!" << endl;
        return;
    }
    for (const auto& v : StockList) {
        Stock* c = v.second;
        cout << setw(12) << setfill(' ');
        cout << left << c->getSection() << "   |";
        cout << left;
        for(int i = 0; i < c->getQuantity(); i++) {
            if(c->getP_id().at(i) == id) {
                cout << "\033[33m";
                cout << "*";
                c->getP_id().at(i);
            } else {
                cout << "\033[0m";
                cout << "*";
            }
        }
        cout << endl;
    }
    cout << "Product : " << id << " " << pm.search(id)->getName() << " " << pm.search(id)->getPrice() << endl;;
}