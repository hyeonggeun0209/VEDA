#ifndef __STOCK_MANAGER_H__
#define __STOCK_MANAGER_H__

#include <map>
#include <vector>
#include "stock.h"
#include "productmanager.h"
class ProductManager;
using namespace std;

class StockManager {
    private:
        map<int, Stock*> StockList;
    public:
        StockManager();
        ~StockManager();
        void storeProduct(ProductManager& pm);
        void incrementStockQuantity(int id, const string& name);
        void updateStock(const string& productType, int quantity);
        void inputStock( );
        void addStock(const string&);
        void deleteStock(int);
        void modifyStock(int);
        Stock* search(int);
        int makeId();
        void displayInfo();
        vector<string> parseCSV(istream&, char);
};

#endif    // __STOCK_MANAGER_H__
