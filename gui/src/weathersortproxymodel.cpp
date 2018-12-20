#include "weathersortproxymodel.h"

#include <QVariant>
#include <QDateTime>

namespace  smart {

WeatherSortProxyModel::WeatherSortProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{

}

bool WeatherSortProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    QVariant leftData = sourceModel()->data(left);
    QVariant rightData = sourceModel()->data(right);

    if (leftData.type() == QVariant::Date) {
        return leftData.toDateTime() < rightData.toDateTime();
    }

    return false;
}

}
