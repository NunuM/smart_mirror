#ifndef TRAFFICMODEL_H
#define TRAFFICMODEL_H

#include <QAbstractListModel>
#include "trafficmanager.h"

namespace smart {

class TrafficModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(TrafficManager * manager READ getManager WRITE setManager)

public:
    explicit TrafficModel(QObject *parent = nullptr);

    enum {
        IdRole,
        LatitudeRole,
        LongitudeRole,
        DescriptionRole,
        IsRodeClosedRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    TrafficManager *getManager() const;
    void setManager(TrafficManager *value);

private:
    TrafficManager * manager;
};

}
#endif // TRAFFICMODEL_H
