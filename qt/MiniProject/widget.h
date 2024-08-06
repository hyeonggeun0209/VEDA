#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include <vector>
#include <QString>

class QLabel;
class QPushButton;

class Widget : public QWidget
{
    Q_OBJECT

private:
    QLabel *label;
    QVector<QPushButton*> buttons;
    QString op1;
    double num1;
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

signals:
    void clicked();

public slots:
    void setnum();
    void op();
    void cal();
    void clear();
};
#endif // WIDGET_H
