#include <QtCore>
#include <QtNetwork>

#include "addressdialog.h"
#include "association.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <utility>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    nameTemplate(QStringLiteral("Alice (clone number %1)"))
{
    ui->setupUi(this);
    updateUi();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//! [0]

const QString colorizer(QStringLiteral("<font color=\"%1\">%2</font><br>"));

void MainWindow::addErrorMessage(const QString &message)
{
    ui->clientMessages->insertHtml(colorizer.arg(QStringLiteral("Crimson"), message));
}

void MainWindow::addWarningMessage(const QString &message)
{
    ui->clientMessages->insertHtml(colorizer.arg(QStringLiteral("DarkOrange"), message));
}

void MainWindow::addInfoMessage(const QString &message)
{
    ui->clientMessages->insertHtml(colorizer.arg(QStringLiteral("DarkBlue"), message));
}

void MainWindow::addServerResponse(const QString &clientInfo, const QByteArray &datagram,
                                   const QByteArray &plainText)
{
    static const QString messageColor = QStringLiteral("DarkMagenta");
    static const QString formatter = QStringLiteral("<br>---------------"
                                                    "<br>%1 received a DTLS datagram:<br> %2"
                                                    "<br>As plain text:<br> %3");

    const QString html = formatter.arg(clientInfo, QString::fromUtf8(datagram.toHex(' ')),
                                       QString::fromUtf8(plainText));
    ui->serverMessages->insertHtml(colorizer.arg(messageColor, html));
}

//! [0]

void MainWindow::on_connectButton_clicked()
{
    if (lookupId != -1) {
        QHostInfo::abortHostLookup(lookupId);
        lookupId = -1;
        port = 0;
        updateUi();
        return;
    }

    AddressDialog dialog;
    if (dialog.exec() != QDialog::Accepted)
        return;

    const QString hostName = dialog.remoteName();
    if (hostName.isEmpty())
        return addWarningMessage(tr("Host name or address required to connect"));

    // port = dialog.remotePort();
    QHostAddress remoteAddress;
    remoteAddress.setAddress(hostName);
    // if (remoteAddress.setAddress(hostName))
    //     return startNewConnection(remoteAddress);

    addInfoMessage(tr("Looking up the host ..."));
    lookupId = QHostInfo::lookupHost(hostName, this, &MainWindow::lookupFinished);
    updateUi();

    // RTSP 연결 설정
    QTcpSocket *rtspSocket = new QTcpSocket(this);
    rtspSocket->connectToHost("192.168.0.10", 8554);
    if (!rtspSocket->waitForConnected()) {
        addErrorMessage(tr("RTSP 서버 연결 실패: %1").arg(rtspSocket->errorString()));
        return;
    }
    qDebug() << "RTSP 서버와 연결됨.";

    QByteArray setupRequest = "SETUP rtsp://192.168.0.10:8554/test/track1 RTSP/1.0\r\nCSeq: 3\r\nTransport: RTP/AVP;unicast;client_port=12345-12346\r\n\r\n";
    rtspSocket->write(setupRequest);
    qDebug() << rtspSocket->read(1024);

    // sleep(1);

    QByteArray playRequest = "PLAY rtsp://192.168.0.10:8554/test RTSP/1.0\r\nCSeq: 4\r\nSession: 12345678\r\n\r\n";
    rtspSocket->write(playRequest);
    rtspSocket->read(1024);

    // sleep(1);

    // rtspSocket->close();

    QUdpSocket *rtpSocket = new QUdpSocket(this);
    rtpSocket->connectToHost("192.168.0.10", 12345);
    // 기존의 연결 로직 시작
    // startNewConnection(remoteAddress);
}

void MainWindow::updateUi()
{
    ui->connectButton->setText(lookupId == -1 ? tr("Connect ...") : tr("Cancel lookup"));
    ui->shutdownButton->setEnabled(connections.size() != 0);
}

void MainWindow::lookupFinished(const QHostInfo &hostInfo)
{
    if (hostInfo.lookupId() != lookupId)
        return;

    lookupId = -1;
    updateUi();

    if (hostInfo.error() != QHostInfo::NoError) {
        addErrorMessage(hostInfo.errorString());
        return;
    }

    const QList<QHostAddress> foundAddresses = hostInfo.addresses();
    if (foundAddresses.empty()) {
        addWarningMessage(tr("Host not found"));
        return;
    }

    const auto remoteAddress = foundAddresses.at(0);
    addInfoMessage(tr("Connecting to: %1").arg(remoteAddress.toString()));
    startNewConnection(remoteAddress);
}

void MainWindow::startNewConnection(const QHostAddress &address)
{
    AssocPtr newConnection(new Association(address, 12345, nameTemplate.arg(nextId)));
    connect(newConnection.data(), &Association::errorMessage, this, &MainWindow::addErrorMessage);
    connect(newConnection.data(), &Association::warningMessage, this, &MainWindow::addWarningMessage);
    connect(newConnection.data(), &Association::infoMessage, this, &MainWindow::addInfoMessage);
    connect(newConnection.data(), &Association::serverResponse, this, &MainWindow::addServerResponse);
    connections.push_back(std::move(newConnection));
    connections.back()->startHandshake();
    updateUi();

    ++nextId;
}

void MainWindow::on_shutdownButton_clicked()
{
    connections.clear();
    updateUi();
}
