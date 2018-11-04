QT += core
QT -= gui
QT += widgets
QT += concurrent
TARGET = untitled6
CONFIG += console
CONFIG -= app_bundle

include("qxtglobalshortcut5/qxt.pri")

TEMPLATE = app
CONFIG += C++14
QMAKE_CXXFLAGS += -std=c++14
SOURCES += main.cpp \
    sendconsole.cpp \
    utilityfunctions.cpp \
    overlayback.cpp \
    steamoverlay.cpp \
    botsitems.cpp \
    creepsandsummons.cpp \
    dotaitems.cpp \
    general.cpp \
    heros.cpp \
    vision.cpp \
    wards.cpp

HEADERS += \
    overlayback.h \
    steamoverlay.h \
    sendconsole.h \
    dotaitems.h \
    heros.h \
    general.h \
    botsitems.h \
    creepsandsummons.h \
    vision.h \
    wards.h \
    utilityfunctions.h

