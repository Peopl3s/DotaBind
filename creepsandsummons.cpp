#include <QtWidgets>
#include <QtCore>
#include <algorithm>
#include "sendconsole.h"
#include "utilityfunctions.h"
#include <windows.h>
#include "creepsandsummons.h"
    Creeps_And_Summons::Creeps_And_Summons(QWidget *p):QWidget(p)
    {
        searchCS = new QLineEdit;
        searchCS->setPlaceholderText("Type word for searching. Press Enter");
        commandCS=new QTableWidget(rows, cols);
        connect(searchCS, &QLineEdit::returnPressed,[this](){ searchedCommand(searchCS->text());});
        fillTable("console/creepss.txt");
        commandCS->setEditTriggers(QAbstractItemView::NoEditTriggers);
        commandCS->setSelectionMode(QAbstractItemView::SingleSelection);
        commandCS->setSelectionMode(QAbstractItemView::NoSelection);

        QVBoxLayout *v = new QVBoxLayout;
        v->setMargin(0);
        v->addWidget(searchCS);
        v->addWidget(commandCS);

        QHBoxLayout *h = new QHBoxLayout;
        h->setMargin(0);
        h->addLayout(v);
        setLayout(h);
    }

    void Creeps_And_Summons::fillTable(const QString &path)
    {
        commandCS->setHorizontalHeaderLabels(QStringList() << "Command"<<"Option"<<"Discribe");
        commandCS->verticalHeader()->hide();
        QVector<QPair<QString, QString>> vecComm=readCommandsFromFile(path, "([a-z0-9-_ ()]+);(---);([a-zA-Z0-9 ,.- ()]+)\\r\\n");
        //qDebug()<<"Creeps:"<<vecComm.size();
        if(!vecComm.isEmpty())
        {
            for(int i = 0;i != rows; ++i)
            {
                QPair<QString,QString> p = vecComm.takeFirst();
                QPushButton *b1 = new QPushButton(p.first);
                connect(b1, &QPushButton::clicked, this, &Creeps_And_Summons::sendCommndInConsole);
                commandCS->setCellWidget(i, 0, b1);
                QLabel *l1 = new QLabel(p.second);
                l1->setWordWrap(true);
                commandCS->setCellWidget(i, cols - 1, l1);
            }
        }
          commandCS->resizeColumnsToContents();
          commandCS->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
          commandCS->horizontalHeader()->setStretchLastSection(true);  // test
}

    void Creeps_And_Summons::sendCommndInConsole()
    {
        QString co = qobject_cast<QPushButton*>(sender())->text();
        sendConsoleCommand(co.toStdString());
        SendMessage((HWND)winId(), WM_ACTIVATE, WA_ACTIVE, 0);
        SendMessage((HWND)winId(), WM_SETFOCUS, 0, 0);
    }

    void Creeps_And_Summons::searchedCommand(const QString &text)
    {
            if(!allRowsShow(commandCS))
            {
                for(int i = 0;i != commandCS->rowCount(); ++i)
                {
                    commandCS->showRow(i);
                }
                 commandCS->update();
              }
        QRegExp reg("([A-Z0-9 -.,]*)(" + text.toLower() + ")([A-Z0-9 -.,]*)");
        findlWork(commandCS, reg, 0, rows);
        commandCS->update();
    }

