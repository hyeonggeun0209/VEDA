#include <QLabel>
#include <QPushButton>
#include <QApplication>
#include <QString>
#include "widget.h"
#include "calculator.h"
#define WIDTH 4

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    const char ButtonChar[16][2] = {
        "7", "8", "9", "/",
        "4", "5", "6", "x",
        "1", "2", "3", "-",
        "0", "C", "=", "+",
    };

    label =  new QLabel("0", this);
    label->setGeometry(10, 5, 230, 40);
    label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    // QPushButton *buttons[16];
    for(int y = 0; y < WIDTH; y++) {
        for(int x = 0; x < WIDTH; x++) {
            buttons.append(new QPushButton(ButtonChar[x+y*WIDTH], this));
            buttons.at(x+y*WIDTH)->setGeometry(5+60*x, 50+60*y, 55, 55);
        }
    }

    connect(buttons[0], SIGNAL(clicked()), this, SLOT(setnum()));
    connect(buttons[1], SIGNAL(clicked()), this, SLOT(setnum()));
    connect(buttons[2], SIGNAL(clicked()), this, SLOT(setnum()));
    connect(buttons[4], SIGNAL(clicked()), this, SLOT(setnum()));
    connect(buttons[5], SIGNAL(clicked()), this, SLOT(setnum()));
    connect(buttons[6], SIGNAL(clicked()), this, SLOT(setnum()));
    connect(buttons[8], SIGNAL(clicked()), this, SLOT(setnum()));
    connect(buttons[9], SIGNAL(clicked()), this, SLOT(setnum()));
    connect(buttons[10], SIGNAL(clicked()), this, SLOT(setnum()));
    connect(buttons[12], SIGNAL(clicked()), this, SLOT(setnum()));

    connect(buttons[3], SIGNAL(clicked()), this, SLOT(op()));
    connect(buttons[7], SIGNAL(clicked()), this, SLOT(op()));
    connect(buttons[11], SIGNAL(clicked()), this, SLOT(op()));
    connect(buttons[15], SIGNAL(clicked()), this, SLOT(op()));

    connect(buttons[14], SIGNAL(clicked()), this, SLOT(cal()));
    connect(buttons[13], SIGNAL(clicked()), this, SLOT(clear()));

}

void Widget::setnum() {

    QPushButton *button = (QPushButton*)(sender());
    if(label->text().toInt() == 0)
        label->setText(button->text());
    else
        label->setText(label->text()+button->text());


}

void Widget::op() {
    QPushButton *button = (QPushButton*)(sender());
    num1 = label->text().toDouble();
    op1 = button->text();
    label->setText("0");
}

void Widget::cal() {
    Calculator c(num1, op1[0].toLatin1(), label->text().toDouble());
    label->setText(QString::number(c.doCalculate()));
}

void Widget::clear() {
    label->setText("0");
}

Widget::~Widget() {
    delete label;
    buttons.clear();
}
