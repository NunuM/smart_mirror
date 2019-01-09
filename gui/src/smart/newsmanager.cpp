#include "newsmanager.h"

#include <QtDBus/QDBusConnection>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QVariant>
#include <QDebug>

namespace smart{

NewsManager::NewsManager(QObject *parent)
    : QObject(parent), mItems(QJsonArray())
{
    QDBusConnection connection = QDBusConnection::sessionBus();

    connection.registerObject(QStringLiteral("/io/smart/News"), this,  QDBusConnection::ExportAllSlots);
    connection.registerService(QStringLiteral("io.smart.News"));
}

QVariantMap NewsManager::lastInsertedNews() const
{
    QVariantMap map;

    if(mItems.isEmpty()){

        map.insert(QStringLiteral("title"), QVariant("Nothing for the moment"));
        map.insert(QStringLiteral("image"), QVariant(""));
        map.insert(QStringLiteral("description"), QVariant("description"));

        return map;
    }

    auto lastItem = mItems.last().toObject();

    map.insert(QStringLiteral("title"), QVariant(lastItem["title"]));
    map.insert(QStringLiteral("image"), QVariant(lastItem["image"]));
    map.insert(QStringLiteral("description"), QVariant(lastItem["description"]));

    return map;
}

bool smart::NewsManager::appendNews(QString news)
{
    QJsonParseError error;

    auto document = QJsonDocument::fromJson(news.toUtf8(), &error);

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
             && object.contains(QStringLiteral("description"))
             && object.contains(QStringLiteral("content"))
             && object.contains(QStringLiteral("urlToImage"))
             && object.contains(QStringLiteral("publishedAt"))
             && object.contains(QStringLiteral("author")))){

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

bool NewsManager::removeNews(QString title)
{
    for (int i = 0; i < mItems.size(); i++) {
        if(mItems.at(i).toObject()["title"].toString().toLower() == title.toLower()){
            emit preItemRemoved(i);
            mItems.removeAt(i);
            emit postItemRemoved();
            return true;
        }
    }

    return false;
}



int NewsManager::numberOfNews()
{
    return mItems.size();
}

QJsonArray NewsManager::items() const
{
    return mItems;
}

void NewsManager::setItems(const QJsonArray &items)
{
    mItems = items;
}

}
