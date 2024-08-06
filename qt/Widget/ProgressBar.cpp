// #include "widget.h"
// #include <QProgressBar>
// #include <QApplication>
// #include <QTimer>

// int main(int argc, char *argv[])
// {
//     QApplication a(argc, argv);

//     QProgressBar *pb = new QProgressBar();
//     pb->setOrientation(Qt::Vertical);
//     pb->show();

//     QTimer timer;
//     int n = 0;
//     QObject::connect(&timer, &QTimer::timeout, [&]{ pb->setValue(++n%101);});

//     timer.start(120);

//     return a.exec();
// }
