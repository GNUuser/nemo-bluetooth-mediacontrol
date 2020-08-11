TARGET = nemobluetoothmediacontrol
PLUGIN_IMPORT_PATH = org/nemomobile/bluetoothmediacontrol

TEMPLATE = lib

QT += qml dbus
QT -= gui

target.path = $$[QT_INSTALL_QML]/$$PLUGIN_IMPORT_PATH
INSTALLS += target

SOURCES += \
    plugin.cpp

INCLUDEPATH += ../lib
LIBS += -L../lib -lnemo-bluetooth-mediacontrol
