TEMPLATE = app
TARGET = test

SOURCES += \
    main.cpp

QT += dbus gui

INCLUDEPATH += ../lib
LIBS += -L../lib -lnemo-bluetooth-mediacontrol
