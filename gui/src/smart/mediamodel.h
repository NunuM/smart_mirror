#ifndef MEDIAMODEL_H
#define MEDIAMODEL_H

#include <QAbstractListModel>
#include "mediamanager.h"

namespace smart {

class MediaModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(MediaManager * manager READ manager WRITE setManager)

public:
    explicit MediaModel(QObject *parent = nullptr);

    enum {
        TitleRole,
        PlotRole,
        GenreRole,
        ActorRole,
        PosterRole,
        RatingRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    MediaManager *manager() const;
    void setManager(MediaManager *value);

private:
    MediaManager * mList;
};

}

#endif // MEDIAMODEL_H
