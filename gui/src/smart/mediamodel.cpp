#include "mediamodel.h"
#include "mediamanager.h"
#include <QJsonValue>

namespace smart {

MediaModel::MediaModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int MediaModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() || !mList)
        return 0;

    return mList->numbersOfMovies();
}

QVariant MediaModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();

    auto item = mList->items().at(index.row());

    if(item.isObject()){
        auto jsonObject = item.toObject();

        switch (role) {
        case TitleRole:
            return QVariant(jsonObject["title"]);
        case PlotRole:
            return QVariant(jsonObject["plot"]);
        case PosterRole:
            return QVariant(jsonObject["poster"]);
        case GenreRole:
            return QVariant(jsonObject["genre"]);
        case ActorRole:
            return QVariant(jsonObject["actors"]);
        case RatingRole:
            return QVariant(jsonObject["imdbrating"]);
        }
    }

    return QVariant();
}

Qt::ItemFlags MediaModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsSelectable;
}

QHash<int, QByteArray> MediaModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[TitleRole] = "title";
    names[PlotRole] = "plot";
    names[GenreRole] = "genre";
    names[ActorRole] = "actors";
    names[PosterRole] = "poster";
    names[RatingRole] = "rating";
    return names;
}

MediaManager *MediaModel::manager() const
{
    return mList;
}

void MediaModel::setManager(MediaManager *value)
{
    beginResetModel();

    if (mList)
        mList->disconnect(this);

    mList = value;

    if (mList) {
        connect(mList, &MediaManager::preItemAppended, this, [=]() {
            const int index = mList->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(mList, &MediaManager::postItemAppended, this, [=]() {
            endInsertRows();
        });

        connect(mList, &MediaManager::preItemRemoved, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(mList, &MediaManager::postItemRemoved, this, [=]() {
            endRemoveRows();
        });

        connect(mList, &MediaManager::postItemUpdated, this, [=](int index) {
            emit dataChanged(this->index(index),this->index(index));
        });
    }

    endResetModel();
}

}
