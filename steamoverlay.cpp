#include <QtWidgets>
#include <QtCore>
#include "steamoverlay.h"
#include "dotaitems.h"
#include "heros.h"
#include "botsitems.h"
#include "creepsandsummons.h"
#include "general.h"
#include "vision.h"
#include "wards.h"
#include <windows.h>


  SteamOverlay::SteamOverlay::SteamOverlay(QWidget *p): QWidget(p)
    {
       QRect screenGeometry = QApplication::desktop() -> screenGeometry();
       resize(screenGeometry.width() * 0.62, screenGeometry.height() * 0.56);
       int x = (screenGeometry.width() - width()) / 2;
       int y = (screenGeometry.height() - height()) - (screenGeometry.height() * 0.04);
       move(x, y);

       setAttribute(Qt::WA_TranslucentBackground);
       SetForegroundWindow((HWND)winId());
       Qt::WindowFlags flags = this -> windowFlags();
       flags = flags & ~Qt::WindowMinimizeButtonHint;
       this -> setWindowFlags(flags | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint|  Qt::Tool);
       // setWindowFlags(Qt::WindowStaysOnTopHint);

       dotaItem = new DotaItems();
       heros = new Heros();
       listMenu = new QListWidget();
       wards = new Wards();
       creepSummon = new Creeps_And_Summons();
       vision = new Vision();
       botsItems = new BotsItems();
       general = new General();
       ativateTab = new QStackedWidget();

      // ativateTab->setMaximumWidth(790);
       foreach(QString str, QStringList() << "General" << "Items" << "Heros" << "BotsItems" << "Creeps and summons" << "Vision and creeps spawn" << "Wards")
          {
              QListWidgetItem *pitem = new QListWidgetItem(QIcon("item.png"), str, listMenu);
              pitem->setTextAlignment(Qt::AlignCenter);
              pitem->setFont(QFont("Times", 10, QFont::Bold));
              Q_UNUSED(pitem)
          }

       setQss(listMenu, "qss/listview.qss");
       listMenu->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
       listMenu->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
       listMenu->setMaximumWidth(width() * 0.21);

       ativateTab->addWidget(general);
       ativateTab->addWidget(dotaItem);
       ativateTab->addWidget(heros);
       ativateTab->addWidget(botsItems);
       ativateTab->addWidget(creepSummon);
       ativateTab->addWidget(vision);
       ativateTab->addWidget(wards);
       ativateTab->setCurrentIndex(0);

       listMenu->setCurrentRow(0);

       connect(listMenu,&QListWidget::itemClicked,this,&SteamOverlay::changeTab);

       QHBoxLayout *h = new QHBoxLayout;
       h->addWidget(listMenu);
       h->addWidget(ativateTab);

       setLayout(h);
       setQss(this, "qss/generalstyle.qss");
    }


    void SteamOverlay::visibility(const bool &ex)
    {
       if(isDota())
       {
           //qDebug()<<"Dota";
           setVisible(ex);
           visible = ex;
       }
    }

    void SteamOverlay::changeTab(QListWidgetItem *item)
    {
       QString widgetname = item->text();

       // qDebug()<<listitems[widgetname];

        ativateTab->setCurrentIndex(listItems[widgetname]);
    }

    bool SteamOverlay::event(QEvent *pe)
    {
        if (pe->type() == QEvent::KeyPress)
        {
            if(isDota())
            {
                if (static_cast<QKeyEvent*>(pe)->key() == Qt::Key_Space && static_cast<QKeyEvent*>(pe)->modifiers() & Qt::ShiftModifier)
                {
                   //qDebug()<<"xyi"<<"\n";

                     if(visible)
                     {
                              //qDebug()<<"visible TRUE"<<"\n";
                              emit changeVisibility(false);
                              visibility(false);

                      } else
                     {
                          //qDebug()<<"visible false"<<"\n";
                          emit changeVisibility(true);
                          visibility(true);
                     }
              return true;
                }
            }
        }
        return QWidget::event(pe);
    }


