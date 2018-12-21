#include "weathermanager.h"
#include <QDebug>
#include <QtDBus/QDBusConnection>
#include <QVariant>

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

QVariantMap WeatherManager::todayWeather() const
{
    QDate d = QDate::currentDate();

    auto weather = getWeatherForDate(d);

    QVariantMap map;

    map["humidity"] = QVariant(weather.humidity);
    map["pressure"] = QVariant(weather.pressure);
    map["temp"] = QVariant(weather.temp);
    map["tempMax"] = QVariant(weather.tempMax);
    map["tempMin"] = QVariant(weather.tempMin);
    map["description"] = QVariant(weather.description);
    map["windDeg"] = QVariant(weather.windDeg);
    map["icon"] = QVariant(weather.icon);
    map["windSpeed"] = QVariant(weather.windSpeed);
    map["isSet"] = QVariant(weather.isSet);

    return map;
}

QVariantMap WeatherManager::tomorrowWeather() const
{
    QDate d = QDate::currentDate();
    auto weather = getWeatherForDate(d.addDays(1));

    QVariantMap map;

    map["humidity"] = QVariant(weather.humidity);
    map["pressure"] = QVariant(weather.pressure);
    map["temp"] = QVariant(weather.temp);
    map["tempMax"] = QVariant(weather.tempMax);
    map["tempMin"] = QVariant(weather.tempMin);
    map["description"] = QVariant(weather.description);
    map["windDeg"] = QVariant(weather.windDeg);
    map["icon"] = QVariant(weather.icon);
    map["windSpeed"] = QVariant(weather.windSpeed);
    map["isSet"] = QVariant(weather.isSet);

    return map;
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
    weather.humidity = 0;
    weather.pressure = 0;
    weather.temp = 0;
    weather.tempMax = 0;
    weather.tempMin = 0;
    weather.description = QStringLiteral("");
    weather.windDeg = 0;
    weather.icon = QStringLiteral("");
    weather.windSpeed = 0;
    weather.isSet = true;

    return weather;
}

}
