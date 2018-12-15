#include "sensor.h"
#include <QVariant>

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
Sensor::Sensor(QString name, QString unit, QObject *parent)
    : QObject(parent), mName(name), mUnit(unit), mReadings(QVector<qreal>(10))
{
}

/**
 * @brief Sensor::Sensor
 * @param name
 * @param unit
 * @param readings
 * @param parent
 */
Sensor::Sensor(QString name, QString unit, QVector<qreal> readings, QObject *parent)
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
qreal Sensor::lastReading() const
{
    qDebug("Reading");

    if(mReadings.size() == 0){
        return 0;
    }

    return  mReadings.last();
}

/**
 * @brief Sensor::olderReadings
 * @return QVarianList
 */
QVariantList Sensor::olderReadings()
{
    QVariantList list;

    for (int i = 0; i < mReadings.size(); ++i) {
        list.append(QVariant(mReadings.at(i)));
    }

    return list;
}

/**
 * @brief Sensor::newReading
 * @param newReading
 */
void Sensor::newReading(qreal value)
{
    qDebug("New reading");
    mReadings.append(value);
    emit readingChanged(value);
}

QString Sensor::unit() const
{
    return mUnit;
}

void Sensor::setUnit(const QString &unit)
{
    mUnit = unit;
}

}
