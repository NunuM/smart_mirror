#include "sensormodel.h"

#include "sensor.h"

namespace smart {

SensorModel::SensorModel(QObject *parent)
    : QAbstractListModel(parent), mList(nullptr)
{

}

int SensorModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() || !mList)
        return 0;

    return mList->numbersOfSensors();
}

QVariant SensorModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();

    const Sensor * item = mList->items().at(index.row());
    switch (role) {
    case NameRole:
        return QVariant(item->name());
    case UnitRole:
        return QVariant(item->unit());
    case ReadingRole:
        return QVariant(item->lastReading());
    }

    return QVariant();
}

Qt::ItemFlags SensorModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsSelectable;
}

QHash<int, QByteArray> SensorModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[NameRole] = "name";
    names[UnitRole] = "unit";
    names[ReadingRole] = "reading";
    return names;
}

SensorManager *SensorModel::manager() const
{
    return mList;
}

void SensorModel::setManager(SensorManager *manager)
{
    beginResetModel();

    if (mList)
        mList->disconnect(this);

    mList = manager;

    if (mList) {
        connect(mList, &SensorManager::preItemAppended, this, [=]() {
            const int index = mList->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(mList, &SensorManager::postItemAppended, this, [=]() {
            endInsertRows();
        });

        connect(mList, &SensorManager::preItemRemoved, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(mList, &SensorManager::postItemRemoved, this, [=]() {
            endRemoveRows();
        });

        connect(mList, &SensorManager::postItemUpdated, this, [=](int index) {
            emit dataChanged(this->index(index),this->index(index));
        });
    }

    endResetModel();
}


}
