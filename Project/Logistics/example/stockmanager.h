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
        map<string, string> section;
    public:
        StockManager();
        ~StockManager();
        void storeProduct(ProductManager& pm);
        void incrementStockQuantity(int id, const string& name);
        void inputStock( );
        void deleteStock(int);
        void modifyStock(int);
        Stock* search(int);
        void find_id(ProductManager& pm);
        int makeId();
        void displayInfo();
        vector<string> parseCSV(istream&, char);
        void showStock();
};

#endif    // __STOCK_MANAGER_H__
