#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include <vector>
#include <QString>

class QLabel;
class QPushButton;
class QButtonGroup;

class Widget : public QWidget
{
    Q_OBJECT

private:
    QLabel *label;
    QString op1;
    double num1;
    QButtonGroup *buttonGroup;
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

signals:
    void clicked();

public slots:
    void click(int id);
};
#endif // WIDGET_H
