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


QtEditor::QtEditor(QWidget *parent)
    : QMainWindow(parent)
{
    //QMdiArea widget
    mdiArea = new QMdiArea(this);
    setCentralWidget(mdiArea);
#if 0
    QTextEdit *textedit = new QTextEdit(this);
    mdiArea->addSubWindow(textedit);
#else
    QTextEdit *textedit = newFile();
#endif

    // QTextEdit *textedit = new QTextEdit(this);
    // setCentralWidget(textedit);

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


    //QMenu class
    QMenu *fileMenu = menubar->addMenu("&File");
    QMenu *editMenu = menubar->addMenu("&Edit");
    QMenu *helpMenu = menubar->addMenu("&Help");
    fileMenu->addAction(newAct);
    fileMenu->addAction(quitAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);

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
    QAction *alignLeftAct = new QAction(QIcon(":/images/left.png"), "Left", this);
    QAction *alignCenterAct = new QAction(QIcon(":/images/center.png"), "Center", this);
    QAction *alignRightAct = new QAction(QIcon(":/images/right.png"), "Right", this);
    QAction *alignJustifyAct = new QAction(QIcon(":/images/justify.png"), "Justify", this);
    alignMenu->addAction(alignLeftAct);
    alignMenu->addAction(alignCenterAct);
    alignMenu->addAction(alignRightAct);
    alignMenu->addAction(alignJustifyAct);
    connect(alignLeftAct, SIGNAL(triggered()), this, SLOT(alignLeft()));
    connect(alignCenterAct, SIGNAL(triggered()), this, SLOT(alignCenter()));
    connect(alignRightAct, SIGNAL(triggered()), this, SLOT(alignRight()));
    connect(alignJustifyAct, SIGNAL(triggered()), this, SLOT(alignJustify()));


    //QToolBar class
    QToolBar *fileToolBar = addToolBar("&File");
    fileToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);
    fileToolBar->addAction(saveAsAct);


    fileToolBar->addSeparator();
    fileToolBar->addAction(quitAct);
    fileToolBar->addAction(undoAct);
    fileToolBar->addAction(redoAct);

    fileToolBar->addSeparator();
    fileToolBar->addAction(copyAct);
    fileToolBar->addAction(pasteAct);

    fileToolBar->addSeparator();
    fileToolBar->addAction(zoomInAct);
    fileToolBar->addAction(zoomOutAct);

    QMenu *windowMenu = menubar->addMenu("&Window");
    QMenu *toolbarMenu = windowMenu->addMenu("&Toolbar");
    toolbarMenu->addAction(fileToolBar->toggleViewAction());

    QFontComboBox *fontComboBox = new QFontComboBox(this);
    connect(fontComboBox, SIGNAL(currentFontChanged(QFont)), textedit, SLOT(setCurrentFont(QFont)));
    QDoubleSpinBox *sizeSpinBox = new QDoubleSpinBox(this);
    connect(sizeSpinBox, SIGNAL(valueChanged(double)), textedit, SLOT(setFontPointSize(qreal)));
    addToolBarBreak(); // 다음 툴바는 아랫줄로 위치


    QToolBar *formatToolbar = addToolBar("&Format");
    formatToolbar->addAction(fontAct);
    formatToolbar->addAction(colorAct);
    formatToolbar->addWidget(fontComboBox);
    formatToolbar->addWidget(sizeSpinBox);
    formatToolbar->addSeparator();
    formatToolbar->addAction(alignLeftAct);
    formatToolbar->addAction(alignCenterAct);
    formatToolbar->addAction(alignRightAct);
    formatToolbar->addAction(alignJustifyAct);




    //QDockWidget class
    QWidget *w = new QWidget(this);
    QLabel *label = new QLabel("Dock Widget", w);
    label->resize(100, 500);
    QDockWidget *dock = new QDockWidget("Dock Widget", label);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);


    // QDockWidget 크기 설정
    dock->setMinimumSize(150, 150); // 최소 크기 설정

    addDockWidget(Qt::RightDockWidgetArea, dock);
    dock->setWidget(w);

    // QTextEdit *text = new QTextEdit(w);
    // text->resize(150, 150);
    toolbarMenu->addAction(dock->toggleViewAction());


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
    QTextEdit *textedit = new QTextEdit;
    mdiArea->addSubWindow(textedit);
    textedit->show();
    // mdiArea->tileSubWindows();
    // mdiArea->cascadeSubWindows();
    return textedit;
}

void QtEditor::openFile() {
    QString fileName = QFileDialog::getOpenFileName(this,
                    tr("Select file to open"), QDir::home().dirName(),"Text File(*.txt *.html *.c *.cpp *.h)");
    qDebug() << fileName;


}

void QtEditor::saveFile() {
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Select file to save"), ".","Text File(*.txt *.html *.c *.cpp *.h)");
    qDebug() << fileName;


}

void QtEditor::saveAsFile() {
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Select file to save as"), QDir::home().dirName(),"Text File(*.txt *.html *.c *.cpp *.h)");
    qDebug() << fileName;


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

QtEditor::~QtEditor() {}
