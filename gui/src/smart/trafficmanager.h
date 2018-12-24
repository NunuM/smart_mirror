#ifndef TRAFFICMANAGER_H
#define TRAFFICMANAGER_H

#include <QObject>
#include <QVector>

namespace smart {

struct Incident {
    QString incidentId;
    qreal latitude;
    qreal longitude;
    QString description;
    bool isRoadClosed;
};

class TrafficManager : public QObject
{
    Q_OBJECT

    Q_CLASSINFO("D-Bus Interface", "io.smart.Traffic")

public:
    explicit TrafficManager(QObject *parent = nullptr);

    QVector<Incident> items() const;
    void setItems(const QVector<Incident> &items);

signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();

    void preItemUpdated(int index);
    void postItemUpdated(int index);

public slots:
    bool appendTrafficIncidentsAsJsonArray(QString traffic);
    bool appendTraffic(QString incidentId,
                       qreal latitude,
                       qreal longitude,
                       QString description,
                       bool isRoadClosed);

    bool removeIncident(QString incidentId);
    int numberOfIncidents();

private:
    QVector<Incident> mItems;

    int exists(const QString &id);

};

}

#endif // TRAFFICMANAGER_H
