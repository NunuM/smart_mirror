#include "navigationmanager.h"
#include <QtDBus/QDBusConnection>

namespace smart {

NavigationManager::NavigationManager(QObject *parent)
    : QObject(parent), availableViews(QHash<QString,QString>())
{
}

bool NavigationManager::setApplicationsViewAsRoot()
{
    return tryToSetView(QStringLiteral("applications"));
}

bool NavigationManager::setNewsViewAsRoot()
{
    return tryToSetView(QStringLiteral("news"));
}

bool NavigationManager::setSensorsViewAsRoot()
{
    return tryToSetView(QStringLiteral("sensors"));
}

bool NavigationManager::setMediaViewAsRoot()
{
    return tryToSetView(QStringLiteral("media"));
}

bool NavigationManager::setNotesViewAsRoot()
{
    return tryToSetView(QStringLiteral("notes"));
}

bool NavigationManager::setWeatherViewAsRoot()
{
    return tryToSetView(QStringLiteral("weather"));
}

bool NavigationManager::setHomeViewAsRoot()
{
    return tryToSetView(QStringLiteral("home"));
}

bool NavigationManager::setTrafficViewAsRoot()
{
    return tryToSetView(QStringLiteral("traffic"));
}

QHash<QString, QString> NavigationManager::getAvailableViews() const
{
    return availableViews;
}

void NavigationManager::setAvailableViews(const QHash<QString, QString> &value)
{
    availableViews = value;
}

void NavigationManager::init()
{
    QDBusConnection connection = QDBusConnection::sessionBus();

    connection.registerObject(QStringLiteral("/io/smart/Navigation"), this,  QDBusConnection::ExportAllSlots);
    connection.registerService(QStringLiteral("io.smart.Navigation"));
}

bool NavigationManager::appendView(QString viewName, QString viewPath)
{
    if(availableViews.contains(viewName)){
        return false;
    }

    availableViews.insert(viewName, viewPath);

    return true;
}

bool NavigationManager::tryToSetView(const QString &key)
{
    if(availableViews.contains(key)){
        emit changeViewTo(availableViews[key]);
        return true;
    }
    return false;
}

}
