#include "widget.h"
#include <QDir>
#include <QFile>
#include <QListWidget>
#include <QLineEdit>
#include <QFileInfo>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QMenu>
#include <QContextMenuEvent>
#include <QApplication>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    directory = new QDir("."); // 현재 디렉토리 내용을 저장하는 객체

    QAction *mkdirAction = new QAction("&Make Directory", this);
    connect(mkdirAction, SIGNAL(triggered()), SLOT(makeDir()));

    QAction *copyAction = new QAction("&Copy", this);
    connect(copyAction, SIGNAL(triggered()), SLOT(copyFile()));

    QAction *removeAction = new QAction("Re&move", this);
    connect(removeAction, SIGNAL(triggered()), SLOT(removeDir()));

    QAction *renameAction = new QAction("&Rename", this);
    connect(renameAction, SIGNAL(triggered()), SLOT(renameDir()));

    QAction *quitAction = new QAction("&Quit", this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    m_menu = new QMenu(this);
    m_menu->addSection("&Directory");

    m_menu->addAction(mkdirAction);
    m_menu->addSeparator();
    m_menu->addSection("&File");
    m_menu->addAction(copyAction);
    m_menu->addAction(removeAction);
    m_menu->addAction(renameAction);
    m_menu->addSeparator();
    m_menu->addAction(quitAction);


    // 화면에 표시될 위젯들을 정의하고 레이아웃
    dirListWidget = new QListWidget(this);
    filenameLineEdit = new QLineEdit(this);

    outputEdit = new QTextEdit(this);
    outputEdit->setReadOnly(true);

    QPushButton *actionButton = new QPushButton("Action", this);
    actionButton->setMenu(m_menu); // 팝업 메뉴를 설정

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(dirListWidget);
    layout->addWidget(filenameLineEdit);
    layout->addWidget(actionButton);
    layout->addWidget(outputEdit);

    // 시그널과 슬롯을 연결
    connect(dirListWidget, SIGNAL(itemClicked(QListWidgetItem*)),SLOT(selectItem(QListWidgetItem*)));
    connect(dirListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), SLOT(changeDir()));

    refreshDir(); // 현재 디렉토리 내용을 QListWidget에 표시

}

Widget::~Widget() {}

void Widget::refreshDir() { // 디렉토리를 경신
    dirListWidget->clear(); // 현재 QListWidget의 내용을 모두 삭제

    // QDir 클래스에 저장된 현재 파일의 목록을 QListWidget에 아이템으로 추가
    for(int index=0; index < directory->entryList().count(); index++) {
        dirListWidget->addItem(directory->entryList().at(index));
    }
}

void Widget::selectItem(QListWidgetItem *item) {
    filenameLineEdit->setText(item->text());
}

void Widget::copyFile() { // 파일 복사
    QString filename = directory->absoluteFilePath(dirListWidget->currentItem()->text());

    QFileInfo checkDir(filename);
    if(checkDir.isFile() && filenameLineEdit->text().length()) {
        QString newFile = directory->absoluteFilePath(filenameLineEdit->text());
        QFile::copy(filename, newFile); // QFile의 static 메소드 사용
    }
    refreshDir();
}

void Widget::changeDir() {
    // 현재 파일의 경로를 절대 경로로 변경
    QString filename = directory->absoluteFilePath(dirListWidget->currentItem()->text());

    QFileInfo checkDir(filename); // QFileInfo 클래스로 파일 체크
    if(checkDir.isDir()) { // 디렉토리이면 파일 이동 후 QListWidget을 경신
        directory->cd(filename);
        directory->refresh();
        refreshDir();
    }
}

void Widget::makeDir() { // 디렉토리 생성
    if(filenameLineEdit->text().length() && dirListWidget->currentItem()!= NULL) {
        directory->mkdir(filenameLineEdit->text());
        directory->refresh(); // QDir 클래스는 현재의 디렉토리 정보를 캐싱
        refreshDir();
    }
}

void Widget::removeDir() { // 디렉토리나 파일 삭제
    if(filenameLineEdit->text().length() && dirListWidget->currentItem()!= NULL) {
        QString filename = directory->absoluteFilePath(dirListWidget->currentItem()->text());

        QFileInfo checkDir(filename);
        if(checkDir.isDir()) // 디렉토리이면 디렉토리 삭제
            directory->rmdir(filenameLineEdit->text());
        else if(checkDir.isFile()) // 파일이면 파일 삭제
            QFile::remove(filename);
        directory->refresh();
        refreshDir();
    }
}

void Widget::renameDir() { // 디렉토리나 파일의 이름 변경
    if(filenameLineEdit->text().length() && dirListWidget->currentItem()!= NULL) {
        directory->rename(dirListWidget->currentItem()->text(), filenameLineEdit->text());
        directory->refresh();
        refreshDir();
    }
}

// 컨텍스트 메뉴를 오픈
void Widget::contextMenuEvent(QContextMenuEvent *event) {
    QWidget::contextMenuEvent(event);
    m_menu->exec(QCursor::pos());
}














