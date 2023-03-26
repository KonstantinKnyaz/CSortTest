#ifndef LEVELCHECKER_H
#define LEVELCHECKER_H

#include <QObject>
#include <QHash>

class LevelChecker : public QObject
{
    Q_OBJECT

    enum ERRORS {
        NO_ERROR = 0x0,
        READ_ERROR = 0x1,
        JSON_ERROR = 0x2,
        ANOTHER_ERROR = 0x3
    };

public:
    explicit LevelChecker(QObject *parent = Q_NULLPTR);
    ~LevelChecker();
    /*!
     * \brief setPathToFile ф-я устанавливает путь до файла с уровнями доступа и паролями
     * \param personalFileDataPath переменная пути
     */
    int setPathToFile(const QString &personalFileDataPath);
    /*!
     * \brief setPass устанавливает пароль введённй пользователем
     * \param pass переменная пароля
     */
    void setPass(const QString &pass);

signals:
    /*!
     * \brief finished сигнал об окончании проверки
     */
    void finished();
    /*!
     * \brief sendLevel сигнал о получении уровня доступа
     * \param level переменная уровня доступа
     */
    void sendLevel(QString level);

public slots:
    /*!
     * \brief run слот начала проверки уровня доступа
     */
    void run();

private:
    /*!
     * \brief startReadFile функция начала чтения файла со списком уровней доступа и паролями
     * \return
     */
    int startReadFile();
    /*!
     * \brief _personalFileDataPath переменная с путём к файлу со списком уровней доступа и паролями
     */
    QString _personalFileDataPath;
    /*!
     * \brief _pass переменная пароля
     */
    QString _pass;
    /*!
     * \brief _level переменная уровня доступа
     */
    QString _level;
};

#endif // LEVELCHECKER_H
