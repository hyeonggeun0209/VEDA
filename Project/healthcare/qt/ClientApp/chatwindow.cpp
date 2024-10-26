#include "chatwindow.h"
#include "ui_chatwindow.h"
#include <QJsonDocument>  // QJsonDocument 헤더 추가
#include <QJsonObject>    // QJsonObject 헤더 추가
#include <QByteArray>     // QByteArray 헤더 추가
#include <QDebug>


ChatWindow::ChatWindow(QWidget *parent, const QString& customerName)
    : QDialog(parent)
    , ui(new Ui::ChatWindow)
    , socket(nullptr)  // 소켓 초기화
    , customerName(customerName)  // 고객 이름 초기화
{
    ui->setupUi(this);

    // 윈도우 제목에 고객 이름 표시
    setWindowTitle("Chat with " + customerName);

    // 서버에 연결
    connectToServer();

    // 서버로부터 메시지를 받을 때 readyRead 시그널 연결
    connect(socket, &QTcpSocket::readyRead, this, &ChatWindow::onReadyRead);

    // 전송 버튼 클릭 시 메시지 보내기
    connect(ui->sendButton, &QPushButton::clicked, this, &ChatWindow::onSendMessage);

    // 종료 버튼 클릭 시 채팅 창만 닫기
    connect(ui->closeButton, &QPushButton::clicked, this, &ChatWindow::onCloseButtonClicked);
}

ChatWindow::~ChatWindow()
{
    delete ui;
    if (socket) {
        socket->close();
        delete socket;
    }
}

// 종료 버튼을 눌렀을 때 채팅 창을 닫음 (소켓은 유지)
void ChatWindow::onCloseButtonClicked()
{
    this->close();  // 채팅 창만 닫음
}

// 서버에 연결하는 함수
void ChatWindow::connectToServer()
{
    // 이미 연결되어 있으면 재연결하지 않음
    if (socket && socket->state() == QAbstractSocket::ConnectedState) {
        return;  // 이미 연결된 경우, 함수 종료
    }

    // 소켓 초기화 및 연결
    if (!socket) {
        socket = new QTcpSocket(this);
    }

    connect(socket, &QTcpSocket::connected, [this]() {
        ui->chatLog->append("서버에 연결되었습니다.");
        qDebug() << "Connected to server!";
    });

    connect(socket, &QTcpSocket::disconnected, [this]() {
        ui->chatLog->append("서버와의 연결이 끊어졌습니다.");
    });

    connect(socket, &QTcpSocket::errorOccurred, [this](QAbstractSocket::SocketError socketError) {
        ui->chatLog->append("연결 오류: " + socket->errorString());
    });

    // 서버로부터 데이터를 받을 때 처리 (readyRead 시그널)
    connect(socket, &QTcpSocket::readyRead, this, &ChatWindow::onReadyRead);

    socket->connectToHost("192.168.35.128", 8080);  // 서버 IP와 포트 설정
}

void ChatWindow::onReadyRead() {
    QByteArray data = socket->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);

    if (!doc.isObject()) {
        qDebug() << "Invalid JSON received";
        return;
    }

    QJsonObject json = doc.object();
    if (json.contains("type") && json["type"].toString() == "MESSAGE") {
        QString message = json["message"].toString();
        ui->chatLog->append("Server: " + message);
    } else {
        qDebug() << "Unexpected message format";
    }
}


void ChatWindow::onSendMessage()
{
    QString message = ui->messageInput->text();
    if (!message.isEmpty()) {
        QJsonObject json;
        json["type"] = "MESSAGE";
        json["message"] = message;
        json["targetUser"] = customerName;  // 메시지를 받을 타겟 고객 이름

        QJsonDocument doc(json);
        socket->write(doc.toJson());

        ui->chatLog->append("You: " + message);
        ui->messageInput->clear();
    }
}


