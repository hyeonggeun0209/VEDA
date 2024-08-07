// #include "widget.h"
// #include <QApplication>
// #include <QFrame>
// #include <QWidget>

// int main(int argc, char *argv[])
// {
//     QApplication a(argc, argv);

//     QWidget w;
//     QFrame *plainLine = new QFrame(&w);
//     plainLine->setGeometry(QRect(10, 0, 270, 160));
//     plainLine->setLineWidth(5);
//     plainLine->setFrameStyle(QFrame::VLine | QFrame::Plain);

//     QFrame *raiseLine = new QFrame(&w);
//     raiseLine->setGeometry(QRect(30, 0, 270, 160));
//     raiseLine->setLineWidth(5);
//     raiseLine->setFrameStyle(QFrame::VLine | QFrame::Raised);

//     QFrame *sunkenLine = new QFrame(&w);
//     sunkenLine->setGeometry(QRect(50, 0, 270, 160));
//     sunkenLine->setLineWidth(5);
//     sunkenLine->setFrameStyle(QFrame::VLine | QFrame::Sunken);

//     w.show();
//     return a.exec();
// }
