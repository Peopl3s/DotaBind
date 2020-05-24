#ifndef STEAMOVERLAY
#define STEAMOVERLAY
#include <QtWidgets>
#include <QtCore>
#include "dotaitems.h"
#include "heros.h"
#include "botsitems.h"
#include "creepsandsummons.h"
#include "general.h"
#include "vision.h"
#include "wards.h"
#include <windows.h>

class SteamOverlay: public QWidget
{
    Q_OBJECT
public:
   SteamOverlay(QWidget *p = 0);
    ~SteamOverlay(){}
public slots:
    void visibility(const bool &);
    void changeTab(QListWidgetItem *);
protected:
    bool event(QEvent *)override;
signals:
    void changeVisibility(bool);
private:
    bool visible {false};
    QListWidget *listMenu;
    QStackedWidget *ativateTab;
    DotaItems *dotaItem;
    Heros *heros;
    General *general;
    Wards *wards;
    Vision *vision;
    BotsItems *botsItems;
    Creeps_And_Summons *creepSummon;
    QMap<QString, int> listItems{{"General", 0}, {"Items", 1}, {"Heros", 2}, {"BotsItems", 3},
                                {"Creeps and summons", 4},{"Vision and creeps spawn", 5},{"Wards", 6}};
};
#endif // STEAMOVERLAY

