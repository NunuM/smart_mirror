#include "sensormanager.h"

#include <QtDBus/QDBusConnection>
#include <QJsonDocument>
#include "sensor.h"

namespace smart {

SensorManager::SensorManager(QObject *parent) : QObject(parent)
{
    QDBusConnection connection = QDBusConnection::sessionBus();

    connection.registerObject(QStringLiteral("/io/smart/OSensor"), this,  QDBusConnection::ExportAllSlots);
    connection.registerService(QStringLiteral("io.smart.SSensor"));
}

bool SensorManager::addSensor(const QString &name,const QString &unit, QVariantList readings)
{
    emit preItemAppended();

    auto json =QJsonDocument::fromVariant(readings).array();
    Sensor * sensor = new Sensor(name, unit, json);

    mSensors.append(sensor);
    emit newSensor(sensor);
    emit postItemAppended();

    return true;
}

bool SensorManager::deleteSensor(const QString &name)
{
    bool wasFound = false;

    for (int i = 0; i < mSensors.size(); ++i) {
        if (mSensors.at(i)->name() == name){

            emit preItemRemoved(i);

            mSensors.removeAt(i);

            emit postItemRemoved();

            break;
        }
    }

    return wasFound;
}

bool SensorManager::addSensorReading(const QString &name, qreal value)
{
    bool wasUpdated = false;

    for (int i = 0; i < mSensors.size(); ++i) {
        if (mSensors.at(i)->name() == name){
            auto t  = QJsonDocument::fromJson(QString("{\"name\":\"outside\",\"value\":54}").toUtf8());
            mSensors.at(i)->newReading(t.object());
            wasUpdated = true;
            break;
        }
    }

    return wasUpdated;
}

QList<Sensor *> SensorManager::sensors() const
{
    return mSensors;
}

void SensorManager::setSensors(const QList<Sensor *> &sensors)
{
    mSensors = sensors;
}
}
