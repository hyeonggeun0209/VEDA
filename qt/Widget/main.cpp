#include "widget.h"
#include <QApplication>
#include <QSlider>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSlider *slider = new QSlider();
    slider->resize(300,200);
    slider->setOrientation(Qt::Horizontal);
    slider->setTickPosition(QSlider::TicksAbove);
    slider->setStyle(QStyleFactory::create("Fusion"));
    slider->show();

    return a.exec();
}