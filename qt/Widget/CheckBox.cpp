#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    // CheckBox widget
    label = new QLabel("0",this);
    label->setGeometry(20, 10, 70, 30);
    label->setAlignment(Qt::AlignVCenter | Qt::AlignRight);

    resize(120, 140);
    buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(false);
    connect(buttonGroup, SIGNAL(idClicked(int)), this, SLOT(selectButton(int)));
    // connect(buttonGroup, &QButtonGroup::idClicked, [&](int id){ label->setText(QString::number(id)); });
    for(int i = 0; i < 4; i++) {
        QString str = QString("CheckBox%1").arg(i+1);
        checkBox[i] = new QCheckBox(str, this);
        checkBox[i]->move(10, 40+20*i);
        buttonGroup->addButton(checkBox[i], i+1); // i값이 없으면 디폴트로 -1이 들어감
    }
}
