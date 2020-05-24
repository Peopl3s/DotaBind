#include <QtWidgets>
#include <QtCore>
#include <algorithm>
#include "sendconsole.h"
#include "utilityfunctions.h"
#include <QtConcurrent>
#include <QAtomicInt>
#include <windows.h>
#include "dotaitems.h"

    DotaItems::DotaItems(QWidget *p):QWidget(p)
    {
        search = new QLineEdit;
        search->setPlaceholderText("Type word for searching. Press Enter");
        commands=new QTableWidget(rows - 1, cols);
        connect(search, &QLineEdit::returnPressed, [this](){ searchedCommand(search->text());});
        fillTable("console/items.txt", "ItemSorted");
        commands->setEditTriggers(QAbstractItemView::NoEditTriggers);
        commands->setSelectionMode(QAbstractItemView::SingleSelection);
        commands->setSelectionMode(QAbstractItemView::NoSelection);

        QVBoxLayout *v = new QVBoxLayout;
        v->setMargin(0);
        v->addWidget(search);
        v->addWidget(commands);
        QHBoxLayout *h = new QHBoxLayout;
        h->setMargin(0);
        h->addLayout(v);

        setLayout(h);
    }

    void DotaItems::fillTable(const QString &path, const QString &pathP)
    {
        commands->setHorizontalHeaderLabels(QStringList() << "Command" << "Option" << "Discribe");
        commands->verticalHeader()->hide();
        QVector<QPair<QString,QString>> vecComm = readCommandsFromFile(path, "([a-zA-Z0-9-_ ()]+);(---);([a-zA-Z0-9,.- ()]+)\\r\\n");
        QStringList pics = picLoad(pathP);
        if(!vecComm.isEmpty())
        {
            for(int i = 0;i != rows - 1; ++i)
            {
                QPair<QString, QString> p = vecComm.takeFirst();
                QPushButton *b1 = new QPushButton(p.first);
                connect(b1, &QPushButton::clicked, this, &DotaItems::sendCommndInConsole);
                commands->setCellWidget(i, 0, b1);
                QLabel *l1 = new QLabel(p.second);
                l1->setWordWrap(true);
                commands->setCellWidget(i, cols - 1, l1);

                QLabel *icon = new QLabel;
                icon->setPixmap(QPixmap(pathP + "/" + pics.at(i)));
                icon->setFixedSize(100, 40);
                icon->setAlignment(Qt::AlignCenter);
                commands->setCellWidget(i, 1, icon);

            }
        }
        commands->resizeColumnsToContents();
        commands->resizeRowsToContents();
        commands->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);        // test
        commands->horizontalHeader()->setStretchLastSection(true);
    }

    void DotaItems::sendCommndInConsole()
    {
        QString co = qobject_cast<QPushButton*>(sender())->text();
        sendConsoleCommand(co.toStdString());
        SendMessage((HWND)winId(), WM_SETFOCUS, 0, 0);
        SendMessage( (HWND)winId(), WM_ACTIVATE, WA_ACTIVE, 0);
    }

    void DotaItems::searchedCommand(const QString &text)
    {
            if(!allRowsShow(commands))
            {
                for(int i = 0;i != commands->rowCount(); ++i)
                {
                    commands->showRow(i);
                }
                 commands->update();
              }
        QRegExp reg("([A-Z0-9 -.,]*)(" + text.toLower() + ")([A-Z0-9 -.,]*)");
        findlWork(commands, reg, 0, rows - 1);
        commands->update();
    }
