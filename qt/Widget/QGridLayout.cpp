#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{


    //QGridLayout class
    QGridLayout *gridLayout = new QGridLayout;
    QPushButton *pushButton[NO_OF_ROW* NO_OF_ROW];
    for(int y = 0; y < NO_OF_ROW; y++){
        for(int x = 0; x < NO_OF_ROW; x++) {
            int p = x+y*NO_OF_ROW;
            QString str = QString("Button%1").arg(p+1);
            pushButton[p] = new QPushButton(str, this);
            gridLayout->addWidget(pushButton[p],x,y);
        }
    }
    setLayout(gridLayout);
}
