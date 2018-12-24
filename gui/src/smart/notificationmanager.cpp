#include "notificationmanager.h"

#include <QtDBus/QDBusConnection>

namespace smart {

NotificationManager::NotificationManager(QObject *parent) : QObject(parent)
{
    QDBusConnection connection = QDBusConnection::sessionBus();

    connection.registerObject(QStringLiteral("/io/smart/Notification"), this,  QDBusConnection::ExportAllSlots);
    connection.registerService(QStringLiteral("io.smart.Notification"));
}

bool NotificationManager::notification(int action, QString message)
{
    emit notify(action, message);

    return true;
}

}
