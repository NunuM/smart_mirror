#include "sensormanager.h"
#include "sensor.h"

#include <QtDBus/QDBusConnection>

namespace  smart {

SensorManager::SensorManager(QObject *parent) : QObject(parent)
{
    mItems = QVector<Sensor *>();

    QDBusConnection connection = QDBusConnection::sessionBus();

    connection.registerObject(QStringLiteral("/io/smart/OSensor"), this,  QDBusConnection::ExportAllSlots);
    connection.registerService(QStringLiteral("io.smart.SSensor"));
 }

QVector<Sensor *> smart::SensorManager::items() const
{
    return mItems;
}

bool SensorManager::setItemAt(int index, Sensor * sensor)
{
    if(index < 0  || index >= mItems.size()){
        return false;
    }

    mItems[index] = sensor;

    return true;
}

bool SensorManager::appendSensor(QString name, QString unit, QVector<qreal> reading)
{
    Sensor * sensor = new Sensor(name, unit, reading);

    if(exists(name) < 0){
        emit preItemAppended();
        mItems.append(sensor);
        emit postItemAppended();
        return true;
    }

    return false;
}

bool SensorManager::addReading(QString name, qreal value)
{
    int index =  exists(name);

    if(index < 0){
        return false;
    }

    emit preItemUpdated(index);
    mItems.at(index)->newReading(value);
    emit postItemUpdated(index);

    return true;
}

bool SensorManager::removeSensor(QString name)
{
    int index =  exists(name);

    if(index < 0){
        return false;
    }

    emit preItemRemoved(index);
    mItems.removeAt(index);
    emit postItemRemoved();

    return true;
}

int SensorManager::numbersOfSensors()
{
    return mItems.size();
}

int SensorManager::exists(QString name)
{
    for(int i=0; i< mItems.size(); i++){
        if(mItems.at(i)->name() == name){
            return i;
        }
    }

    return -1;
}

}
