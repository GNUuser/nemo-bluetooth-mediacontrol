#include <QDebug>
#include <QGuiApplication>
#include "bluetoothmediacontrol.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    BluetoothMediaControl *btControl = new BluetoothMediaControl();

    qDebug() << "start";

    return app.exec();
}
