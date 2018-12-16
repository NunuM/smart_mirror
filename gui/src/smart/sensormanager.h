#ifndef SENSORMANAGER_H
#define SENSORMANAGER_H

#include <QObject>
#include <QVector>

namespace smart {

class Sensor;

class SensorManager : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "io.smart.Sensor")

public:
    explicit SensorManager(QObject *parent = nullptr);

    QVector<Sensor *> items() const;

    bool setItemAt(int index, Sensor * sensor);

signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();

    void preItemUpdated(int index);
    void postItemUpdated(int index);

public slots:
    bool appendSensor(QString name, QString unit, QVector<qreal> reading);
    bool addReading(QString name, qreal value);

    bool removeSensor(QString name);
    int  numbersOfSensors();

private:
    QVector<Sensor *> mItems;

    int exists(QString name);

};

}
#endif // SENSORMANAGER_H
