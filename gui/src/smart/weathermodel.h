#ifndef WEATHERMODEL_H
#define WEATHERMODEL_H

#include <QAbstractListModel>
#include "weathermanager.h"

namespace smart {

class WeatherModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(WeatherManager * manager READ getManager WRITE setManager)

    Q_CLASSINFO("D-Bus Interface", "io.smart.Weather")

public:
    explicit WeatherModel(QObject *parent = nullptr);

    enum{
        HumidityRole,
        PressureRole,
        TempRole,
        TempMaxRole,
        TempMinRole,
        DescriptionRole,
        IconRole,
        WindDegRole,
        WindSpeedRole,
        IsSetRole,
        DateRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    WeatherManager *getManager() const;
    void setManager(WeatherManager *value);

private:
    WeatherManager * manager;
};

}
#endif // WEATHERMODEL_H
