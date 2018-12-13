#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>
#include <QString>
#include <QVariantList>
#include <QJsonArray>
#include <QJsonObject>

namespace smart {

class Sensor : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(qreal lastReading READ lastReading NOTIFY readingChanged)
    Q_PROPERTY(QVariantList olderReadings READ olderReadings)

public:
    explicit Sensor(QObject *parent = nullptr);
    Sensor(QString name, QJsonArray readings, QObject *parent= nullptr);

    QString name() const;
    void setName(const QString &name);
    qreal lastReading();
    QVariantList olderReadings();

    void newReading(const QJsonObject &newReading);

signals:
    void nameChanged();
    void readingChanged(qreal newReading);

public slots:

private:
    QString mName;
    QJsonArray mReadings;
};

}

#endif // SENSOR_H
