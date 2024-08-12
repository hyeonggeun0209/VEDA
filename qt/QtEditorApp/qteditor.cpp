#include "qteditor.h"
#include <QTextEdit>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QApplication>
#include <QToolBar>
#include <QFontComboBox>
#include <QSpinBox>
#include <QStatusBar>
#include <QLabel>
#include <QColorDialog>
#include <QDockWidget>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QFontDialog>
#include <QPrinter>
#include <QPrintDialog>


QtEditor::QtEditor(QWidget *parent)
    : QMainWindow(parent)
{
    //QMdiArea widget
    mdiArea = new QMdiArea(this);
    setCentralWidget(mdiArea);

    // QTextEdit *textedit = new QTextEdit(this);

    //QMenubar class
    QMenuBar *menubar = new QMenuBar(this);
    setMenuBar(menubar);


    //QAction class
    QAction *newAct = makeAction(":/images/new.png", tr("&New"), QKeySequence::New, tr("Make new file"), [this](){ newFile();});
    QAction *quitAct = makeAction(":/images/quit.png", tr("&Quit"), QKeySequence::Quit, tr("Quit this program"), [](){ qApp->quit();});
    QAction *openAct = makeAction(":/images/open.png", tr("&Open"), QKeySequence::Open, tr("Open file"), this, SLOT(openFile()));
    QAction *saveAct = makeAction(":/images/save.png", tr("&Save"), QKeySequence::Save, tr("Save file"), [this](){ saveFile();});
    QAction *saveAsAct = makeAction(":/images/saveAs.png", tr("&Save As..."), QKeySequence::SaveAs, tr("Save as file"), [this](){ saveAsFile();});
    QAction *undoAct = makeAction(":/images/undo.png", tr("&Undo"), QKeySequence::Undo, tr("Undo"), this, SLOT(undo()));
    QAction *redoAct = makeAction(":/images/redo.png", tr("&Redo"), QKeySequence::Redo, tr("redo"), this, SLOT(redo()));
    QAction *copyAct = makeAction(":/images/copy.png", tr("&Copy"), QKeySequence::Copy, tr("Copy"), this, SLOT(copy()));
    QAction *cutAct = makeAction(":/images/cut.png", tr("&Cut"), QKeySequence::Cut,  tr("Cut"), this, SLOT(cut()));
    QAction *pasteAct = makeAction(":/images/paste.png", tr("&Paste"), QKeySequence::Paste,  tr("Paste"), this, SLOT(paste()));
    QAction *zoomInAct = makeAction(":/images/zoomIn.png", tr("&ZoomIn"), QKeySequence::ZoomIn,  tr("ZoomIn"), this, SLOT(zoomIn()));
    QAction *zoomOutAct = makeAction(":/images/zoomOut.png", tr("&ZoomOut"), QKeySequence::ZoomOut,  tr("ZoomOut"), this, SLOT(zoomOut()));
    QAction *aboutAct = makeAction(":/images/about.png", tr("&About"), tr(""), tr("About"), this, SLOT(about()));
    QAction *aboutQtAct = makeAction(":/images/qt.png", tr("&AboutQt"), tr(""), tr("AboutQt"), qApp, SLOT(aboutQt()));
    QAction *colorAct = makeAction(":/images/color.png", tr("&Color"), tr(""), tr("Color"), this, SLOT(setColor()));
    QAction *fontAct = makeAction(":/images/font.png", tr("&Font"), tr(""), tr("Font"), this, SLOT(setFont()));
    QAction *printAct = makeAction(":/images/print.png", tr("&Print"), tr(""), tr("Print"), this, SLOT(print()));


    //QMenu class
    QMenu *fileMenu = menubar->addMenu("&File");
    QMenu *editMenu = menubar->addMenu("&Edit");
    QMenu *helpMenu = menubar->addMenu("&Help");
    fileMenu->addAction(newAct);
    fileMenu->addAction(quitAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addAction(printAct);

    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addSeparator();
    editMenu->addAction(copyAct);
    editMenu->addAction(cutAct);
    editMenu->addAction(pasteAct);
    editMenu->addSeparator();
    editMenu->addAction(zoomInAct);
    editMenu->addAction(zoomOutAct);

    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    // QStatusBar class
    QStatusBar *statusbar = statusBar();
    QLabel *statusLabel = new QLabel(tr("Qt Editor"), statusbar);
    statusLabel->setObjectName("StatusLabel");
    statusbar->addPermanentWidget(statusLabel);
    statusbar->showMessage("started", 1500);


    // QTextEdit Alignment
    QMenu *formatMenu = menubar->addMenu("&Format");
    QMenu *alignMenu = new QMenu("&Align", this);
    formatMenu->addMenu(alignMenu);
    formatMenu->addAction(fontAct);
    formatMenu->addAction(colorAct);
    QAction *leftAct = makeAction(":/images/left.png", tr("&Left"), "Ctrl+1", tr("Align left"), this, SLOT(alignLeft()));
    QAction *centerAct = makeAction(":/images/center.png", tr("&Center"), "Ctrl+2", tr("Align center"), this, SLOT(alignCenter()));
    QAction *rightAct = makeAction(":/images/right.png", tr("&Right"), "Ctrl+3", tr("Align right"), this, SLOT(alignRight()));
    QAction *justifyAct = makeAction(":/images/justify.png", tr("&Justify"), "Ctrl+4", tr("Align justify"), this, SLOT(alignJustify()));
    alignMenu->addAction(leftAct);
    alignMenu->addAction(centerAct);
    alignMenu->addAction(rightAct);
    alignMenu->addAction(justifyAct);


    //QToolBar class
    QToolBar *fileToolBar = addToolBar("&File");
    fileToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);
    fileToolBar->addAction(saveAsAct);

    fileToolBar->addSeparator();
    fileToolBar->addAction(printAct);

    fileToolBar->addSeparator();
    fileToolBar->addAction(quitAct);
    fileToolBar->addAction(undoAct);
    fileToolBar->addAction(redoAct);

    fileToolBar->addSeparator();
    fileToolBar->addAction(copyAct);
    fileToolBar->addAction(cutAct);
    fileToolBar->addAction(pasteAct);

    fileToolBar->addSeparator();
    fileToolBar->addAction(zoomInAct);
    fileToolBar->addAction(zoomOutAct);

    QAction *tileAct = makeAction(":/images/tile.png", tr("&Tile"), "Ctrl+Shift+T", \
                                  tr("tile"), mdiArea, SLOT(tileSubWindows( )));
    QAction *cascateAct = makeAction(":/images/cascade.png", tr("&Cascade"), "Ctrl+Shift+C", \
                                     tr("cascade"), mdiArea, SLOT(cascadeSubWindows( )));
    QAction *previousAct = makeAction(":/images/previous.png", tr("&Previous"), QKeySequence::PreviousChild, \
                                      tr("previous"), mdiArea, SLOT(activatePreviousSubWindow( )));
    QAction *nextAct = makeAction(":/images/next.png", tr("&Next"), QKeySequence::NextChild, \
                                  tr("next"), mdiArea, SLOT(activateNextSubWindow( )));

    windowMenu = menubar->addMenu("&Window");
    windowMenu->addAction(tileAct);
    windowMenu->addAction(cascateAct);
    windowMenu->addSeparator( );
    windowMenu->addAction(previousAct);
    windowMenu->addAction(nextAct);


    QMenu *toolbarMenu = windowMenu->addMenu("&Toolbar");
    toolbarMenu->addAction(fileToolBar->toggleViewAction());

    fontComboBox = new QFontComboBox(this);
    connect(fontComboBox, SIGNAL(currentFontChanged(QFont)), SLOT(setTextFont(QFont)));
    sizeSpinBox = new QDoubleSpinBox(this);
    connect(sizeSpinBox, SIGNAL(valueChanged(double)), SLOT(setTextSize(qreal)));
    addToolBarBreak(); // 다음 툴바는 아랫줄로 위치


    QToolBar *formatToolbar = addToolBar("&Format");
    formatToolbar->addAction(fontAct);
    formatToolbar->addAction(colorAct);
    formatToolbar->addWidget(fontComboBox);
    formatToolbar->addWidget(sizeSpinBox);
    formatToolbar->addSeparator();
    formatToolbar->addAction(leftAct);
    formatToolbar->addAction(centerAct);
    formatToolbar->addAction(rightAct);
    formatToolbar->addAction(justifyAct);

    formatToolbar->addSeparator( );
    formatToolbar->addAction(tileAct);
    formatToolbar->addAction(cascateAct);
    formatToolbar->addSeparator( );
    formatToolbar->addAction(previousAct);
    formatToolbar->addAction(nextAct);


    //QDockWidget class
    QWidget *w = new QWidget(this);
    QLabel *label = new QLabel("Dock Widget", w);
    QDockWidget *dock = new QDockWidget("Dock Widget", this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    dock->setWidget(w);
    toolbarMenu->addAction(dock->toggleViewAction());

#if 0
    QTextEdit *textedit = new QTextEdit(this);
    mdiArea->addSubWindow(textedit);
#else
    QTextEdit *textedit = newFile();
#endif

}

template<typename T, typename Functor>
QAction *QtEditor::makeAction(QString icon, QString text, T shortCut, QString toolTip, Functor lambda)
{
    QAction *act = new QAction(text, this);
    if(icon.length())
        act->setIcon(QIcon(icon));
    QKeySequence keySequence(shortCut);
    act->setShortcut(keySequence);
    act->setStatusTip(toolTip);
    act->setToolTip(toolTip);
    connect(act, &QAction::triggered, this, lambda);
    return act;
}

template<typename T>
QAction *QtEditor::makeAction(QString icon, QString text, T shortCut, QString toolTip, QObject *recv, const char* slot)
{
    QAction *act = new QAction(text, this);
    if(icon.length())
        act->setIcon(QIcon(icon));
    QKeySequence keySequence(shortCut);
    act->setShortcut(keySequence);
    act->setStatusTip(toolTip);
    act->setToolTip(toolTip);
    connect(act, SIGNAL(triggered()),recv, slot);
    return act;
}

QTextEdit *QtEditor::newFile() {
    qDebug("Make New File");
    QAction *newFileAct = makeAction(":/images/file.png",
                            tr("&New File"), tr(""), tr("New File"), this, SLOT(selectWindow()));
    windowMenu->addAction(newFileAct);

    QTextEdit *textedit = new QTextEdit;
    connect(textedit, SIGNAL(cursorPositionChanged()), SLOT(setFontWidget()));
    // connect(newFileAct, SIGNAL(triggered()), textedit, SLOT(setFocus()));
    connect(textedit, SIGNAL(destroyed(QObject*)), textedit, SLOT(deleteLater()));
    connect(textedit, SIGNAL(destroyed(QObject*)), newFileAct, SLOT(deleteLater()));
    mdiArea->addSubWindow(textedit);
    textedit->show( );

    windowHash[newFileAct] = textedit;
    return textedit;

}

void QtEditor::selectWindow() {
    QTextEdit *textedit = (QTextEdit*)windowHash[(QAction*)sender()];
    textedit->setFocus();
}

void QtEditor::openFile() {
    qDebug("Open a file");
    QString filename = QFileDialog::getOpenFileName(this,
                        tr("Select file to open"), ".","Text File(*.txt *.html *.c *.cpp *.h)");

    if(!filename.length()) return;

    QFileInfo fileInfo(filename);
    if(fileInfo.isReadable()) {
        QFile file(filename);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QByteArray msg = file.readAll();
        file.close();

        QTextEdit *textedit = newFile();
        textedit->setWindowTitle(filename);
        windowHash.key(textedit)->setText(filename);

        if(fileInfo.suffix() == "htm" || fileInfo.suffix() == "html")
            textedit->setHtml(msg);
        else
            textedit->setPlainText(msg);

    } else
        QMessageBox::warning(this, "Error", "Can't Read this file", QMessageBox::Ok);
}

void QtEditor::saveFile() {
    qDebug("Save this file");
    QMdiSubWindow *window = mdiArea->currentSubWindow();
    if(window != nullptr) {
        QTextEdit *textedit = qobject_cast<QTextEdit*>(window->widget( ));
        QString filename = textedit->windowTitle();
        if(!filename.length()) {
            filename = QFileDialog::getSaveFileName(this,
                        tr("Select file to save"), ".", tr("Text Files (*.txt *.html *.htm *.c *.cpp *.h *.hpp *.cs)"));
            if(!filename.length()) return;
            textedit->setWindowTitle(filename);
            windowHash.key(textedit)->setText(filename);
        }

        QFile file(filename);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QFileInfo fileInfo(filename);
        if(fileInfo.isWritable()) {
            QByteArray msg = (fileInfo.suffix() == "htm" || fileInfo.suffix() == "html")?
                                 textedit->toHtml().toUtf8():textedit->toPlainText().toUtf8();
            file.write(msg);
        } else
            QMessageBox::warning(this, "Error", "Can't Save this file", QMessageBox::Ok);
        file.close();
    }
}

void QtEditor::saveAsFile() {
    qDebug("Save As a file");
    QMdiSubWindow *window = mdiArea->currentSubWindow();
    if(window != nullptr) {
        QTextEdit *textedit = qobject_cast<QTextEdit*>(window->widget( ));
        QString filename = QFileDialog::getSaveFileName(this,
                            tr("Select file to save"), ".", tr("Text Files (*.txt *.html *.htm *.c *.cpp *.h *.hpp *.cs)"));

        if(!filename.length()) return;
        textedit->setWindowTitle(filename);
        QFile file(filename);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QFileInfo fileInfo(filename);
        if(fileInfo.isWritable()) {
            QByteArray msg = (fileInfo.suffix() == "htm" || fileInfo.suffix() == "html")?
                                 textedit->toHtml().toUtf8():textedit->toPlainText().toUtf8();
            file.write(msg);
        } else
            QMessageBox::warning(this, "Error", "Can't Save this file", QMessageBox::Ok);
        file.close();
    }
}

void QtEditor::print() {
    QPrinter printer(QPrinter::HighResolution);
    printer.setFullPage(true);
    QPrintDialog printDialog(&printer, this);
    if(printDialog.exec() == QDialog::Accepted) {
        QTextEdit *textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
        textedit->print(&printer);
    }
}
void QtEditor::undo() {
    QMdiSubWindow *subWindow = mdiArea->currentSubWindow();
    if(subWindow != nullptr) {
        QTextEdit *textedit = dynamic_cast<QTextEdit*>(subWindow->widget());
        textedit->undo();
    }
}

void QtEditor::redo() {
    QMdiSubWindow *subWindow = mdiArea->currentSubWindow();
    if(subWindow != nullptr) {
        QTextEdit *textedit = dynamic_cast<QTextEdit*>(subWindow->widget());
        textedit->redo();
    }
}

void QtEditor::copy() {
    QMdiSubWindow *subWindow = mdiArea->currentSubWindow();
    if(subWindow != nullptr) {
        QTextEdit *textedit = dynamic_cast<QTextEdit*>(subWindow->widget());
        textedit->copy();
    }
}

void QtEditor::cut() {
    QMdiSubWindow *subWindow = mdiArea->currentSubWindow();
    if(subWindow != nullptr) {
        QTextEdit *textedit = dynamic_cast<QTextEdit*>(subWindow->widget());
        textedit->cut();
    }
}

void QtEditor::paste() {
    QMdiSubWindow *subWindow = mdiArea->currentSubWindow();
    if(subWindow != nullptr) {
        QTextEdit *textedit = dynamic_cast<QTextEdit*>(subWindow->widget());
        textedit->paste();
    }
}

void QtEditor::zoomIn() {
    QMdiSubWindow *subWindow = mdiArea->currentSubWindow();
    if(subWindow != nullptr) {
        QTextEdit *textedit = dynamic_cast<QTextEdit*>(subWindow->widget());
        textedit->zoomIn();
    }
}

void QtEditor::zoomOut() {
    QMdiSubWindow *subWindow = mdiArea->currentSubWindow();
    if(subWindow != nullptr) {
        QTextEdit *textedit = dynamic_cast<QTextEdit*>(subWindow->widget());
        textedit->zoomOut();
    }
}

void QtEditor::about() {
    QMessageBox::about(this,"Information","CopyRight by Qt");
    // QMessageBox::information(this, "QMessageBox::information()","CopyRight by Qt",QMessageBox::Ok);
}

void QtEditor::setColor() {
    QTextEdit *textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    QColor color = QColorDialog::getColor();
    if(color.isValid()) textedit->setTextColor(color);
}

void QtEditor::setFont() {
    bool ok;
    QTextEdit *textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    QFont font = QFontDialog::getFont(&ok, textedit->currentFont(), this);
    if(ok) textedit->setCurrentFont(font);
}

void QtEditor::alignLeft() {
    QTextEdit *textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    textedit->setAlignment(Qt::AlignLeft);
}

void QtEditor::alignCenter() {
    QTextEdit *textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    textedit->setAlignment(Qt::AlignCenter);
}

void QtEditor::alignRight() {
    QTextEdit *textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    textedit->setAlignment(Qt::AlignRight);
}

void QtEditor::alignJustify() {
    QTextEdit *textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    textedit->setAlignment(Qt::AlignJustify);
}

void QtEditor::setTextFont(QFont font) {
    qDebug("setTextFont");
    QTextEdit *textedit = (QTextEdit*)mdiArea->currentSubWindow( )->widget( );
    textedit->setCurrentFont(font);
}

void QtEditor::setTextSize(qreal size) {
    qDebug("setTextSize");
    QTextEdit *textedit = (QTextEdit*)mdiArea->currentSubWindow( )->widget( );
    QFont font = textedit->currentFont( );
    font.setPointSizeF(size);
    textedit->setCurrentFont(font);
}
QtEditor::~QtEditor() {}
