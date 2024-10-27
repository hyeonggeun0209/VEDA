/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *pushButton;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QLabel *ImageLabel;
    QLabel *label_3;
    QPushButton *pushButton_2;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(407, 427);
        pushButton = new QPushButton(Widget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(120, 370, 71, 31));
        label = new QLabel(Widget);
        label->setObjectName("label");
        label->setGeometry(QRect(120, 310, 58, 16));
        lineEdit = new QLineEdit(Widget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(170, 310, 113, 21));
        label_2 = new QLabel(Widget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(120, 340, 58, 16));
        lineEdit_2 = new QLineEdit(Widget);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(170, 340, 113, 21));
        ImageLabel = new QLabel(Widget);
        ImageLabel->setObjectName("ImageLabel");
        ImageLabel->setGeometry(QRect(60, 10, 291, 261));
        ImageLabel->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/fitness.png")));
        ImageLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        ImageLabel->setWordWrap(false);
        ImageLabel->setMargin(0);
        label_3 = new QLabel(Widget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(70, 280, 261, 16));
        label_3->setAlignment(Qt::AlignmentFlag::AlignCenter);
        pushButton_2 = new QPushButton(Widget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(200, 370, 81, 31));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        pushButton->setText(QCoreApplication::translate("Widget", "Login", nullptr));
        label->setText(QCoreApplication::translate("Widget", "ID :", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "PW :", nullptr));
        ImageLabel->setText(QString());
        label_3->setText(QCoreApplication::translate("Widget", "VEDA \355\227\254\354\212\244\354\274\200\354\226\264\354\227\220 \354\230\244\354\213\240 \352\262\203\354\235\204 \355\231\230\354\230\201\355\225\251\353\213\210\353\213\244!", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Widget", "Sign In", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
