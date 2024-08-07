#include "widget.h"
#include <QDial>
#include <QCalendarWidget>
#include <QTextEdit>
#include <QTabWidget>
#define NO_OF_ROW 3

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    // QTabWidget widget
    QDial *dial = new QDial(this);
    QCalendarWidget *calendarWidget = new QCalendarWidget(this);
    QTextEdit *textEdit = new QTextEdit("Tab 3", this);

    QTabWidget *tabWidget = new QTabWidget(this);
    tabWidget->addTab(dial, "Tab &1");
    tabWidget->addTab(calendarWidget, "Tab &2");
    tabWidget->addTab(textEdit, "Tab &3");

    resize(tabWidget->sizeHint());

}
