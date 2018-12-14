#ifndef SENSORMANAGER_H
#define SENSORMANAGER_H

#include <QObject>
#include <QVariantList>
#include <QList>

namespace smart {

class Sensor;

class SensorManager : public QObject
{
    Q_OBJECT

    Q_CLASSINFO("D-Bus Interface", "io.smart.Sensor")

public:
    explicit SensorManager(QObject *parent = nullptr);

    QList<Sensor *> sensors() const;
    void setSensors(const QList<Sensor *> &sensors);
    QList<QObject *> * listOfSensors();


signals:
    void newSensor(const Sensor * sensor);
    void removeSensor(const Sensor * sensor);

    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();

public slots:
    bool addSensor(const QString &name, const QString &unit, QVariantList readings);
    bool deleteSensor(const QString &name);
    bool addSensorReading(const QString &name, qreal value);

private:
    QList<Sensor*> mSensors;
};

}

#endif // SENSORMANAGER_H
