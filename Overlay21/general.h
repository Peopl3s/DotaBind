#ifndef GENERAL
#define GENERAL
#include <QtWidgets>
#include <QtCore>
#include <algorithm>
#include "sendconsole.h"
#include "utilityfunctions.h"
#include <windows.h>

class General :public QWidget
{
    Q_OBJECT
public:
    General(QWidget *p = 0);
    ~General(){}
private:
    QLineEdit *searchGen;
    QLineEdit *lvlup;
    QLineEdit *gold;
    QTableWidget *commandsGen;
    QValidator *validatorLvl;
    QValidator *validatorGold;
    int rows = 10;
    int cols = 3;
public slots:
    void fillTable(const QString &);
    void sendCommndInConsole();
    void searchedCommand(const QString &);
};
#endif // GENERAL

