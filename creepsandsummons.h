#ifndef CREEPSANDSUMMONS
#define CREEPSANDSUMMONS
#include <QtWidgets>
#include <QtCore>
#include <algorithm>
#include "sendconsole.h"
#include "utilityfunctions.h"
#include <windows.h>

class Creeps_And_Summons :public QWidget
{
    Q_OBJECT
public:
    Creeps_And_Summons(QWidget *p = 0);
    ~Creeps_And_Summons(){}
private:
    QLineEdit *searchCS;
    QTableWidget *commandCS;
    const int rows = 121;
    const int cols = 3;
public slots:
    void fillTable(const QString &);
    void sendCommndInConsole();
    void searchedCommand(const QString &);
};

#endif // CREEPSANDSUMMONS

