#ifndef WEATHERMANAGER_H
#define WEATHERMANAGER_H

#include <QObject>
#include <QDate>
#include <QMap>

namespace smart {

struct Weather {
    qreal humidity;
    qreal pressure;
    qreal temp;
    qreal tempMax;
    qreal tempMin;
    QString description;
    QString icon;
    qreal windDeg;
    qreal windSpeed;
    bool isSet;
};

class WeatherManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Weather today READ todayWeather)
    Q_PROPERTY(Weather tomorrow READ tomorrowWeather)

    Q_CLASSINFO("D-Bus Interface", "io.smart.Weather")

public:
    explicit WeatherManager(QObject *parent = nullptr);

    QMap<QDate, Weather> getItems() const;
    void setItems(const QMap<QDate, Weather> &items);

    Weather todayWeather() const;
    Weather tomorrowWeather() const;

signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();

public slots:
    bool appendWeather(QString date,
                       qreal humidity,
                       qreal pressure,
                       qreal temp,
                       qreal tempMax,
                       qreal tempMin,
                       QString description,
                       QString icon,
                       qreal windDeg,
                       qreal windSpeed);

    bool removeWeather(QString date);

private:
    QMap<QDate, Weather> mItems;

    Weather getWeatherForDate(const QDate &day) const;
};

}

#endif // WEATHERMANAGER_H
