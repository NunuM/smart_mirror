#include "sensor.h"

namespace smart {
/**
 * @brief Sensor::Sensor
 * @param parent
 */
Sensor::Sensor(QObject *parent) : QObject(parent)
{

}

/**
 * @brief Sensor::Sensor
 * @param name human readable name of the sensor
 * @param readings
 * @param parent
 */
Sensor::Sensor(QString name, QString unit, QJsonArray readings, QObject *parent)
    : QObject(parent), mName(name), mUnit(unit), mReadings(readings)
{
}

/**
 * @brief Sensor::name
 * @return human readable name of the sensor
 */
QString Sensor::name() const
{
    return mName;
}

/**
 * @brief Sensor::setName
 * @param name
 */
void Sensor::setName(const QString &name)
{
    mName = name;
    emit nameChanged();
}

/**
 * @brief Sensor::lastReading
 * @return last reading value
 */
qreal Sensor::lastReading()
{
    qDebug("Reading");

    if(mReadings.size() == 0){
        return 0;
    }

    auto entry = mReadings.last();
    return entry["value"].toDouble();
}

/**
 * @brief Sensor::olderReadings
 * @return QVarianList
 */
QVariantList Sensor::olderReadings()
{
    return mReadings.toVariantList();
}

/**
 * @brief Sensor::newReading
 * @param newReading
 */
void Sensor::newReading(const QJsonObject &newReading)
{
    qDebug("New reading");
    auto value = newReading["value"].toDouble();
    mReadings.append(newReading);
    emit readingChanged(value);
}

}
