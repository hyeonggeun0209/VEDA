#ifndef ASSOCIATION_H
#define ASSOCIATION_H

#include <QtNetwork>
#include <QtCore>

//! [0]
class Association : public QObject
{
    Q_OBJECT

public:
    Association(const QHostAddress &address, quint16 port,
                    const QString &connectionName);
    ~Association();
    void startHandshake();

signals:
    void errorMessage(const QString &message);
    void warningMessage(const QString &message);
    void infoMessage(const QString &message);
    void serverResponse(const QString &clientInfo, const QByteArray &datagraam,
                        const QByteArray &plainText);

private slots:
    void udpSocketConnected();
    void readyRead();
    void handshakeTimeout();
    void pskRequired(QSslPreSharedKeyAuthenticator *auth);
    void pingTimeout();

private:
    QString name;
    QUdpSocket socket;
    QDtls crypto;

    QTimer pingTimer;
    unsigned ping = 0;

    Q_DISABLE_COPY(Association)
};
//! [0]
#endif // ASSOCIATION_H
