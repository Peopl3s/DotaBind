#ifndef WARDS
#define WARDS
#include <QtWidgets>
#include <QtCore>
#include <algorithm>
#include "sendconsole.h"
#include "utilityfunctions.h"
#include <windows.h>

class Wards :public QWidget
{
    Q_OBJECT
public:
    Wards(QWidget *p = 0);
    ~Wards(){}
private:
    QLineEdit *searchV;
    QTableWidget *commandV;
    const int rows = 2;
    const int cols = 3;
public slots:
    void fillTable(const QString &);
    void sendCommndInConsole();
    void searchedCommand(const QString &);
};
#endif // WARDS

