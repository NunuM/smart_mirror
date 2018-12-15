#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QVariantList>

namespace smart {

class Sensor : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(qreal lastReading READ lastReading NOTIFY readingChanged)
    Q_PROPERTY(QVariantList olderReadings READ olderReadings)

public:
    explicit Sensor(QObject *parent = nullptr);
    Sensor(QString name, QString unit, QObject *parent= nullptr);
    Sensor(QString name, QString unit, QVector<qreal> readings, QObject *parent= nullptr);

    QString name() const;
    void setName(const QString &name);

    qreal lastReading() const;

    QVariantList olderReadings();

    void newReading(qreal value);

    QString unit() const;
    void setUnit(const QString &unit);

signals:
    void nameChanged();
    void readingChanged(qreal newReading);

public slots:

private:
    QString mName;
    QString mUnit;
    QVector<qreal> mReadings;
};

}

#endif // SENSOR_H
