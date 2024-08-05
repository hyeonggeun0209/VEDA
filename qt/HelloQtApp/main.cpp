#include "widget.h"
#include <QLabel>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QLabel hello("<font color=blue>" "Hello <i>Qt!</i> </font>", 0);
    hello.show();
    // Widget w;
    // w.show();
    return a.exec();
}
