#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H

#include <QObject>

namespace smart {

class NotificationManager : public QObject
{
    Q_OBJECT

    Q_CLASSINFO("D-Bus Interface", "io.smart.Notification")

public:
    explicit NotificationManager(QObject *parent = nullptr);

signals:
    void notify(int action, QString message);

public slots:
    bool notification(int action, QString message);
};

}

#endif // NOTIFICATIONMANAGER_H
