#include "widget.h"
#include <QApplication>
#include <QSpinBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSpinBox *spinBox = new QSpinBox();
    spinBox->resize(100, 30);
    spinBox->setRange(0, 10);
    spinBox->setSuffix("%");
    spinBox->setWrapping(true);
    spinBox->setSpecialValueText("Percent");
    spinBox->show();

    return a.exec();
}
