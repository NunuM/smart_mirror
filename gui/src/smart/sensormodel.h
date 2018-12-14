#ifndef SENSORMODEL_H
#define SENSORMODEL_H

#include <QAbstractItemModel>
#include "sensormanager.h"

class SensorModel : public QAbstractItemModel
{
    Q_OBJECT
    Q_PROPERTY(SensorManager *list READ list)

public:
    explicit SensorModel(QObject *parent = nullptr);

    enum {
        NameRole =  Qt::UserRole,
        UnitRole,
        ValueRule
    };

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    // Fetch data dynamically:
    bool hasChildren(const QModelIndex &parent = QModelIndex()) const override;

    bool canFetchMore(const QModelIndex &parent) const override;
    void fetchMore(const QModelIndex &parent) override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

    virtual QHash<int, QByteArray> roleNames() const override;

private:
};

#endif // SENSORMODEL_H
