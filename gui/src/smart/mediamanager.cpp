#include "mediamanager.h"

#include <QtDBus/QDBusConnection>
#include <QStringLiteral>
#include <QJsonDocument>
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

bool MediaManager::appendMovie(QString entry)
{
    emit preItemAppended();

    auto object = QJsonDocument::fromJson(entry.toUtf8()).object();

    qDebug() << object["description"];

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
