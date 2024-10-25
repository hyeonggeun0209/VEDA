#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QJsonDocument>  // QJsonDocument 헤더 추가
#include <QJsonObject>    // QJsonObject 헤더 추가
#include <QByteArray>     // QByteArray 헤더 추가
#include <QApplication>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , socket(nullptr)
{
    ui->setupUi(this);

    setWindowTitle("VEDA healthcare");

    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::onReadyRead);

    connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::on_exitButton_clicked);

    // 전송 버튼 클릭 시 메시지 전송
    connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::onSendMessage);

}

MainWindow::~MainWindow()
{
    delete ui;
    if (socket) {
        socket->close();
        delete socket;
    }
}

void MainWindow::on_pushButton_clicked()
{
    if (socket && socket->state() == QAbstractSocket::ConnectedState) {
        socket->disconnectFromHost();
        ui->pushButton->setText("채팅 접속");
        ui->listWidget->addItem("서버와의 연결이 끊어졌습니다.");
    } else {
        connectToServer();
    }
}

// 전송 버튼을 클릭했을 때 서버로 메시지를 전송
void MainWindow::onSendMessage()
{
    QString message = ui->messageInput->text();  // 메시지 입력 필드에서 텍스트 가져오기
    if (!message.isEmpty() && socket) {
        QJsonObject json;
        json["type"] = "MESSAGE";
        json["message"] = message;
        json["targetUser"] = "admin";  // 메시지를 관리자에게 전송

        QJsonDocument doc(json);
        socket->write(doc.toJson());

        ui->listWidget->addItem("You: " + message);
        ui->messageInput->clear();  // 입력 필드를 비움
    }
    qDebug() << "Message send client";
}

void MainWindow::connectToServer()
{
    if (!socket) {
        socket = new QTcpSocket(this);  // 소켓이 초기화되지 않았으면 새로 생성
    }

    connect(socket, &QTcpSocket::connected, [this]() {
        ui->listWidget->addItem("서버에 연결되었습니다.");
        ui->pushButton->setText("연결 끊기");
    });

    connect(socket, &QTcpSocket::disconnected, [this]() {
        ui->listWidget->addItem("서버와의 연결이 끊어졌습니다.");
        ui->pushButton->setText("채팅 접속");
    });

    connect(socket, &QTcpSocket::errorOccurred, [this](QAbstractSocket::SocketError socketError) {
        ui->listWidget->addItem("연결 오류: " + socket->errorString());
    });

    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::onReadyRead);

    socket->connectToHost("127.0.0.1", 8080);  // localhost의 8080 포트로 연결
}


// 서버로부터 메시지 수신
void MainWindow::onReadyRead()
{
    QByteArray data = socket->readAll();  // 데이터를 읽어옴
    QJsonDocument doc = QJsonDocument::fromJson(data);  // JSON 형식으로 변환
    QJsonObject json = doc.object();

    qDebug() << "Message received from server:" << doc.toJson();  // 서버에서 받은 메시지 출력

    if (json["type"].toString() == "MESSAGE") {
        QString message = json["message"].toString();
        ui->listWidget->addItem("Received: " + message);  // 받은 메시지를 리스트 위젯에 추가
    }
}



// 종료 버튼 클릭 시 호출되는 슬롯
void MainWindow::on_exitButton_clicked()
{
    QApplication::quit();  // 프로그램 종료
}
