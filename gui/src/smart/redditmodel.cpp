#include "redditmodel.h"
#include <QJsonObject>

namespace smart {

RedditModel::RedditModel(QObject *parent)
    : QAbstractListModel(parent), mList(nullptr)
{
}

int RedditModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mList)
        return 0;
    return mList->numberOfPosts();
}

QVariant RedditModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();

    auto item = mList->items().at(index.row());

    if(item.isObject()){

        auto jsonObject = item.toObject();

        switch (role) {
        case TitleRole:
            return QVariant(item["title"]);
        case SubRedditRole:
            return QVariant(item["subreddit"]);
        case ImageRole:
            return QVariant(item["urlToImage"]);
        case AuthorRole:
            return QVariant(item["author"]);
        case NumberOfUpvotesRole:
            return QVariant(item["numberOfUpvotes"]);
        }

    }
    return QVariant();
}

QHash<int, QByteArray> RedditModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[TitleRole] = "title";
    names[SubRedditRole] = "subreddit";
    names[ImageRole] = "image";
    names[AuthorRole] = "author";
    names[NumberOfUpvotesRole] = "upvotes";
    return names;
}

RedditManager *RedditModel::getManager() const
{
    return mList;
}

void RedditModel::setManager(RedditManager *value)
{
    beginResetModel();

    if (mList)
        mList->disconnect(this);

    mList = value;

    if (mList) {
        connect(mList, &RedditManager::preItemAppended, this, [=]() {
            const int index = mList->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(mList, &RedditManager::postItemAppended, this, [=]() {
            endInsertRows();
        });

        connect(mList, &RedditManager::preItemRemoved, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(mList, &RedditManager::postItemRemoved, this, [=]() {
            endRemoveRows();
        });

        connect(mList, &RedditManager::postItemUpdated, this, [=](int index) {
            emit dataChanged(this->index(index),this->index(index));
        });
    }

    endResetModel();
}

}
