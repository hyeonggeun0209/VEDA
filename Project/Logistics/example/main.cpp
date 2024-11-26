#include <iostream>
#include "center.h"
#include "stockmanager.h"
#include "productmanager.h"
#include "dockmanager.h"

int main()
{
    ProductManager pm;
    StockManager sm;
    DockManager dm;
    Center center(dm, pm, sm);
    center.run();
    return 0;
}
