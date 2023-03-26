#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

#define OPERATOR 1
#define TEXNIK   2
#define INJENER  3

#define LEVEL_FILE_PATH "PersonLevel.json"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Тестовое задание");

    setHidenAllBtn();

    ui->lineEdit->setEchoMode(QLineEdit::Password);

    if(lvlChecker.setPathToFile(LEVEL_FILE_PATH)) {
        qCritical() << "Неправильно указан путь до файла с уровнями доступа";
        ui->pushButton->setEnabled(false);
        return;
    }

    connect(&thread, &QThread::started, &lvlChecker, &LevelChecker::run);

    connect(&lvlChecker, &LevelChecker::sendLevel, this, &MainWindow::takeLevel, Qt::DirectConnection);
    connect(&lvlChecker, &LevelChecker::finished, &thread, &QThread::terminate);

    lvlChecker.moveToThread(&thread);

    connect(this, &MainWindow::levelSet, this, &MainWindow::setLevel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::takeLevel(QString level)
{
    lvl = level;
    emit levelSet();
}

void MainWindow::setHidenAllBtn()
{
    ui->btn1->setHidden(true);
    ui->btn2->setHidden(true);
    ui->btn3->setHidden(true);
    ui->btn4->setHidden(true);
    ui->btn5->setHidden(true);
    ui->btn6->setHidden(true);
}

void MainWindow::setLevel()
{
    if(lvl == "оператор") {
        setBtnLvl(OPERATOR);
        windowLevel = OPERATOR;
    } else if(lvl == "техник") {
        setBtnLvl(TEXNIK);
        windowLevel = TEXNIK;
    } else if(lvl == "инженер") {
        setBtnLvl(INJENER);
        windowLevel = INJENER;
    }
}

void MainWindow::setBtnLvl(const int lvl)
{
    setHidenAllBtn();
    switch (lvl) {
        case 3:
            ui->btn5->setHidden(false);
            ui->btn6->setHidden(false);
        case 2:
            ui->btn3->setHidden(false);
            ui->btn4->setHidden(false);
        case 1:
            ui->btn1->setHidden(false);
            ui->btn2->setHidden(false);
        default:
            break;
    }
}

void MainWindow::on_pushButton_clicked()
{
    lvlChecker.setPass(ui->lineEdit->text());

    thread.start();
}

void MainWindow::on_WindowBtn_clicked()
{
    window1 = new TextWindow(windowLevel);

    connect(window1, &TextWindow::closedW, this, &MainWindow::closeTextW);

    window1->show();
}

void MainWindow::closeTextW(TextWindow *window)
{
    window->deleteLater();
}
