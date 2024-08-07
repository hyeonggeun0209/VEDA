#include "widget.h"
#include <QPushButton>
#include <QApplication>
#include <QLabel>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QPushButton *quit = new QPushButton("Quit", this);
    quit->resize(75, 35);

    connect(quit, SIGNAL(clicked()), this, SLOT(slotQuit()));


}

void Widget::slotQuit() {
    qDebug("slotQuit");
    // qApp->quit();
    emit clicked();

}

Widget::~Widget() {}
