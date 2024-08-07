#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    //QGroupBox widget
    QStringList labels;
    labels << "&IP Address" << "&Mac Address" << "&Date";
    QLineEdit* lineEdit[3];
    QFormLayout *formLayout = new QFormLayout;
    for(int i = 0; i < 3; i++) {
        lineEdit[i] = new QLineEdit(this);
        if(i == 0) lineEdit[i]->setInputMask("000.000.000.000;_");
        else if(i == 1) lineEdit[i]->setInputMask("HH:HH:HH:HH:HH:HH;_");
        else lineEdit[i]->setInputMask("0000-00-00");
        formLayout->addRow(labels.at(i), lineEdit[i]);
    }

    QGroupBox *groupBox = new QGroupBox("&Widget Group", this);
    groupBox->move(5, 5);
    groupBox->setLayout(formLayout);

    resize(groupBox->sizeHint().width()+10, groupBox->sizeHint().height()+10);
}
