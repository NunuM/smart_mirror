#include "sensormodel.h"

SensorModel::SensorModel(QObject *parent)
    : QAbstractItemModel(parent)
{
}

QModelIndex SensorModel::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

QModelIndex SensorModel::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

int SensorModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int SensorModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

bool SensorModel::hasChildren(const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

bool SensorModel::canFetchMore(const QModelIndex &parent) const
{
    // FIXME: Implement me!
    return false;
}

void SensorModel::fetchMore(const QModelIndex &parent)
{
    // FIXME: Implement me!
}

QVariant SensorModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}

bool SensorModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
}

bool SensorModel::insertColumns(int column, int count, const QModelIndex &parent)
{
    beginInsertColumns(parent, column, column + count - 1);
    // FIXME: Implement me!
    endInsertColumns();
}

bool SensorModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endRemoveRows();
}

bool SensorModel::removeColumns(int column, int count, const QModelIndex &parent)
{
    beginRemoveColumns(parent, column, column + count - 1);
    // FIXME: Implement me!
    endRemoveColumns();
}
