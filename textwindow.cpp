#include "textwindow.h"
#include "ui_textwindow.h"

TextWindow::TextWindow(int lvl, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TextWindow)
{
    ui->setupUi(this);
    setModal(false);

    setHiddenAll();

    switch (lvl) {
        case 3:
            ui->label_6->setHidden(false);
            ui->label_5->setHidden(false);
        case 2:
            ui->label_4->setHidden(false);
            ui->label_3->setHidden(false);
        case 1:
            ui->label_2->setHidden(false);
            ui->label->setHidden(false);
        default:
            break;
    }
}

TextWindow::~TextWindow()
{
    delete ui;
}

void TextWindow::on_pushButton_clicked()
{
    this->close();
}

void TextWindow::setHiddenAll()
{
    ui->label_6->setHidden(true);
    ui->label_5->setHidden(true);

    ui->label_4->setHidden(true);
    ui->label_3->setHidden(true);

    ui->label_2->setHidden(true);
    ui->label->setHidden(true);
}

void TextWindow::closeEvent(QCloseEvent *event)
{
    emit closedW(this);
}

