#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    //RadioButton widget
    resize(140, 110);
    buttonGroup = new QButtonGroup(this);
    for(int i = 0; i < 4; i++) {
        QString str = QString("RadioButton%1").arg(i+1);
        radioButton[i] = new QRadioButton(str, this);
        radioButton[i]->move(10, 10+20*i);
        buttonGroup->addButton(radioButton[i]);
    }
}
