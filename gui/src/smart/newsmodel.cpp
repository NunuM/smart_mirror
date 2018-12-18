#include "newsmodel.h"
#include <QJsonObject>

namespace smart {

NewsModel::NewsModel(QObject *parent)
    : QAbstractListModel(parent), mList(nullptr)
{
}

int NewsModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mList)
        return 0;

    return mList->numberOfNews();
}

QVariant NewsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();

    auto item = mList->items().at(index.row());

    if(item.isObject()){

        auto jsonObject = item.toObject();

        switch (role) {
        case TitleRole:
            return QVariant(item["title"]);
        case DescriptionRole:
            return QVariant(item["description"]);
        case ContentRole:
            return QVariant(item["content"]);
        case ImageRole:
            return QVariant(item["urlToImage"]);
        case PublishRole:
            return QVariant(item["publishedAt"]);
        case AuthorRole:
            return QVariant(item["author"]);
        }

    }
    return QVariant();
}

QHash<int, QByteArray> NewsModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[TitleRole] = "title";
    names[DescriptionRole] = "description";
    names[ContentRole] = "content";
    names[ImageRole] = "image";
    names[PublishRole] = "publish";
    names[AuthorRole] = "author";
    return names;
}

NewsManager *NewsModel::getManager() const
{
    return mList;
}

void NewsModel::setManager(NewsManager *value)
{
    beginResetModel();

    if (mList)
        mList->disconnect(this);

    mList = value;

    if (mList) {
        connect(mList, &NewsManager::preItemAppended, this, [=]() {
            const int index = mList->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(mList, &NewsManager::postItemAppended, this, [=]() {
            endInsertRows();
        });

        connect(mList, &NewsManager::preItemRemoved, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(mList, &NewsManager::postItemRemoved, this, [=]() {
            endRemoveRows();
        });

        connect(mList, &NewsManager::postItemUpdated, this, [=](int index) {
            emit dataChanged(this->index(index),this->index(index));
        });
    }

    endResetModel();
}

}
