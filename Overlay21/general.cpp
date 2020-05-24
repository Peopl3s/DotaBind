#include <QtWidgets>
#include <QtCore>
#include <algorithm>
#include "sendconsole.h"
#include "utilityfunctions.h"
#include <windows.h>
#include "general.h"

    General::General(QWidget *p):QWidget(p)
    {
        validatorGold = new QIntValidator(-99999, 99999);
        validatorLvl = new QIntValidator(1, 25);
        searchGen = new QLineEdit;
        searchGen->setPlaceholderText("Type word for searching. Press Enter");
        gold = new QLineEdit("1");
        lvlup = new QLineEdit("1");
        lvlup->setValidator(validatorLvl);
        gold->setValidator(validatorGold);
        commandsGen=new QTableWidget(rows,cols);
        commandsGen->setEditTriggers(QAbstractItemView::NoEditTriggers);
        commandsGen->setSelectionMode(QAbstractItemView::SingleSelection);
        commandsGen->setSelectionMode(QAbstractItemView::NoSelection);

        connect(searchGen,&QLineEdit::returnPressed,[this](){ searchedCommand( searchGen->text());});
        fillTable("console/general.txt");

        QVBoxLayout *v = new QVBoxLayout;
        v->setMargin(0);
        v->addWidget(searchGen);
        v->addWidget(commandsGen);

        QHBoxLayout *h = new QHBoxLayout;
        h->setMargin(0);
        h->addLayout(v);
        setLayout(h);
        setQss(this,"qss/generalstyle.qss");
    }

    void General::fillTable(const QString &path)
    {
        commandsGen->setHorizontalHeaderLabels(QStringList() << "Command" << "Option" << "Discribe");
        commandsGen->verticalHeader()->hide();
        QVector<QPair<QString,QString>> vecComm = readCommandsFromFile(path, "([a-z-_ ]+)\\;(---)\\;([a-zA-Z,.- ]+)\\r\\n");
        if(!vecComm.isEmpty())
        {
            for(int i = 0;i != rows; ++i)
            {
                QPair<QString, QString> p = vecComm.takeFirst();
                QPushButton *b1 = new QPushButton(p.first);
                connect(b1,&QPushButton::clicked,this, &General::sendCommndInConsole);
                commandsGen->setCellWidget(i, 0, b1);
                QLabel *l1 = new QLabel(p.second);
                l1->setWordWrap(true);
                commandsGen->setCellWidget(i, cols - 1, l1);
            }

        }
        commandsGen->setCellWidget(0, 1, gold);
        commandsGen->setCellWidget(1, 1, lvlup);
        commandsGen->resizeColumnsToContents();
        commandsGen->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);     // test
        commandsGen->horizontalHeader()->setStretchLastSection(true);


    }

    void General::sendCommndInConsole()
    {

        QString co = qobject_cast<QPushButton*>(sender())->text();
        if(co == "-gold")
        {
            co += " "+gold->text();
        }
        if(co.indexOf("-lvlup") != -1)
        {
           co += " " + lvlup->text();
        }

        qDebug()<<"Command: "<<co<<"\n";
        sendConsoleCommand(co.toStdString());
        //SetForegroundWindow((HWND)winId());
        SendMessage((HWND)winId(), WM_ACTIVATE, WA_ACTIVE, 0);
        SendMessage((HWND)winId(), WM_SETFOCUS, 0, 0);
    }

    void General::searchedCommand(const QString &text)
    {

            if(!allRowsShow(commandsGen))
            {
                for(int i = 0;i != commandsGen->rowCount(); ++i)
                {
                    commandsGen->showRow(i);
                }
                commandsGen->update();
              }
        QRegExp reg("([A-Z0-9 -.,]*)(" + text.toLower() + ")([A-Z0-9 -.,]*)");
        findlWork(commandsGen, reg, 0, rows);
        commandsGen->update();
    }
