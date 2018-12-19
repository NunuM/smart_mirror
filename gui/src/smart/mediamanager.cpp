#include "mediamanager.h"

#include <QtDBus/QDBusConnection>
#include <QStringLiteral>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QDebug>

namespace smart {

MediaManager::MediaManager(QObject *parent) : QObject(parent)
{
    mItems = QJsonArray();

    QDBusConnection connection = QDBusConnection::sessionBus();

    connection.registerObject(QStringLiteral("/io/smart/Media"), this,  QDBusConnection::ExportAllSlots);
    connection.registerService(QStringLiteral("io.smart.Media"));
}

QJsonArray MediaManager::items() const
{
    return mItems;
}

void MediaManager::setItems(const QJsonArray &items)
{
    mItems = items;
}

bool MediaManager::bulkMoviesInsertion(QString entry)
{
    bool hasErros = false;

    QJsonParseError error;

    auto document = QJsonDocument::fromJson(entry.toUtf8(), &error);

    if(error.error != QJsonParseError::NoError){
        qDebug() << "Json document is invalid"
                 << error.errorString();
        return false;
    }

    if(!document.isArray()){
        qDebug() << "Json document is not a object";
        return false;
    }

    auto jsonArray = document.array();

    foreach(const QJsonValue & value, jsonArray){
        auto object = value.toObject();

        if(!(object.contains(QStringLiteral("title"))
             && object.contains(QStringLiteral("plot"))
             && object.contains(QStringLiteral("poster"))
             && object.contains(QStringLiteral("genre"))
             && object.contains(QStringLiteral("actors"))
             && object.contains(QStringLiteral("imdbrating")))){

            qDebug() << "Json object with invalid keys";
            hasErros = true;
            continue;
        } else {
            emit preItemAppended();
            mItems.append(object);
            emit postItemAppended();
        }
    }

    return !hasErros;
}

bool MediaManager::appendMovie(QString entry)
{
    QJsonParseError error;

    auto document = QJsonDocument::fromJson(entry.toUtf8(), &error);

    if(error.error != QJsonParseError::NoError){
        qDebug() << "Json document is invalid"
                 << error.errorString();
        return false;
    }

    if(!document.isObject()){
        qDebug() << "Json document is not a object";
        return false;
    }

    auto object = document.object();

    if(!(object.contains(QStringLiteral("title"))
         && object.contains(QStringLiteral("plot"))
         && object.contains(QStringLiteral("poster"))
         && object.contains(QStringLiteral("genre"))
         && object.contains(QStringLiteral("actors"))
         && object.contains(QStringLiteral("imdbrating")))){

        qDebug() << "Json object with invalid keys";

        return false;
    }

    emit preItemAppended();

    mItems.append(object);

    emit postItemAppended();

    return true;
}

int MediaManager::numbersOfMovies()
{
    return mItems.size();
}

bool MediaManager::currentPlayingSong(const QString &songName)
{
    emit notifiy(1, songName);
    return true;
}

bool MediaManager::songHasStoppped()
{
    emit notifiy(1, QStringLiteral(""));
    return false;
}

}
