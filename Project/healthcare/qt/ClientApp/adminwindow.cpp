#include "adminwindow.h"
#include "ui_adminwindow.h"
#include <QLabel>
#include <QApplication>
#include <QMessageBox>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

AdminWindow::AdminWindow(QTcpSocket *sharedSocket, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminWindow),
    chatWindow(nullptr),
    socket(sharedSocket)  // 기존 소켓 사용
{
    ui->setupUi(this);

    qDebug() << "Socket connection state:" << socket->state();
    qDebug() << "Socket is valid:" << socket->isValid();
    qDebug() << "Socket is open:" << socket->isOpen();

    setWindowTitle("관리자");

    connect(ui->customerList, &QListWidget::itemClicked, this, &AdminWindow::on_customerList_itemClicked);
    connect(ui->chatConnectButton, &QPushButton::clicked, this, &AdminWindow::on_chatConnectButton_clicked);
    connect(ui->exitButton, &QPushButton::clicked, this, &AdminWindow::on_exitButton_clicked);
    connect(socket, &QTcpSocket::readyRead, this, &AdminWindow::onReadyRead);

    // 선택된 고객 이름을 저장하기 위한 변수
    selectedCustomer = "";

    // 서버에 고객 목록 요청
    requestCustomerList();
}

AdminWindow::~AdminWindow()
{
    delete ui;

    // 채팅 창이 열려 있으면 삭제
    if (chatWindow) {
        delete chatWindow;
    }
}

// 서버에 고객 목록을 요청하는 함수
void AdminWindow::requestCustomerList()
{
    QJsonObject request;
    request["type"] = "REQUEST_CUSTOMER_LIST";
    QJsonDocument requestDoc(request);
    socket->write(requestDoc.toJson());
    socket->flush();
    qDebug() << "request called!";
}

// 고객 정보를 서버에 요청하는 함수
void AdminWindow::requestCustomerInfo(const QString& customerName)
{
    QJsonObject request;
    request["type"] = "REQUEST_CUSTOMER_INFO";
    request["name"] = customerName;
    QJsonDocument requestDoc(request);
    socket->write(requestDoc.toJson());
    socket->flush();


}

// 서버로부터 데이터를 수신했을 때 호출되는 슬롯
void AdminWindow::onReadyRead()
{
    qDebug() << "onReadyRead called!";
    qDebug() << "Bytes available:" << socket->bytesAvailable();

    QByteArray receivedData = socket->readAll();
    qDebug() << "Raw data received (hex):" << receivedData.toHex();
    qDebug() << "Raw data received (string):" << QString(receivedData);

    if (receivedData.isEmpty()) {
        qDebug() << "Received empty data!";
        return;
    }

    buffer += receivedData;
    qDebug() << "Current buffer content:" << buffer;

    while (!buffer.isEmpty()) {
        int endIndex = buffer.indexOf('\n');
        if (endIndex == -1) {
            qDebug() << "No complete message in buffer yet";
            break;
        }

        QByteArray messageData = buffer.left(endIndex);
        buffer.remove(0, endIndex + 1);

        qDebug() << "Processing message:" << messageData;

        QJsonParseError parseError;
        QJsonDocument doc = QJsonDocument::fromJson(messageData, &parseError);

        if (parseError.error != QJsonParseError::NoError) {
            qDebug() << "JSON parse error:" << parseError.errorString();
            continue;
        }

        QJsonObject json = doc.object();
        qDebug() << "Successfully parsed JSON:" << json;

        processServerResponse(json);
    }
}

void AdminWindow::processServerResponse(const QJsonObject& json)
{
    QString type = json["type"].toString();
    qDebug() << "[processServerResponse] Response type:" << type;

    if (type == "CUSTOMER_LIST") {
        QJsonArray customers = json["customers"].toArray();
        ui->customerList->clear();
        for (const QJsonValue &value : customers) {
            QString customerName = value.toObject()["name"].toString();
            qDebug() << "[processServerResponse] Adding customer to list:" << customerName;
            ui->customerList->addItem(customerName);
        }
    } else if (type == "CUSTOMER_INFO") {
        QString name = json["name"].toString();
        QString age = json["age"].toString();
        QString email = json["email"].toString();

        qDebug() << "[processServerResponse] Customer Info - Name:" << name << ", Age:" << age << ", Email:" << email;

        ui->chatHistory->clear();  // 기존 텍스트 삭제
        ui->chatHistory->append("Customer Information:");
        ui->chatHistory->append("Name: " + name);
        ui->chatHistory->append("Age: " + age);
        ui->chatHistory->append("Email: " + email);
    }
}



// 고객 이름을 클릭했을 때 고객 정보를 로드하는 함수
void AdminWindow::on_customerList_itemClicked(QListWidgetItem *item)
{
    QString customerName = item->text();
    selectedCustomer = customerName;  // 선택된 고객 이름 저장
    requestCustomerInfo(customerName);
}

// "채팅 접속" 버튼이 눌렸을 때 새로운 채팅 창을 띄움
void AdminWindow::on_chatConnectButton_clicked()
{
    if (selectedCustomer.isEmpty()) {
        QMessageBox::warning(this, "Error", "고객을 먼저 선택하세요!");  // 고객 선택 안된 경우 경고
        return;
    }

    // 채팅 창이 이미 열려 있으면 기존 창을 재사용
    if (chatWindow && chatWindow->isVisible()) {
        chatWindow->raise();  // 이미 열린 창을 최상단으로 올림
        chatWindow->activateWindow();  // 창을 활성화
        return;
    }

    // 새 채팅 창을 띄우고 고객과의 채팅 시작
    chatWindow = new ChatWindow(this, selectedCustomer);  // 고객 이름 전달
    chatWindow->show();
}

// 종료 버튼 클릭 시 호출되는 슬롯
void AdminWindow::on_exitButton_clicked()
{
    QApplication::quit();  // 프로그램 종료
}
