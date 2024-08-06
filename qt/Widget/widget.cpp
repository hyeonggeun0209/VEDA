#include "widget.h"

#include <QRadioButton>
#include <QCheckBox>
#include <QButtonGroup>
#include <QLabel>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    // RadioButton widget
    // resize(140, 110);
    // buttonGroup = new QButtonGroup(this);
    // for(int i = 0; i < 4; i++) {
    //     QString str = QString("RadioButton%1").arg(i+1);
    //     radioButton[i] = new QRadioButton(str, this);
    //     radioButton[i]->move(10, 10+20*i);
    //     buttonGroup->addButton(radioButton[i]);
    // }


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

void Widget::selectButton(int id) {
    QButtonGroup *buttonGroup = (QButtonGroup*)sender();
    QCheckBox *button = (QCheckBox*)buttonGroup->button(id);
    qDebug("CheckBox%d is selected(%s)", id, (button->isChecked())?"On":"Off");
    label->setText(QString::number(id));
}

Widget::~Widget() {}
