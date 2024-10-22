#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtSql>
#include <QMap>

class QLabel;
class QPushButton;

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);

private slots:
    void startServer();
    void stopServer();
    void clientConnect();
    void sendServerInfo();
    bool initDatabase();
    bool registerUser(const QString &name, const QString &age, const QString &email, const QString &userid, const QString &password);
    void processClientData(QTcpSocket *clientSocket);
    void sendMessageToClient(const QString& customerName, const QString& message);
    bool validateLogin(const QString &userid, const QString &password, QString &name);
    void sendCustomerInfo(QTcpSocket *clientSocket, const QString &customerName);
    void sendCustomerList(QTcpSocket *clientSocket);

private:
    QLabel *statusLabel;
    QPushButton *startButton;
    QPushButton *stopButton;
    QTcpServer *tcpServer;
    // QList<QTcpSocket*> clientSockets;
    void updateButtonStates();
    QString getLocalIPAddress();
    QSqlDatabase db;
    // 클라이언트 소켓을 userid와 매핑하여 관리
    QMap<QString, QTcpSocket*> clientSockets;
};

#endif // WIDGET_H
