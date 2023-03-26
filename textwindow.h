#ifndef TEXTWINDOW_H
#define TEXTWINDOW_H

#include <QDialog>

namespace Ui {
class TextWindow;
}

class TextWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TextWindow(int lvl, QWidget *parent = nullptr);
    ~TextWindow();

private slots:
    void on_pushButton_clicked();

signals:
    /*!
     * \brief closedW сигнал закрытия окна
     * \param window указатель на это окно
     */
    void closedW(TextWindow *window);

private:
    Ui::TextWindow *ui;
    /*!
     * \brief setHiddenAll ф-я прячущая все лейблы
     */
    void setHiddenAll();

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // TEXTWINDOW_H
