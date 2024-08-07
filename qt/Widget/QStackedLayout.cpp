#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{


    // QStackedLayout class
    QDial *dial = new QDial(this);
    dial->setRange(0, 2);

    QLabel *label = new QLabel("Stack 1", this);
    QCalendarWidget *calendarWidget = new QCalendarWidget(this);
    QTextEdit *textEdit = new QTextEdit("Stack 3", this);

    QStackedLayout *stackedLayout = new QStackedLayout(); // Layout은 this를 쓰지 않는 것을 권장
    stackedLayout->addWidget(label);
    stackedLayout->addWidget(calendarWidget);
    stackedLayout->addWidget(textEdit);

    connect(dial, &QDial::valueChanged, stackedLayout, &QStackedLayout::setCurrentIndex);
    QHBoxLayout *hBoxLayout = new QHBoxLayout();
    hBoxLayout->addWidget(dial);
    hBoxLayout->addLayout(stackedLayout);
    setLayout(hBoxLayout);

}
