#include "widget.h"
#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPushButton *pushButton = new QPushButton("Push&Button", 0);
    pushButton->setCheckable(true);
    QObject::connect(pushButton, &QPushButton::toggled, [&](bool flag){ qDebug() << "toggled"; if(!flag) a.quit();});
    pushButton->show();

    return a.exec();
}
