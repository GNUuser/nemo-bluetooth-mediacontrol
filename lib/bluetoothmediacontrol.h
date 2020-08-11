#ifndef BLUETOOTHMEDIACONTROL_H
#define BLUETOOTHMEDIACONTROL_H

#include <QObject>
#include <QDBusConnection>
#include <QDBusObjectPath>

class BluetoothMediaControl : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool available READ available NOTIFY availableChanged)
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(QString status READ status NOTIFY statusChanged)
    Q_PROPERTY(QString subtype READ subtype NOTIFY subtypeChanged)
    Q_PROPERTY(QString type READ type NOTIFY typeChanged)
    Q_PROPERTY(QString shuffle READ shuffle NOTIFY shuffleChanged)
    Q_PROPERTY(QString repeat READ repeat NOTIFY repeatChanged)
    Q_PROPERTY(uint position READ position NOTIFY positionChanged)

public:
    explicit BluetoothMediaControl(QObject *parent = nullptr);

    bool available(){return m_available;}
    QString name(){return m_name;}
    QString status(){return m_status;}
    QString subtype(){return m_subtype;}
    QString type(){return m_type;}
    QString shuffle() {return m_shuffle;}
    QString repeat() {return m_repeat;}
    uint position() {return m_position;}

    void FastForward();
    void Next();
    void Pause();
    void Play();
    void Previous();
    void Rewind();
    void Stop();

signals:
    void availableChanged(bool available);
    void nameChanged(QString name);
    void statusChanged(QString status);
    void subtypeChanged(QString subtype);
    void typeChanged(QString type);
    void shuffleChanged(QString shuffle);
    void repeatChanged(QString repeat);
    void positionChanged(uint position);

public slots:

private slots:
    void serviceAdded(QDBusObjectPath object, QVariantMap interfaces);
    void serviceRemoved(QDBusObjectPath object, QStringList interfaces);

    void propertesChanged(QString interface, QVariantMap changed_properties, QStringList invalidated_properties);

private:
    bool m_available;
    QString m_path;

    QString m_name;
    QString m_status;
    QString m_subtype;
    QString m_type;
    QString m_shuffle;
    QString m_repeat;
    uint m_position;
};

#endif // BLUETOOTHMEDIACONTROL_H
