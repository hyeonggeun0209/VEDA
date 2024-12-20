#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSharedPointer>
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}

class QHostAddress;
class QHostInfo;
QT_END_NAMESPACE

class Association;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void addErrorMessage(const QString &message);
    void addWarningMessage(const QString &message);
    void addInfoMessage(const QString &message);
    void addServerResponse(const QString &clientInfo, const QByteArray &datagram,
                           const QByteArray &plainText);

    void on_connectButton_clicked();
    void on_shutdownButton_clicked();

    void lookupFinished(const QHostInfo &hostInfo);

private:
    void updateUi();
    void startNewConnection(const QHostAddress &address);

    Ui::MainWindow *ui = nullptr;

    using AssocPtr = QSharedPointer<Association>;
    QList<AssocPtr> connections;

    QString nameTemplate;
    unsigned nextId = 0;

    quint16 port = 0;
    int lookupId = -1;
};

#endif // MAINWINDOW_H
