#include <QtWidgets>
#include <QtCore>
#include "steamoverlay.h"
#include "overlayback.h"

    OverlayBackground::OverlayBackground(QWidget *p): QWidget(p)
    {
        setWindowFlags(Qt::FramelessWindowHint);
        setWindowState(Qt::WindowFullScreen);
        setWindowOpacity(0.5);
        setStyleSheet("OverlayBackground{background-color:black;}");
        setFocusPolicy(Qt::FocusPolicy::NoFocus);
        SetForegroundWindow((HWND)winId());
        Qt::WindowFlags flags = this -> windowFlags();
        flags = flags & ~Qt::WindowMinimizeButtonHint;
        this -> setWindowFlags(flags | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
    }


    void OverlayBackground::visibility(const bool &ex)
    {
       setVisible(ex);
    }
    void OverlayBackground::setVisible(bool v)
    {
        //qDebug()<<"SV";
        //SteamOverlay *sv=(SteamOverlay *)sender();
        QWidget::setVisible(v);
    }

    void OverlayBackground::mousePressEvent(QMouseEvent *e)
    {
        emit doEvent();
    }

