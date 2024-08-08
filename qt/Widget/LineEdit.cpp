#include "widget.h"
#include <QApplication>
#include <QLineEdit>
#include <QCompleter>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // QLineEdit widget
    QLineEdit *lineEdit = new QLineEdit();
    lineEdit->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    lineEdit->setInputMask("000.000.000.000;_");
    lineEdit->setPlaceholderText("input the number");
    lineEdit->show();

    //QCompleter class
    QStringList wordList;
    wordList << "alpha" << "omega" << "omicron" << "zeta";

    QLineEdit *lineEdit = new QLineEdit();

    QCompleter *completer = new QCompleter(wordList, 0);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    lineEdit->setCompleter(completer);
    lineEdit->show();

    return a.exec();
}
