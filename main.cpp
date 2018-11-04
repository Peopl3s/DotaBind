#include <QApplication>
#include <QtCore>
#include <QtWidgets>
#include "qxtglobalshortcut.h"
#include "overlayback.h"
#include "steamoverlay.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OverlayBackground bg;
    SteamOverlay sOver;

    QObject::connect(&sOver,&SteamOverlay::changeVisibility,&bg,&OverlayBackground::visibility);
    QObject::connect(&bg,&OverlayBackground::doEvent,[&sOver](){sOver.activateWindow();});

    QxtGlobalShortcut *shortcut = new QxtGlobalShortcut;
    shortcut->setShortcut(QKeySequence("Shift+Space"));
    QKeyEvent key(QEvent::KeyPress,Qt::Key_Space, Qt::ShiftModifier);

    QObject::connect(shortcut, &QxtGlobalShortcut::activated,[&sOver,&key]() {
        QApplication::postEvent(&sOver,&key);
    });
    return a.exec();
}

