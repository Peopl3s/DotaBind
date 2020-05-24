#include <QtWidgets>
#include <QtCore>
#include <algorithm>
#include "sendconsole.h"
#include "utilityfunctions.h"
#include <windows.h>
#include "heros.h"

    Heros::Heros(QWidget *p):QWidget(p)
    {
        validator = new QIntValidator(1, 25);
        searchHero = new QLineEdit;
        searchHero->setPlaceholderText("Type word for searching. Press Enter");
        lvl = new QLineEdit("1");
        lvl->setValidator(validator);
        commandsH = new QTableWidget(rows,cols);
        fraction = new QLabel("Enemy or neutral hero: ");
        fraction->setAlignment(Qt::AlignCenter);
        fraction->setStyleSheet("QLabel{background-color:black; color:white;}");
        enemy = new QRadioButton("Enemy");
        enemy->setChecked(true);
        setQss(enemy, "qss/radio.qss");
        neutral = new QRadioButton("Neutral");
        setQss(neutral, "qss/radio.qss");

        connect(searchHero, &QLineEdit::returnPressed, [this](){ searchedCommand( searchHero->text());});
        fillTable("console/heros.txt","Heros");
        commandsH->setEditTriggers(QAbstractItemView::NoEditTriggers);
        commandsH->setSelectionMode(QAbstractItemView::SingleSelection);
        commandsH->setSelectionMode(QAbstractItemView::NoSelection);

        QVBoxLayout *v = new QVBoxLayout;
        v->setMargin(0);
        v->addWidget(searchHero);

        QHBoxLayout *eN = new QHBoxLayout;
        eN->addWidget(fraction);
        eN->setSpacing(0);
        eN->addWidget(enemy);
        eN->addWidget(neutral);
        v->addLayout(eN);
        v->addWidget(commandsH);

        QHBoxLayout *h = new QHBoxLayout;
        h->setMargin(0);
        h->addLayout(v);

        setLayout(h);
        setQss(this,"qss/generalstyle.qss");
    }


    void Heros::fillTable(const QString &pathC,const QString &pathP )
    {
        commandsH->setHorizontalHeaderLabels(QStringList() << "Command" << "Option" << "Discribe");
        commandsH->verticalHeader()->hide();
        QVector<QPair<QString, QString>> vecComm=readCommandsFromFile(pathC, "([a-z-_ ]+)\\;(---)\\;([a-zA-Z,.- ]+)\\r\\n");
        QStringList pics = picLoad(pathP);
        //qDebug()<<vecComm.size();
        if(!vecComm.isEmpty())
        {
            for(int i = 0;i != rows; ++i)
            {
                QPair<QString,QString> p = vecComm.takeFirst();
                QPushButton *b1 = new QPushButton(p.first);
                b1->setMinimumHeight(35);
                connect(b1, &QPushButton::clicked, this, &Heros::sendCommndInConsole);
                commandsH->setCellWidget(i, 0, b1);
                QLabel *l1 = new QLabel(p.second);
                l1->setWordWrap(true);
                commandsH->setCellWidget(i, cols - 1, l1);

               if(i>0 && i <= pics.size())
               {
                    QLabel *icon = new QLabel;
                    icon->setPixmap(QPixmap(pathP + "/" + pics.at(i - 1)));
                    icon->setFixedSize(100, 35);
                    icon->setAlignment(Qt::AlignCenter);
                    commandsH->setCellWidget(i, 1, icon);
                }
            }

        }

        commandsH->setCellWidget(0, 1, lvl);
        commandsH->resizeColumnsToContents();
        commandsH->resizeRowsToContents();
        commandsH->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);        // test
        commandsH->horizontalHeader()->setStretchLastSection(true);
    }

    void Heros::sendCommndInConsole()
    {

        QString co = qobject_cast<QPushButton*>(sender())->text();
        if(co == "-levelbots")
        {
            co += " " + lvl->text();
        }
        if(co.indexOf("-createhero") != -1)
        {
            if(enemy->isChecked())
            {
                co += " enemy";

            } else  co += " neutral";
        }

        qDebug()<<"Command: "<<co<<"\n";
        sendConsoleCommand(co.toStdString());
        SendMessage((HWND)winId(), WM_ACTIVATE, WA_ACTIVE, 0);
        SendMessage((HWND)winId(), WM_SETFOCUS, 0, 0);
    }

    void Heros::searchedCommand(const QString &text)
    {
            if(!allRowsShow(commandsH))
            {
                for(int i = 0;i != commandsH->rowCount(); ++i)
                {
                    commandsH->showRow(i);
                }
                commandsH->update();
              }
        QRegExp reg("([A-Z0-9 -.,]*)(" + text.toLower() + ")([A-Z0-9 -.,]*)");
        findlWork(commandsH, reg, 0, rows);
        commandsH->update();
    }
