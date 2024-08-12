#include "widget.h"
#include <QDial>
#include <QSplitter>
#include <QLabel>
#include <QPushButton>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    // QSplitter widget
    QLabel *label = new QLabel("&Value", this);
    QPushButton *button = new QPushButton(this);
    QDial *dial1 = new QDial(this);
    QDial *dial2 = new QDial(this);
    label->setBuddy(dial2); // focus를 넘긴다 alt v 누르면
    dial1->setWrapping(true);
    dial2->setWrapping(true);


    QSplitter *splitter = new QSplitter(this);
    splitter->addWidget(label);
    splitter->addWidget(dial1);
    splitter->addWidget(dial2);
    splitter->addWidget(button);

    resize(splitter->sizeHint());

}
