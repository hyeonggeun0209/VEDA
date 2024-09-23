#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>

#include "product.h"
#include "productmanager.h"

ProductManager::ProductManager()
{
   ifstream file;
   file.open("productlist.csv");
   if(!file.fail()) {
       while(!file.eof()) {
           vector<string> row = parseCSV(file, ',');
           if(row.size()) {
               int id = atoi(row[0].c_str());
               Product* c = new Product(id, row[1], row[2]);
               productList.insert( { id, c } );
           }
       }
   }
   file.close( );
}

ProductManager::~ProductManager()
{
   ofstream file;
   file.open("productlist.csv");
   if(!file.fail()) {
      for (const auto& v : productList) {
          Product* c = v.second;
          file << c->id() << ", " << c->getName() << ", ";
          file << c->getPrice() << endl;
      }
   }
   file.close( );
}

void ProductManager::inputProduct(const string& name="", const string& price="")
{   
    int id = makeId( );
    Product* c = new Product(id, name, price);
    productList.insert( { id, c } );
}

void ProductManager::receiveProduct(DockManager& dm) {
    int price;
    srand(time(NULL));
    for(int i = 0; i < dm.getDockSize(); i++) {
        for(int j = 0; j < dm.searchDock(i)->getItemQuantity(); j++) {
            price = ((rand() % 501) + 100) * 100;
            inputProduct(dm.searchDock(i)->getItemType(), to_string(price));
        }
    }
}

Product* ProductManager::search(int id)
{
    return productList[id];
}

void ProductManager::deleteProduct(int key)
{
    productList.erase(key);
}

void ProductManager::modifyProduct(int key)
{
    Product* c = search(key);
    cout << "  ID  |     Name     |     Price " << endl;
    cout << setw(5) << setfill('0') << right << c->id() << " | " << left;
    cout << setw(12) << setfill(' ') << c->getName() << " | ";
    cout << setw(12) << c->getPrice() << endl;

    string name, price;
    cout << "name : "; cin >> name;
    cout << "price : "; cin.ignore(); getline(cin, price, '\n'); //cin >> address;

    c->setName(name);
    c->setPrice(price);
    productList[key] = c;
}

void ProductManager::displayInfo()
{
    cout << endl << "  ID  |     Name     |     Price " << endl;
    for (const auto& v : productList) {
        Product* c = v.second;
        cout << setw(5) << setfill('0') << right << c->id() << " | " << left;
        cout << setw(12) << setfill(' ')  << c->getName() << " | ";
        cout << setw(12) << c->getPrice() << endl;
    }
}

void ProductManager::addProduct(Product* c)
{
    productList.insert( { c->id(), c } );
}

int ProductManager::makeId( )
{
    if(productList.size( ) == 0) {
        return 0;
    } else {
        auto elem = productList.end();
        int id = (--elem)->first;
        return ++id;
    }
}

vector<string> ProductManager::parseCSV(istream &file, char delimiter)
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

int ProductManager::getsize() {
    return productList.size();
}
