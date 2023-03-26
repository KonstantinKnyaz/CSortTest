#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>

#include "levelchecker.h"

#include "textwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /*!
     * \brief takeLevel слот вызываемый для принятия уровня доступа
     * \param level название уровня доступа
     */
    void takeLevel(QString level);
    void on_pushButton_clicked();
    /*!
     * \brief setLevel слот для установки уровна доступа
     */
    void setLevel();

    void on_WindowBtn_clicked();
    /*!
     * \brief closeTextW слот для последующего уджаления класса вызываемого диалогового окна
     * \param window указатель на область памяти, где хранится диалоговое окно
     */
    void closeTextW(TextWindow *window);

signals:
    /*!
     * \brief levelSet сигнал того, что уровень доступа получен
     */
    void levelSet();

private:
    Ui::MainWindow *ui;
    /*!
     * \brief setHidenAllBtn ф-я прячущая все кнопки
     */
    void setHidenAllBtn();
    /*!
     * \brief setBtnLvl функция показывающая кнопки в зависимости от уровня доступа
     * \param lvl
     */
    void setBtnLvl(const int lvl);

    QThread thread;
    /*!
     * \brief lvlChecker класс для выявления уровня доступа
     */
    LevelChecker lvlChecker;
    /*!
     * \brief lvl уровень доступа
     */
    QString lvl;
    /*!
     * \brief windowLevel номер уровня доступа (сделал для того, чтобы можно было поработать со свич кейсами)
     */
    int windowLevel = 0;
    /*!
     * \brief window1 указатель на диалоговое окно
     */
    TextWindow *window1 = Q_NULLPTR;
};
#endif // MAINWINDOW_H
