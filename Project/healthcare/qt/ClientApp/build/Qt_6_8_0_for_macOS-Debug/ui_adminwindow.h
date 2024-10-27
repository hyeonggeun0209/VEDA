/********************************************************************************
** Form generated from reading UI file 'adminwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMINWINDOW_H
#define UI_ADMINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AdminWindow
{
public:
    QWidget *centralwidget;
    QListWidget *customerList;
    QTextBrowser *chatHistory;
    QPushButton *chatConnectButton;
    QPushButton *exitButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *AdminWindow)
    {
        if (AdminWindow->objectName().isEmpty())
            AdminWindow->setObjectName("AdminWindow");
        AdminWindow->resize(800, 600);
        centralwidget = new QWidget(AdminWindow);
        centralwidget->setObjectName("centralwidget");
        customerList = new QListWidget(centralwidget);
        customerList->setObjectName("customerList");
        customerList->setGeometry(QRect(20, 10, 341, 471));
        customerList->setStyleSheet(QString::fromUtf8("font: 20pt \"Academy Engraved LET\";\n"
"font: 20pt \"Nanum Gothic\";"));
        chatHistory = new QTextBrowser(centralwidget);
        chatHistory->setObjectName("chatHistory");
        chatHistory->setGeometry(QRect(410, 10, 351, 471));
        chatConnectButton = new QPushButton(centralwidget);
        chatConnectButton->setObjectName("chatConnectButton");
        chatConnectButton->setGeometry(QRect(140, 500, 100, 32));
        exitButton = new QPushButton(centralwidget);
        exitButton->setObjectName("exitButton");
        exitButton->setGeometry(QRect(20, 500, 100, 32));
        AdminWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(AdminWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 24));
        AdminWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(AdminWindow);
        statusbar->setObjectName("statusbar");
        AdminWindow->setStatusBar(statusbar);
        QWidget::setTabOrder(chatHistory, customerList);

        retranslateUi(AdminWindow);

        QMetaObject::connectSlotsByName(AdminWindow);
    } // setupUi

    void retranslateUi(QMainWindow *AdminWindow)
    {
        AdminWindow->setWindowTitle(QCoreApplication::translate("AdminWindow", "MainWindow", nullptr));
        chatConnectButton->setText(QCoreApplication::translate("AdminWindow", "\354\261\204\355\214\205 \354\240\221\354\206\215", nullptr));
        exitButton->setText(QCoreApplication::translate("AdminWindow", "\354\242\205\353\243\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AdminWindow: public Ui_AdminWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMINWINDOW_H
