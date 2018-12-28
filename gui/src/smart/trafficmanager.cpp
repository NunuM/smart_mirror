#include "trafficmanager.h"

#include <QtDBus/QDBusConnection>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QDebug>

namespace smart {

TrafficManager::TrafficManager(QObject *parent)
    : QObject(parent), mItems(QVector<Incident>())
{
    QDBusConnection connection = QDBusConnection::sessionBus();

    connection.registerObject(QStringLiteral("/io/smart/Traffic"), this,  QDBusConnection::ExportAllSlots);
    connection.registerService(QStringLiteral("io.smart.Traffic"));
}

QVector<Incident> TrafficManager::items() const
{
    return mItems;
}

void TrafficManager::setItems(const QVector<Incident> &items)
{
    mItems = items;
}

bool TrafficManager::appendTrafficIncidentsAsJsonArray(QString traffic)
{
    QJsonParseError error;

    auto document = QJsonDocument::fromJson(traffic.toUtf8(), &error);

    if(error.error != QJsonParseError::NoError){
        qDebug() << "Error in JSON format"
                 << error.errorString();

        return false;
    }

    if(!document.isArray()){
        qDebug() << "JSON passed in invalid.";

        return false;
    }

    auto jsonArray = document.array();
    bool ret = true;

    foreach (const QJsonValue & v, jsonArray)
    {
        auto object = v.toObject();

        if(!(object.contains(QStringLiteral("incidentId"))
             && object.contains(QStringLiteral("latitude"))
             && object.contains(QStringLiteral("longitude"))
             && object.contains(QStringLiteral("description"))
             && object.contains(QStringLiteral("roadClosed")))){

            qDebug() << "JSON object not contains required keys.";
            ret &=  false;

        } else {

            ret &= appendTraffic(object["incidentId"].toString(),
                    object["latitude"].toDouble(),
                    object["longitude"].toDouble(),
                    object["description"].toString(),
                    object["roadClosed"].toBool());
        }
    }

    return ret;
}

bool TrafficManager::appendTraffic(QString incidentId,
                                   qreal latitude,
                                   qreal longitude,
                                   QString description,
                                   bool isRoadClosed)
{
    if(exists(incidentId) >= 0){
        return false;
    }

    Incident incident;

    incident.incidentId = incidentId;
    incident.latitude = latitude;
    incident.longitude = longitude;
    incident.description = description;
    incident.isRoadClosed = isRoadClosed;

    emit preItemAppended();
    mItems.append(incident);
    emit postItemAppended();

    return true;
}

bool TrafficManager::removeIncident(QString incidentId)
{
    int index = exists(incidentId);

    if(index < 0){
        return false;
    }

    emit preItemRemoved(index);
    mItems.remove(index);
    emit postItemRemoved();

    return true;
}

int TrafficManager::numberOfIncidents()
{
    return mItems.size();
}

int TrafficManager::exists(const QString &id)
{
    for (int i = 0; i < mItems.size(); ++i) {
        if(mItems.at(i).incidentId == id){
            return i;
        }
    }

    return -1;
}

}
