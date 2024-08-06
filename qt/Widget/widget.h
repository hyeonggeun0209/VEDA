#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QRadioButton;
class QButtonGroup;
class QCheckBox;
class QLabel;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    QRadioButton *radioButton[4];
    QButtonGroup *buttonGroup;
    QCheckBox *checkBox[4];
    QLabel *label;
public slots:
    void selectButton(int id);
};

#endif // WIDGET_H
