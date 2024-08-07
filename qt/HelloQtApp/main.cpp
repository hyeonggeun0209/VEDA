#include "widget.h"
#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w;
    QObject::connect(&w, SIGNAL(clicked()), &a, SLOT(quit()));
    w.show();

    // using QLabel
    // QLabel hello("<font color=blue>" "Hello <i>Qt!</i> </font>", &w);
    // hello.resize(75, 35);


    // using QPushButton
    // QPushButton quit("Quit", &w);
    // quit.move(10, 40); quit.resize(75, 35);
    // QObject::connect(&quit, SIGNAL(clicked()), &a, SLOT(quit()));

    // using lambda function
    // QObject::connect(&quit, &QPushButton::clicked, &hello, [&](){ hello.setText("<b>HI</b>");});
    // w.show();


    return a.exec();
}
