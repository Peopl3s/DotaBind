#ifndef OVERLAYBACK
#define OVERLAYBACK
#include <QtWidgets>
#include <QtCore>
#include "steamoverlay.h"

class OverlayBackground: public QWidget
{
    Q_OBJECT
public:
    OverlayBackground(QWidget *p = 0);
    ~OverlayBackground(){}
signals:
    void doEvent();
public slots:
    void visibility(const bool &);
    virtual void setVisible(bool)override;
protected:
    void mousePressEvent(QMouseEvent *);
};
#endif // OVERLAYBACK

