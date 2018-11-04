#ifndef BOTSITEMS
#define BOTSITEMS
#include <QtWidgets>
#include <QtCore>
#include <algorithm>
#include "sendconsole.h"
#include "utilityfunctions.h"
#include <windows.h>
class BotsItems :public QWidget
{
    Q_OBJECT
public:
    BotsItems(QWidget *p = 0);
    ~BotsItems(){}
private:
    QLineEdit *searchBI;
    QTableWidget *commandBI;
    const int rows = 150;
    const int cols = 3;
public slots:
    void fillTable(const QString &, const QString &);
    void sendCommndInConsole();
    void searchedCommand(const QString &);
};
#endif // BOTSITEMS

