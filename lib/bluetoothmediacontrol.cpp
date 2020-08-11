#include "bluetoothmediacontrol.h"

#include <QDBusConnectionInterface>
#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusArgument>
#include <QDebug>

BluetoothMediaControl::BluetoothMediaControl(QObject *parent)
    : QObject(parent),
      m_available(false),
      m_path(""),
      m_name(""),
      m_status("Unknow"),
      m_subtype(""),
      m_type(""),
      m_shuffle("Unknow"),
      m_repeat("Unknow"),
      m_position(0)
{
    QDBusConnection m_bus = QDBusConnection::systemBus();

    m_bus.connect("", "", "org.freedesktop.DBus.ObjectManager", "InterfacesAdded", this, SLOT(serviceAdded(QDBusObjectPath,QVariantMap)));
    m_bus.connect("", "", "org.freedesktop.DBus.ObjectManager", "InterfacesRemoved", this, SLOT(serviceRemoved(QDBusObjectPath,QStringList)));
}

void BluetoothMediaControl::serviceAdded(QDBusObjectPath object, QVariantMap interfaces)
{
    if(interfaces.firstKey() == "org.bluez.MediaPlayer1") {
        qDebug() << "MediaPlayer is added " << object.path();
        m_path = object.path();

        if(!m_available) {
            m_available = true;
            emit availableChanged(m_available);
            QDBusConnection::systemBus().connect("org.bluez",
                                                 m_path,
                                                 "org.freedesktop.DBus.Properties",
                                                 "PropertiesChanged",
                                                 this,
                                                 SLOT(propertesChanged(QString, QVariantMap, QStringList)));
        }
    }


}

void BluetoothMediaControl::serviceRemoved(QDBusObjectPath object, QStringList interfaces)
{
    Q_UNUSED(interfaces);

    if(m_available) {
        if(object.path() == m_path) {
            qDebug() << "MediaPlayer is removed " << object.path();

            m_path = "";
            m_available = false;
            emit availableChanged(m_available);
        }
    }
}

QDBusArgument &operator << (QDBusArgument &argument, const QVariant &value)
{
    switch (value.type()) {
    case QVariant::String:
        return argument << value.toString();
    case QVariant::StringList:
        return argument << value.toStringList();
    case QVariant::Int:
        return argument << value.toInt();
    case QVariant::Bool:
        return argument << value.toBool();
    case QVariant::Double:
        return argument << value.toDouble();
    default:
        if (value.userType() == qMetaTypeId<float>()) {
            return argument << value.value<float>();
        }
        return argument;
    }
}


void BluetoothMediaControl::propertesChanged(QString interface, QVariantMap changed_properties, QStringList invalidated_properties)
{
    Q_UNUSED(invalidated_properties);

    if(interface == "org.bluez.MediaPlayer1") {
        foreach (QString key, changed_properties.keys()) {
            QVariant value = changed_properties.value(key);
            qDebug() << key << ":" << value;

            if(key == "Name") {
                if(value.toString() != m_name)
                {
                    m_name = value.toString();
                    emit nameChanged(m_name);
                }
                return;
            }

            if(key == "Status") {
                if(value.toString() != m_status)
                {
                    m_status = value.toString();
                    emit statusChanged(m_status);
                }
                return;
            }

            if(key == "Subtype") {
                if(value.toString() != m_subtype)
                {
                    m_subtype = value.toString();
                    emit subtypeChanged(m_subtype);
                }
                return;
            }

            if(key == "Type") {
                if(value.toString() != m_type)
                {
                    m_type = value.toString();
                    emit typeChanged(m_type);
                }
                return;
            }

            if(key == "Repeat") {
                if(value.toString() != m_repeat)
                {
                    m_repeat = value.toString();
                    emit repeatChanged(m_repeat);
                }
                return;
            }

            if(key == "Shuffle") {
                if(value.toString() != m_shuffle)
                {
                    m_shuffle = value.toString();
                    emit shuffleChanged(m_shuffle);
                }
                return;
            }

            if(key == "Track") {
                qDebug() << value(2).value<QStringList>();
                return;
            }

            if(key == "Position") {

                if(value.toUInt() != m_position)
                {
                    m_position = value.toUInt();
                    emit positionChanged(m_position);
                }
                return;
            }

            qWarning() << "Unknow key " << key;

        }
    }
}


void BluetoothMediaControl::FastForward()
{
    if(!m_available) {
        return;
    }

    QDBusMessage msg = QDBusMessage::createMethodCall("org.bluez", m_path, "org.bluez.MediaPlayer1", "FastForward");
    QDBusConnection::systemBus().call(msg);
}

void BluetoothMediaControl::Next()
{
    if(!m_available) {
        return;
    }

    QDBusMessage msg = QDBusMessage::createMethodCall("org.bluez", m_path, "org.bluez.MediaPlayer1", "Next");
    QDBusConnection::systemBus().call(msg);
}

void BluetoothMediaControl::Pause()
{
    if(!m_available) {
        return;
    }

    QDBusMessage msg = QDBusMessage::createMethodCall("org.bluez", m_path, "org.bluez.MediaPlayer1", "Pause");
    QDBusConnection::systemBus().call(msg);
}

void BluetoothMediaControl::Play()
{
    if(!m_available) {
        return;
    }

    QDBusMessage msg = QDBusMessage::createMethodCall("org.bluez", m_path, "org.bluez.MediaPlayer1", "Play");
    QDBusConnection::systemBus().call(msg);
}

void BluetoothMediaControl::Previous()
{
    if(!m_available) {
        return;
    }

    QDBusMessage msg = QDBusMessage::createMethodCall("org.bluez", m_path, "org.bluez.MediaPlayer1", "Previous");
    QDBusConnection::systemBus().call(msg);
}

void BluetoothMediaControl::Rewind()
{
    if(!m_available) {
        return;
    }

    QDBusMessage msg = QDBusMessage::createMethodCall("org.bluez", m_path, "org.bluez.MediaPlayer1", "Previous");
    QDBusConnection::systemBus().call(msg);
}

void BluetoothMediaControl::Stop()
{
    if(!m_available) {
        return;
    }

    QDBusMessage msg = QDBusMessage::createMethodCall("org.bluez", m_path, "org.bluez.MediaPlayer1", "Stop");
    QDBusConnection::systemBus().call(msg);
}
