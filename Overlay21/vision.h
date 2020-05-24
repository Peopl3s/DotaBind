#ifndef VISION
#define VISION
#include <QtWidgets>
#include <QtCore>
#include <algorithm>
#include "sendconsole.h"
#include "utilityfunctions.h"
#include <windows.h>

class Vision :public QWidget
{
    Q_OBJECT
public:
    Vision(QWidget *p = 0);
    ~Vision(){}
private:
    QLineEdit *searchVis;
    QTableWidget *commandVis;
    const int rows = 6;
    const int cols = 3;
public slots:
    void fillTable(const QString &);
    void sendCommndInConsole();
    void searchedCommand(const QString &);
};

#endif // VISION

