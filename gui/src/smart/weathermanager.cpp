#include "weathermanager.h"
#include <QDebug>
#include <QtDBus/QDBusConnection>

namespace smart {

WeatherManager::WeatherManager(QObject *parent)
    : QObject(parent), mItems(QMap<QDate, Weather>())
{
    QDBusConnection connection = QDBusConnection::sessionBus();

    connection.registerObject(QStringLiteral("/io/smart/Weather"), this,  QDBusConnection::ExportAllSlots);
    connection.registerService(QStringLiteral("io.smart.Weather"));
}

bool smart::WeatherManager::appendWeather(QString date,
                                          qreal humidity,
                                          qreal pressure,
                                          qreal temp,
                                          qreal tempMax,
                                          qreal tempMin,
                                          QString description,
                                          QString icon,
                                          qreal windDeg,
                                          qreal windSpeed)
{
    QDate theDate = QDate::fromString(date, "yyyy-MM-dd");

    if(!theDate.isValid()){
        qDebug() << "Invalid date";
        return false;
    }

    if(mItems.contains(theDate)){
        return false;
    }

    Weather weather;

    weather.humidity = humidity;
    weather.pressure = pressure;
    weather.temp = temp;
    weather.tempMax = tempMax;
    weather.tempMin = tempMin;
    weather.description = description;
    weather.windDeg = windDeg;
    weather.icon = icon;
    weather.windSpeed = windSpeed;
    weather.isSet = true;

    emit preItemAppended();
    mItems.insert(theDate, weather);
    emit postItemAppended();

    return true;
}

bool WeatherManager::removeWeather(QString date)
{
    QDate theDate = QDate::fromString(date, "yyyy-MM-dd");

    if(!theDate.isValid()){
        qDebug() << "Invalid date";
        return false;
    }

    if(mItems.contains(theDate)){
        int index  = mItems.keys().indexOf(theDate);
        emit preItemRemoved(index);
        mItems.remove(theDate);
        emit postItemRemoved();
        return true;
    }

    return false;
}

Weather WeatherManager::todayWeather() const
{
    QDate d = QDate::currentDate();
    return getWeatherForDate(d);
}

Weather WeatherManager::tomorrowWeather() const
{
    QDate d = QDate::currentDate();
    return getWeatherForDate(d.addDays(1));
}

QMap<QDate, Weather> WeatherManager::getItems() const
{
    return mItems;
}

void WeatherManager::setItems(const QMap<QDate, Weather> &items)
{
    mItems = items;
}

Weather WeatherManager::getWeatherForDate(const QDate &day) const
{
    if(mItems.contains(day)){
        return mItems[day];
    }

    Weather weather;

    weather.description = "Not avaliable";
    weather.isSet = false;

    return weather;
}

}
