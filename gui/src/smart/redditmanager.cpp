#include "redditmanager.h"

#include <QtDBus/QDBusConnection>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QVariant>
#include <QDebug>

namespace smart{

RedditManager::RedditManager(QObject *parent)
    : QObject(parent), mItems(QJsonArray())
{
    QDBusConnection connection = QDBusConnection::sessionBus();

    connection.registerObject(QStringLiteral("/io/smart/Reddit"), this,  QDBusConnection::ExportAllSlots);
    connection.registerService(QStringLiteral("io.smart.Reddit"));
}

QVariantMap RedditManager::lastInsertedPosts() const
{
    QVariantMap map;

    if(mItems.isEmpty()){
        return map;
    }

    auto lastItem = mItems.last().toObject();

    map.insert(QStringLiteral("title"), QVariant(lastItem["title"]));
    map.insert(QStringLiteral("image"), QVariant(lastItem["image"]));
    map.insert(QStringLiteral("subreddit"), QVariant(lastItem["subrredit"]));
    map.insert(QStringLiteral("author"),QVariant(lastItem["author"]));
    map.insert(QStringLiteral("upvotes"),QVariant(lastItem["upvotes"]));
    return map;
}

bool smart::RedditManager::appendRedditPosts(QString posts)
{
    QJsonParseError error;

    auto document = QJsonDocument::fromJson(posts.toUtf8(), &error);

    if(error.error != QJsonParseError::NoError){
        qDebug() << "Error in JSON format"
                 << error.errorString();

        return false;
    }


    if(!document.isArray()){
        qDebug() << "JSON passed in invalid.";

        return false;
    }

    auto jsonArr = document.array();
    bool retValue = true;

    foreach (const QJsonValue & v, jsonArr)
    {
        auto object = v.toObject();
        if(!(object.contains(QStringLiteral("title"))
             && object.contains(QStringLiteral("urlToImage"))
             && object.contains(QStringLiteral("subreddit"))
             && object.contains(QStringLiteral("author")))
             && object.contains(QStringLiteral("numberOfUpvotes"))   ){

            qDebug() << "JSON object not contains required keys.";
            retValue = false;
            break;
        }

        emit preItemAppended();

        mItems.append(object);

        emit postItemAppended();
    }

    return retValue;
}

bool RedditManager::clearAllRedditPosts(){
    for (int i = 0; i < mItems.size(); i++) {
            emit preItemRemoved(i);
            mItems.removeAt(i);
            emit postItemRemoved();
    }
    return true;
}

int RedditManager::numberOfPosts(){
    return mItems.size();
}

QJsonArray RedditManager::items() const
{
    return mItems;
}

void RedditManager::setItems(const QJsonArray &items)
{
    mItems = items;
}

}
