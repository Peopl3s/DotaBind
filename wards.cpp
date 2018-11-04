#include <QtWidgets>
#include <QtCore>
#include <algorithm>
#include "sendconsole.h"
#include "utilityfunctions.h"
#include <windows.h>
#include "wards.h"


    Wards::Wards(QWidget *p):QWidget(p)
    {
        searchV=new QLineEdit;
        searchV->setPlaceholderText("Type word for searching. Press Enter");
        commandV=new QTableWidget(rows,cols);
        connect(searchV,&QLineEdit::returnPressed,[this](){ searchedCommand(searchV->text());});
        fillTable("console/wards.txt");

        commandV->setEditTriggers(QAbstractItemView::NoEditTriggers);
        commandV->setSelectionMode(QAbstractItemView::SingleSelection);
        commandV->setSelectionMode(QAbstractItemView::NoSelection);

        QVBoxLayout *v = new QVBoxLayout;
        v->setMargin(0);
        v->addWidget(searchV);
        v->addWidget(commandV);

        QHBoxLayout *h = new QHBoxLayout;
        h->setMargin(0);
        h->addLayout(v);
        setLayout(h);
    }


    void Wards::fillTable(const QString &path)
    {
        commandV->setHorizontalHeaderLabels(QStringList()<<"Command"<<"Option"<<"Discribe");
        commandV->verticalHeader()->hide();
        QVector<QPair<QString,QString>> vecComm=readCommandsFromFile(path,"([a-z-_ ]+);(---);([a-zA-Z,.- ]+)\\r\\n");
        if(!vecComm.isEmpty())
        {
            for(int i = 0;i != rows; ++i)
            {
                QPair<QString,QString> p = vecComm.takeFirst();
                QPushButton *b1 = new QPushButton(p.first);
                connect(b1,&QPushButton::clicked,this, &Wards::sendCommndInConsole);
                commandV->setCellWidget(i, 0, b1);
                QLabel *l1 = new QLabel(p.second);
                l1->setWordWrap(true);
                commandV->setCellWidget(i, cols-1, l1);
            }
        }
          commandV->resizeColumnsToContents();
          commandV->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);       // test
          commandV->horizontalHeader()->setStretchLastSection(true);
}

    void Wards::sendCommndInConsole()
    {
        QString co = qobject_cast<QPushButton*>(sender())->text();
        sendConsoleCommand(co.toStdString());
        SendMessage((HWND)winId(), WM_ACTIVATE, WA_ACTIVE, 0);
        SendMessage((HWND)winId(), WM_SETFOCUS, 0, 0);
    }

    void Wards::searchedCommand(const QString &text)
    {
            if(!allRowsShow(commandV))
            {
                for(int i = 0;i != commandV->rowCount(); ++i)
                {
                    commandV->showRow(i);
                }
                 commandV->update();
              }
        QRegExp reg("([A-Z0-9 -.,]*)(" + text.toLower() + ")([A-Z0-9 -.,]*)");
        findlWork(commandV, reg, 0, rows);
        commandV->update();
    }

