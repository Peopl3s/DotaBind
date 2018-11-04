#ifndef DOTAITEMS
#define DOTAITEMS
#include <QtWidgets>
#include <QtCore>
#include <algorithm>
#include "sendconsole.h"
#include "utilityfunctions.h"
#include <QtConcurrent>
#include <QAtomicInt>
#include <windows.h>

class DotaItems :public QWidget
{
    Q_OBJECT
public:
    DotaItems(QWidget *p = 0);
    ~DotaItems(){}
private:
    QLineEdit *search;
    QTableWidget *commands;
    const int rows = 151;
    const int cols = 3;
public slots:
    void fillTable(const QString &, const QString &);
    void sendCommndInConsole();
    void searchedCommand(const QString &);
};
#endif // DOTAITEMS

