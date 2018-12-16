#ifndef MEDIAMANAGER_H
#define MEDIAMANAGER_H

#include <QObject>
#include <QJsonArray>
#include <QJsonObject>

namespace smart {

class MediaManager : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "io.smart.Media")

public:
    explicit MediaManager(QObject *parent = nullptr);

    QJsonArray items() const;

    void setItems(const QJsonArray &items);

signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();

    void preItemUpdated(int index);
    void postItemUpdated(int index);

    void notifiy(int action, QString name);

public slots:
    bool appendMovie(QString entry);
    int  numbersOfMovies();

    bool currentPlayingSong(const QString &songName);
    bool songHasStoppped();

private:
    QJsonArray mItems;
};

}
#endif // MEDIAMANAGER_H
