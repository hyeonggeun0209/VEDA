#ifndef QTEDITOR_H
#define QTEDITOR_H

#include <QMainWindow>
#include <QHash>
class QAction;
class QMdiArea;
class QTextEdit;
class QFontComboBox;
class QDoubleSpinBox;

class QtEditor : public QMainWindow
{
    Q_OBJECT

public:
    QtEditor(QWidget *parent = nullptr);
    ~QtEditor();

private:
    QMdiArea *mdiArea;
    QHash<QAction*, QWidget*> windowHash;
    QMenu *windowMenu;
    QFontComboBox *fontComboBox;
    QDoubleSpinBox *sizeSpinBox;
    template <typename T>
    QAction *makeAction(QString icon, QString text, T shortCut, QString toolTip, QObject *recv, const char* slot);
    template <typename T, typename Functor>
    QAction *makeAction(QString icon, QString text, T shortCut, QString toolTip, Functor lambda);

public slots:
    QTextEdit *newFile();
    void selectWindow();
    void openFile();
    void saveFile();
    void saveAsFile();
    void print();
    void undo();
    void redo();
    void copy();
    void cut();
    void paste();
    void zoomIn();
    void zoomOut();
    void about();
    void setColor();
    void setFont();
    void alignLeft();
    void alignCenter();
    void alignRight();
    void alignJustify();
    void setTextFont(QFont font);
    void setTextSize(qreal size);
};
#endif // QTEDITOR_H
