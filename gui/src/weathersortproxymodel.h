#ifndef WEATHERSORTPROXYMODEL_H
#define WEATHERSORTPROXYMODEL_H

#include <QSortFilterProxyModel>

namespace smart {

class WeatherSortProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit WeatherSortProxyModel(QObject *parent = nullptr);


protected:
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;

};

}

#endif // WEATHERSORTPROXYMODEL_H
