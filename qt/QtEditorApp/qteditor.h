#ifndef QTEDITOR_H
#define QTEDITOR_H

#include <QMainWindow>
class QAction;
class QMdiArea;
class QTextEdit;

class QtEditor : public QMainWindow
{
    Q_OBJECT

public:
    QtEditor(QWidget *parent = nullptr);
    ~QtEditor();

private:
    QMdiArea *mdiArea;
    template <typename T>
    QAction *makeAction(QString icon, QString text, T shortCut, QString toolTip, QObject *recv, const char* slot);
    template <typename T, typename Functor>
    QAction *makeAction(QString icon, QString text, T shortCut, QString toolTip, Functor lambda);

public slots:
    QTextEdit *newFile();
    void openFile();
    void saveFile();
    void saveAsFile();
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
};
#endif // QTEDITOR_H
