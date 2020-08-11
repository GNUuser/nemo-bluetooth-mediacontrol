#include <QtGlobal>
#include <QtQml>
#include <QQmlEngine>
#include <QQmlExtensionPlugin>

#include "bluetoothmediacontrol.h"

class NemoBluetoothMediaControlPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.nemomobile.bluetoothmediacontrol")

public:
    void initializeEngine(QQmlEngine *engine, const char *uri)
    {
        Q_UNUSED(engine)
        Q_UNUSED(uri)
    }

    void registerTypes(const char *uri)
    {
        Q_ASSERT(QLatin1String(uri) == QLatin1String("org.nemomobile.bluetoothmediacontrol"));
        qmlRegisterType<BluetoothMediaControl>(uri, 1, 0, "BluetoothMediaControl");
    }
};

#include "plugin.moc"
