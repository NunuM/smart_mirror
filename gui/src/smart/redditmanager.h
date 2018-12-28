#ifndef REDDITMANAGER_H
#define REDDITMANAGER_H

#include <QObject>
#include <QJsonArray>
#include <QVariantMap>

namespace smart {

class RedditManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariantMap last READ lastInsertedPosts NOTIFY lastChanged)

    Q_CLASSINFO("D-Bus Interface", "io.smart.Reddit")

public:
    explicit RedditManager(QObject *parent = nullptr);

    QVariantMap lastInsertedPosts() const;

    QJsonArray items() const;
    void setItems(const QJsonArray &items);
    void clearItems();

signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();

    void preItemUpdated(int index);
    void postItemUpdated(int index);

    void lastChanged();

public slots:
    bool appendRedditPosts(QString posts);
    bool clearAllRedditPosts();
    int numberOfPosts();

private:
    QJsonArray mItems;
};

}


#endif // REDDITMANAGER_H
