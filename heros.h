#ifndef HEROS
#define HEROS
#include <QtWidgets>
#include <QtCore>
#include <algorithm>
#include "sendconsole.h"
#include "utilityfunctions.h"
#include <windows.h>

class Heros :public QWidget
{
    Q_OBJECT
public:
    Heros(QWidget *p = 0);
    ~Heros(){}
public slots:
    void fillTable(const QString &, const QString &);
    void sendCommndInConsole();
    void searchedCommand(const QString &);
private:
    QLineEdit *searchHero;
    QLineEdit *lvl;
    QTableWidget *commandsH;
    QLabel *fraction;
    QRadioButton *enemy;
    QRadioButton *neutral;
    QValidator *validator;
    const int rows = 117;
    const int cols = 3;
};
#endif // HEROS

