/********************************************************************************
** Form generated from reading UI file 'chatwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATWINDOW_H
#define UI_CHATWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_ChatWindow
{
public:
    QTextBrowser *chatLog;
    QLineEdit *messageInput;
    QPushButton *sendButton;
    QPushButton *closeButton;

    void setupUi(QDialog *ChatWindow)
    {
        if (ChatWindow->objectName().isEmpty())
            ChatWindow->setObjectName("ChatWindow");
        ChatWindow->resize(448, 346);
        chatLog = new QTextBrowser(ChatWindow);
        chatLog->setObjectName("chatLog");
        chatLog->setGeometry(QRect(10, 10, 421, 271));
        messageInput = new QLineEdit(ChatWindow);
        messageInput->setObjectName("messageInput");
        messageInput->setGeometry(QRect(10, 290, 231, 31));
        sendButton = new QPushButton(ChatWindow);
        sendButton->setObjectName("sendButton");
        sendButton->setGeometry(QRect(350, 290, 81, 32));
        closeButton = new QPushButton(ChatWindow);
        closeButton->setObjectName("closeButton");
        closeButton->setGeometry(QRect(250, 290, 81, 32));

        retranslateUi(ChatWindow);

        QMetaObject::connectSlotsByName(ChatWindow);
    } // setupUi

    void retranslateUi(QDialog *ChatWindow)
    {
        ChatWindow->setWindowTitle(QCoreApplication::translate("ChatWindow", "Dialog", nullptr));
        sendButton->setText(QCoreApplication::translate("ChatWindow", "\353\251\224\354\213\234\354\247\200 \354\240\204\354\206\241", nullptr));
        closeButton->setText(QCoreApplication::translate("ChatWindow", "\354\242\205\353\243\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatWindow: public Ui_ChatWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATWINDOW_H
