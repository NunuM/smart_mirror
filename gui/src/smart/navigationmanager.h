#ifndef NAVIGATIONMANAGER_H
#define NAVIGATIONMANAGER_H

#include <QObject>
#include <QHash>

namespace smart {

class NavigationManager : public QObject
{
    Q_OBJECT

    Q_CLASSINFO("D-Bus Interface", "io.smart.Navigation")

public:
    explicit NavigationManager(QObject * parent=nullptr);
    NavigationManager(const QHash<QString,QString> &views, QObject * parent=nullptr);

    QHash<QString, QString> getAvailableViews() const;
    void setAvailableViews(const QHash<QString, QString> &value);

    void init();

signals:
    void changeViewTo(QString view);

public slots:
    bool appendView(QString viewName, QString viewPath);
    bool setApplicationsViewAsRoot();
    bool setNewsViewAsRoot();
    bool setSensorsViewAsRoot();
    bool setMediaViewAsRoot();
    bool setNotesViewAsRoot();
    bool setWeatherViewAsRoot();
    bool setHomeViewAsRoot();

private:
    QHash<QString,QString> availableViews;

    bool tryToSetView(const QString &key);
};

}
#endif // NAVIGATIONMANAGER_H
