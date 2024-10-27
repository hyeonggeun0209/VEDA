/********************************************************************************
** Form generated from reading UI file 'signin.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNIN_H
#define UI_SIGNIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_login
{
public:
    QLineEdit *emailEdit;
    QLabel *emailLabel;
    QLabel *id_label;
    QLineEdit *idEdit;
    QLabel *pwLabel_1;
    QLabel *pwLabel_2;
    QLineEdit *pwEdit_1;
    QLineEdit *pwEdit_2;
    QLabel *label_5;
    QPushButton *backButton;
    QPushButton *signInButton;
    QLineEdit *nameEdit;
    QLabel *nameLabel;
    QLabel *age_label;
    QLineEdit *ageEdit;

    void setupUi(QWidget *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName("login");
        login->resize(393, 362);
        emailEdit = new QLineEdit(login);
        emailEdit->setObjectName("emailEdit");
        emailEdit->setGeometry(QRect(140, 170, 113, 21));
        emailLabel = new QLabel(login);
        emailLabel->setObjectName("emailLabel");
        emailLabel->setGeometry(QRect(80, 170, 51, 16));
        id_label = new QLabel(login);
        id_label->setObjectName("id_label");
        id_label->setGeometry(QRect(80, 190, 51, 16));
        idEdit = new QLineEdit(login);
        idEdit->setObjectName("idEdit");
        idEdit->setGeometry(QRect(140, 190, 113, 21));
        pwLabel_1 = new QLabel(login);
        pwLabel_1->setObjectName("pwLabel_1");
        pwLabel_1->setGeometry(QRect(50, 210, 81, 20));
        pwLabel_2 = new QLabel(login);
        pwLabel_2->setObjectName("pwLabel_2");
        pwLabel_2->setGeometry(QRect(50, 230, 91, 20));
        pwEdit_1 = new QLineEdit(login);
        pwEdit_1->setObjectName("pwEdit_1");
        pwEdit_1->setGeometry(QRect(140, 210, 113, 21));
        pwEdit_2 = new QLineEdit(login);
        pwEdit_2->setObjectName("pwEdit_2");
        pwEdit_2->setGeometry(QRect(140, 230, 113, 21));
        label_5 = new QLabel(login);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(90, 30, 191, 61));
        QFont font;
        font.setFamilies({QString::fromUtf8("Nanum Gothic")});
        font.setPointSize(24);
        font.setBold(true);
        label_5->setFont(font);
        label_5->setAlignment(Qt::AlignmentFlag::AlignCenter);
        backButton = new QPushButton(login);
        backButton->setObjectName("backButton");
        backButton->setGeometry(QRect(0, 0, 61, 32));
        signInButton = new QPushButton(login);
        signInButton->setObjectName("signInButton");
        signInButton->setGeometry(QRect(150, 260, 100, 32));
        nameEdit = new QLineEdit(login);
        nameEdit->setObjectName("nameEdit");
        nameEdit->setGeometry(QRect(140, 130, 113, 21));
        nameLabel = new QLabel(login);
        nameLabel->setObjectName("nameLabel");
        nameLabel->setGeometry(QRect(80, 130, 51, 16));
        age_label = new QLabel(login);
        age_label->setObjectName("age_label");
        age_label->setGeometry(QRect(80, 150, 51, 16));
        ageEdit = new QLineEdit(login);
        ageEdit->setObjectName("ageEdit");
        ageEdit->setGeometry(QRect(140, 150, 113, 21));

        retranslateUi(login);

        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QWidget *login)
    {
        login->setWindowTitle(QCoreApplication::translate("login", "Form", nullptr));
        emailLabel->setText(QCoreApplication::translate("login", "E-mail :", nullptr));
        id_label->setText(QCoreApplication::translate("login", "\354\225\204\354\235\264\353\224\224 :", nullptr));
        pwLabel_1->setText(QCoreApplication::translate("login", "\355\214\250\354\212\244\354\233\214\353\223\234 \354\236\205\353\240\245 :", nullptr));
        pwLabel_2->setText(QCoreApplication::translate("login", "\355\214\250\354\212\244\354\233\214\353\223\234 \355\231\225\354\235\270 : ", nullptr));
        label_5->setText(QCoreApplication::translate("login", "\355\232\214\354\233\220\352\260\200\354\236\205", nullptr));
        backButton->setText(QCoreApplication::translate("login", "\353\222\244\353\241\234\352\260\200\352\270\260", nullptr));
        signInButton->setText(QCoreApplication::translate("login", "\355\232\214\354\233\220\352\260\200\354\236\205", nullptr));
        nameLabel->setText(QCoreApplication::translate("login", "\354\235\264\353\246\204 :", nullptr));
        age_label->setText(QCoreApplication::translate("login", "\353\202\230\354\235\264 :", nullptr));
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNIN_H
