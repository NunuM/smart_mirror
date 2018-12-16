#ifndef SENSORMODEL_H
#define SENSORMODEL_H

#include <QAbstractListModel>
#include "sensormanager.h"

namespace smart {

class SensorModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(SensorManager * manager READ manager WRITE setManager)

public:
    explicit SensorModel(QObject *parent = nullptr);

    enum {
        NameRole,
        UnitRole,
        ReadingRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    SensorManager *manager() const;
    void setManager(SensorManager *manager);

private:
    SensorManager * mList;
};

}

#endif // SENSORMODEL_H
