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
    QAction *openAct = makeAction(":/images/open.png", tr("&Open"), QKeySequence::Open, tr("Open file"), [this](){ newFile();});
    QAction *saveAct = makeAction(":/images/save.png", tr("&Save"), QKeySequence::Save, tr("Save file"), [this](){ newFile();});
    QAction *saveAsAct = makeAction(":/images/saveAs.png", tr("&Save As..."), QKeySequence::SaveAs, tr("Save as file"), [this](){ newFile();});
    QAction *undoAct = makeAction(":/images/undo.png", tr("&Undo"), QKeySequence::Undo, tr("Undo"), [=]{ textedit->undo();});
    QAction *redoAct = makeAction(":/images/redo.png", tr("&Redo"), QKeySequence::Redo, tr("redo"), [=]{ textedit->redo();});
    QAction *copyAct = makeAction(":/images/copy.png", tr("&Copy"), QKeySequence::Copy, tr("Copy"), [=]{ textedit->copy();});
    QAction *cutAct = makeAction(":/images/cut.png", tr("&Cut"), QKeySequence::Cut,  tr("Cut"), [=]{ textedit->cut();});
    QAction *pasteAct = makeAction(":/images/paste.png", tr("&Paste"), QKeySequence::Paste,  tr("Paste"), [=]{ textedit->paste();});
    QAction *zoomInAct = makeAction(":/images/zoomIn.png", tr("&ZoomIn"), QKeySequence::ZoomIn,  tr("ZoomIn"), [=]{ textedit->zoomIn();});
    QAction *zoomOutAct = makeAction(":/images/zoomOut.png", tr("&ZoomOut"), QKeySequence::ZoomOut,  tr("ZoomOut"), [=]{ textedit->zoomOut();});

    //QMenu class
    QMenu *fileMenu = menubar->addMenu("&File");
    QMenu *editMenu = menubar->addMenu("&Edit");
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
    QAction *alignLeftAct = new QAction(QIcon(":/images/left.png"), "&Left", this);
    QAction *alignCenterAct = new QAction(QIcon(":/images/center.png"), "&Center", this);
    QAction *alignRightAct = new QAction(QIcon(":/images/right.png"), "&Right", this);
    QAction *alignJustifyAct = new QAction(QIcon(":/images/justify.png"), "&Justify", this);
    alignMenu->addAction(alignLeftAct);
    alignMenu->addAction(alignCenterAct);
    alignMenu->addAction(alignRightAct);
    alignMenu->addAction(alignJustifyAct);
    connect(alignLeftAct, &QAction::triggered, this, [=]{ textedit->setAlignment(Qt::AlignLeft);});
    connect(alignCenterAct, &QAction::triggered, this, [=]{ textedit->setAlignment(Qt::AlignCenter);});
    connect(alignRightAct, &QAction::triggered, this, [=]{ textedit->setAlignment(Qt::AlignRight);});
    connect(alignJustifyAct, &QAction::triggered, this, [=]{ textedit->setAlignment(Qt::AlignJustify);});

    QColorDialog *colorDialog = new QColorDialog(this);
    QAction *colorAct = new QAction(QIcon(":/images/color.png"), "&Color", this);
    // QAction *fontAct = new QAction(QIcon(":/images/font.png"), "&Font", this);
    formatMenu->addAction(colorAct);
    connect(colorAct, &QAction::triggered, this, [=]{ colorDialog->open();});
    connect(colorDialog, SIGNAL(colorSelected(QColor)), textedit, SLOT(setTextColor(QColor)));

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

    QTextEdit *text = new QTextEdit(w);
    text->resize(150, 150);
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

QTextEdit *QtEditor::newFile() {
    qDebug("Make New File");
    QTextEdit *textedit = new QTextEdit;
    // mdiArea->cascadeSubWindows();
    mdiArea->resize(1000, 1000);
    mdiArea->addSubWindow(textedit);
    textedit->show();
    return textedit;
}
QtEditor::~QtEditor() {}
