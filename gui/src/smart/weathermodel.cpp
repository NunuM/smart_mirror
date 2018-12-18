#include "weathermodel.h"

namespace smart {

WeatherModel::WeatherModel(QObject *parent)
    : QAbstractListModel(parent), manager(nullptr)
{
}

int WeatherModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !manager)
        return 0;

    return manager->getItems().size();
}

QVariant WeatherModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !manager)
        return QVariant();

    auto theMap = manager->getItems();

    auto date = theMap.keys().at(index.row());

    auto theWeather = theMap.take(date);

    switch (role) {
    case HumidityRole:
        return QVariant(theWeather.humidity);
    case PressureRole:
        return QVariant(theWeather.pressure);
    case TempRole:
        return QVariant(theWeather.temp);
    case TempMaxRole:
        return QVariant(theWeather.tempMax);
    case TempMinRole:
        return QVariant(theWeather.tempMin);
    case DescriptionRole:
        return QVariant(theWeather.description);
    case IconRole:
        return QVariant(theWeather.icon);
    case WindDegRole:
        return QVariant(theWeather.windDeg);
    case WindSpeedRole:
        return QVariant(theWeather.windSpeed);
    case IsSetRole:
        return QVariant(theWeather.isSet);
    }

    return QVariant();
}

QHash<int, QByteArray> WeatherModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[HumidityRole] = "humidity";
    names[PressureRole] = "pressure";
    names[TempRole] = "temp";
    names[TempMaxRole] = "tempMax";
    names[TempMinRole] = "tempMin";
    names[DescriptionRole] = "description";
    names[IconRole] = "icon";
    names[WindDegRole] = "windDeg";
    names[WindSpeedRole] = "winSpeed";
    names[IsSetRole] = "isSet";
    return names;
}

WeatherManager *WeatherModel::getManager() const
{
    return manager;
}

void WeatherModel::setManager(WeatherManager *value)
{

    beginResetModel();

    if (manager)
        manager->disconnect(this);

    manager = value;

    if (manager) {
        connect(manager, &WeatherManager::preItemAppended, this, [=]() {
            const int index = manager->getItems().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(manager, &WeatherManager::postItemAppended, this, [=]() {
            endInsertRows();
        });

        connect(manager, &WeatherManager::preItemRemoved, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(manager, &WeatherManager::postItemRemoved, this, [=]() {
            endRemoveRows();
        });

    }

    endResetModel();
}

}
