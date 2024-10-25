#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void onReadyRead();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;

    void connectToServer();
    void on_exitButton_clicked();  // 종료 버튼 클릭 시 호출될 슬롯
    void onSendMessage();
};
#endif // MAINWINDOW_H
