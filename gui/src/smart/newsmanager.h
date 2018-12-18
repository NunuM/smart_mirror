#ifndef NEWSMANAGER_H
#define NEWSMANAGER_H

#include <QObject>
#include <QJsonArray>
#include <QVariantMap>

namespace smart {

class NewsManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariantMap last READ lastInsertedNews NOTIFY lastChanged)

    Q_CLASSINFO("D-Bus Interface", "io.smart.News")

public:
    explicit NewsManager(QObject *parent = nullptr);

    QVariantMap lastInsertedNews() const;

    QJsonArray items() const;
    void setItems(const QJsonArray &items);

signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();

    void preItemUpdated(int index);
    void postItemUpdated(int index);

    void lastChanged();

public slots:
    bool appendNews(QString news);

    bool removeNews(QString title);

    bool numberOfNews();

private:
    QJsonArray mItems;
};

}

#endif // NEWSMANAGER_H
