#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTcpSocket>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , loginWidget(nullptr)
    , mainWindow(nullptr)
    , adminWindow(nullptr)
    , socket(nullptr)  // 소켓 초기화
{
    ui->setupUi(this);

    // UI 요소 연결
    idLineEdit = findChild<QLineEdit*>("lineEdit");
    pwLineEdit = findChild<QLineEdit*>("lineEdit_2");
    loginButton = findChild<QPushButton*>("pushButton");
    signInButton = findChild<QPushButton*>("pushButton_2");

    // 비밀번호 입력 시 '*'로 표시
    pwLineEdit->setEchoMode(QLineEdit::Password);

    // 버튼 클릭 시 해당 함수 호출
    connect(loginButton, &QPushButton::clicked, this, &Widget::onLoginClicked);
    connect(signInButton, &QPushButton::clicked, this, &Widget::onSignInClicked);
    connect(loginWidget, &login::backButtonClicked, this, &Widget::onLoginBackButtonClicked);
}

Widget::~Widget()
{
    delete ui;
    if (loginWidget)
        delete loginWidget;
    if (mainWindow)
        delete mainWindow;
    if (adminWindow)
        delete adminWindow;
    if (socket) {
        socket->close();
        delete socket;
    }
}

void Widget::onLoginClicked()
{
    QString id = idLineEdit->text();
    QString password = pwLineEdit->text();

    // 서버와의 연결
    if (!socket) {
        socket = new QTcpSocket(this);  // 소켓 초기화
    }

    // 서버 연결 시그널 처리
    connect(socket, &QTcpSocket::connected, this, [this, id, password]() {
        // 서버에 연결되면 로그인 요청을 보냄
        QJsonObject json;
        json["type"] = "LOGIN";
        json["userid"] = id;
        json["password"] = password;

        QJsonDocument doc(json);
        socket->write(doc.toJson());  // 서버로 로그인 정보 전송
        socket->flush();  // 데이터를 즉시 전송
    });

    // 서버 연결 실패 시 에러 처리
    connect(socket, &QTcpSocket::errorOccurred, this, [this]() {
        QMessageBox::critical(this, "서버 연결 오류", "서버와 연결할 수 없습니다.");
    });

    if (socket->state() == QAbstractSocket::UnconnectedState) {
        socket->connectToHost("127.0.0.1", 8080);  // 서버에 연결
    } else {
        // 이미 연결된 경우, 로그인 요청 바로 전송
        QJsonObject json;
        json["type"] = "LOGIN";
        json["userid"] = id;
        json["password"] = password;

        QJsonDocument doc(json);
        socket->write(doc.toJson());  // 서버로 로그인 정보 전송
        socket->flush();  // 데이터를 즉시 전송
    }

    // 서버로부터 응답을 받았을 때 처리
    connect(socket, &QTcpSocket::readyRead, this, &Widget::onLoginResponse);

}

// 서버로부터 로그인 응답을 처리하는 함수
void Widget::onLoginResponse()
{
    QByteArray data = socket->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject json = doc.object();

    if (json["type"].toString() == "LOGIN_RESPONSE") {
        bool success = json["success"].toBool();
        QString message = json["message"].toString();

        if (success) {
            // 로그인 성공 후 메인 화면으로 전환
            if (idLineEdit->text() == "admin") {
                QMessageBox::information(this, "로그인 성공", message);
                adminWindow = new AdminWindow(socket, nullptr);
                adminWindow->show();
            } else {
                QMessageBox::information(this, "로그인 성공", message);
                mainWindow = new MainWindow(nullptr);
                mainWindow->show();
            }

            this->hide();  // 현재 로그인 창 숨기기
        } else {
            QMessageBox::warning(this, "로그인 실패", message);  // 로그인 실패 경고 메시지
        }
    }
}

void Widget::onSignInClicked()
{
    if (!loginWidget){
        loginWidget = new login();
        connect(loginWidget, &login::backButtonClicked, this, &Widget::onLoginBackButtonClicked);
        connect(loginWidget, &login::registrationSuccessful, this, &Widget::onRegistrationSuccessful);
    }
    loginWidget->show();
    this->hide();
}

void Widget::onLoginBackButtonClicked()
{
    // 로그인 위젯 숨기기
    loginWidget->hide();

    // 메인 위젯(현재 클래스) 보이기
    this->show();
}

void Widget::onRegistrationSuccessful()
{
    loginWidget->hide();
    this->show();
}

// bool Widget::validateLogin(const QString &id, const QString &password)
// {
//     // TODO: 실제 데이터베이스나 서버와의 통신을 통한 로그인 검증 로직으로 대체
//     return (id == "user" && password == "password");
// }
