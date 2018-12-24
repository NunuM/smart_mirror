#include "trafficmodel.h"

namespace smart {

TrafficModel::TrafficModel(QObject *parent)
    : QAbstractListModel(parent), manager(nullptr)
{
}

int TrafficModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() || !manager)
        return 0;

    return manager->numberOfIncidents();
}

QVariant TrafficModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !manager)
        return QVariant();

    auto item = manager->items().at(index.row());

    switch (role) {
    case IdRole:
        return QVariant(item.incidentId);
    case LatitudeRole:
        return QVariant(item.latitude);
    case LongitudeRole:
        return QVariant(item.longitude);
    case DescriptionRole:
        return QVariant(item.description);
    case IsRodeClosedRole:
        return QVariant(item.isRoadClosed);
    }

    return QVariant();
}

QHash<int, QByteArray> TrafficModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[IdRole] = "uid";
    names[LatitudeRole] = "latitude";
    names[LongitudeRole] = "longitude";
    names[DescriptionRole] = "description";
    names[IsRodeClosedRole] = "isClosed";
    return names;
}

TrafficManager *TrafficModel::getManager() const
{
    return manager;
}

void TrafficModel::setManager(TrafficManager *value)
{
    beginResetModel();

    if (manager)
        manager->disconnect(this);

    manager = value;

    if (manager) {
        connect(manager, &TrafficManager::preItemAppended, this, [=]() {
            const int index = manager->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(manager, &TrafficManager::postItemAppended, this, [=]() {
            endInsertRows();
        });

        connect(manager, &TrafficManager::preItemRemoved, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(manager, &TrafficManager::postItemRemoved, this, [=]() {
            endRemoveRows();
        });

        connect(manager, &TrafficManager::postItemUpdated, this, [=](int index) {
            emit dataChanged(this->index(index),this->index(index));
        });
    }

    endResetModel();
}

}
