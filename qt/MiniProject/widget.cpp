#include <QLabel>
#include <QPushButton>
#include <QApplication>
#include <QString>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QGridLayout>
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
    // label->setGeometry(10, 5, 230, 40);
    label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    label->setFrameShape(QFrame::Box);
    label->setMaximumHeight(30);

    buttonGroup = new QButtonGroup();
    QGridLayout *gridLayout = new QGridLayout();
    for(int y = 0; y < WIDTH; ++y) {
        for(int x = 0; x < WIDTH; ++x) {
            int n = x + y * WIDTH;
            buttonGroup->addButton(new QPushButton(ButtonChar[n], this),n);
            gridLayout->addWidget(buttonGroup->button(n), n/WIDTH, n%WIDTH);
        }
    }

    setWindowTitle("Calculator");

    QVBoxLayout *vBoxLayout = new QVBoxLayout();
    vBoxLayout->setContentsMargins(6, 6, 6, 6);
    vBoxLayout->addWidget(label);
    vBoxLayout->addLayout(gridLayout);
    setLayout(vBoxLayout);

    connect(buttonGroup,SIGNAL(idClicked(int)),SLOT(click(int)));
}

void Widget::click(int id) {

    switch(id) {
    case 3:
    case 7:
    case 11:
    case 15: {
        num1 = label->text().toDouble();
        op1 = buttonGroup->button(id)->text();
        label->setText("0");
        break;
    }
    case 14: {
        Calculator c(num1, op1[0].toLatin1(), label->text().toDouble());
        label->setText(QString::number(c.doCalculate()));
        break;
    }
    case 13: {
        label->setText("0");
        break;
    }
    default: {
        if(label->text().toInt() == 0)
            label->setText(buttonGroup->button(id)->text());
        else
            label->setText(label->text()+buttonGroup->button(id)->text());
        }
        break;
    }
}

Widget::~Widget() {
}
