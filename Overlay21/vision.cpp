#include <QtWidgets>
#include <QtCore>
#include <algorithm>
#include "sendconsole.h"
#include "utilityfunctions.h"
#include <windows.h>
#include "vision.h"


    Vision::Vision(QWidget *p):QWidget(p)
    {
        searchVis = new QLineEdit;
        searchVis->setPlaceholderText("Type word for searching. Press Enter");
        commandVis=new QTableWidget(rows, cols);
        connect(searchVis, &QLineEdit::returnPressed, [this](){ searchedCommand(searchVis->text());});
        fillTable("console/visioncreep.txt");

        commandVis->setEditTriggers(QAbstractItemView::NoEditTriggers);
        commandVis->setSelectionMode(QAbstractItemView::SingleSelection);
        commandVis->setSelectionMode(QAbstractItemView::NoSelection);

        QVBoxLayout *v = new QVBoxLayout;
        v->setMargin(0);
        v->addWidget(searchVis);
        v->addWidget(commandVis);

        QHBoxLayout *h = new QHBoxLayout;
        h->setMargin(0);
        h->addLayout(v);
        setLayout(h);
    }

    void Vision::fillTable(const QString &path)
    {
        commandVis->setHorizontalHeaderLabels(QStringList() << "Command" << "Option" << "Discribe");
        commandVis->verticalHeader()->hide();
        QVector<QPair<QString, QString>> vecComm = readCommandsFromFile(path, "([a-z-_ ]+);(---);([a-zA-Z,.- ]+)\\r\\n");
        if(!vecComm.isEmpty())
        {
            for(int i = 0;i != rows; ++i)
            {
                QPair<QString, QString> p = vecComm.takeFirst();
                QPushButton *b1 = new QPushButton(p.first);
                connect(b1, &QPushButton::clicked, this, &Vision::sendCommndInConsole);
                commandVis->setCellWidget(i, 0, b1);
                QLabel *l1 = new QLabel(p.second);
                l1->setWordWrap(true);
                commandVis->setCellWidget(i, cols - 1, l1);
            }
        }
          commandVis->resizeColumnsToContents();
          commandVis->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);       // test
          commandVis->horizontalHeader()->setStretchLastSection(true);
}

    void Vision::sendCommndInConsole()
    {
        QString co = qobject_cast<QPushButton*>(sender())->text();
        sendConsoleCommand(co.toStdString());
       // SetForegroundWindow((HWND)winId());
        SendMessage((HWND)winId(), WM_ACTIVATE, WA_ACTIVE, 0);
        SendMessage((HWND)winId(), WM_SETFOCUS, 0, 0);
    }

    void Vision::searchedCommand(const QString &text)
    {
            if(!allRowsShow(commandVis))
            {
                for(int i = 0;i != commandVis->rowCount(); ++i)
                {
                    commandVis->showRow(i);
                }
                 commandVis->update();
              }
        QRegExp reg("([A-Z0-9 -.,]*)(" + text.toLower() + ")([A-Z0-9 -.,]*)");
        findlWork(commandVis, reg, 0, rows);
        commandVis->update();
    }

