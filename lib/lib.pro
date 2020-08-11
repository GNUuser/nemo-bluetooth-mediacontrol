TARGET = nemo-bluetooth-mediacontrol
TEMPLATE = lib

QT += dbus
QT -= gui

target.path = $$[QT_INSTALL_LIBS]

headers.files = $$PUBLIC_HEADERS
headers.path = $$INSTALL_ROOT$$PREFIX/include/$TARGET

INSTALLS += target headers

HEADERS += \
    bluetoothmediacontrol.h

SOURCES += \
    bluetoothmediacontrol.cpp
