#include <QtWidgets>
#include <QtCore>
#include <algorithm>
#include "sendconsole.h"
#include "utilityfunctions.h"
#include <windows.h>
#include "botsitems.h"

    BotsItems::BotsItems(QWidget *p):QWidget(p)
    {
        searchBI = new QLineEdit;
        searchBI->setPlaceholderText("Type word for searching. Press Enter");
        commandBI = new QTableWidget(rows, cols);
        connect(searchBI,&QLineEdit::returnPressed,[this](){ searchedCommand(searchBI->text());});
        fillTable("console/botsitems.txt","ItemSorted");
        commandBI->setEditTriggers(QAbstractItemView::NoEditTriggers);
        commandBI->setSelectionMode(QAbstractItemView::SingleSelection);
        commandBI->setSelectionMode(QAbstractItemView::NoSelection);

        QVBoxLayout *v = new QVBoxLayout;
        v->setMargin(0);
        v->addWidget(searchBI);
        v->addWidget(commandBI);

        QHBoxLayout *h = new QHBoxLayout;
        h->setMargin(0);
        h->addLayout(v);
        setLayout(h);
    }

    void BotsItems::fillTable(const QString &path, const QString &pathP)
    {
        commandBI->setHorizontalHeaderLabels(QStringList() << "Command"<<"Option"<<"Discribe");
        commandBI->verticalHeader()->hide();
        QVector<QPair<QString, QString>> vecComm = readCommandsFromFile(path, "([a-z0-9-_ ()]+);(---);([a-zA-Z0-9,.- ()]+)\\r\\n");
        QStringList pics = picLoad(pathP);
        if(!vecComm.isEmpty())
        {
            for(int i  =0;i != rows; ++i)
            {
                QPair<QString, QString> p = vecComm.takeFirst();
                QPushButton *b1 = new QPushButton(p.first);
                b1->setMaximumWidth(200);
                connect(b1,&QPushButton::clicked,this, &BotsItems::sendCommndInConsole);
                commandBI->setCellWidget(i, 0, b1);
                QLabel *l1 = new QLabel(p.second);
                l1->setWordWrap(true);
                commandBI->setCellWidget(i, cols - 1, l1);
                QLabel *icon = new QLabel;
                icon->setPixmap(QPixmap(pathP + "/" + pics.at(i)));
                icon->setFixedSize(100, 40);
                icon->setAlignment(Qt::AlignCenter);
                commandBI->setCellWidget(i, 1, icon);
            }
        }
        commandBI->resizeColumnsToContents();
        commandBI->resizeRowsToContents();
        commandBI->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);        // test
        commandBI->horizontalHeader()->setStretchLastSection(true);
    }

    void BotsItems::sendCommndInConsole()
    {
        QString co = qobject_cast<QPushButton*>(sender())->text();
        sendConsoleCommand(co.toStdString());
        SendMessage((HWND)winId(), WM_ACTIVATE, WA_ACTIVE, 0);
        SendMessage((HWND)winId(), WM_SETFOCUS, 0, 0);
    }

    void BotsItems::searchedCommand(const QString &text)
    {
        //qDebug()<<text;
            if(!allRowsShow(commandBI))
            {
                for(int i = 0;i != commandBI->rowCount(); ++i)
                {
                    commandBI->showRow(i);
                }
                 commandBI->update();
              }
        QRegExp reg("([A-Z0-9 -.,]*)(" + text.toLower() + ")([A-Z0-9 -.,]*)");
        findlWork(commandBI, reg, 0, rows);
        commandBI->update();
    }

