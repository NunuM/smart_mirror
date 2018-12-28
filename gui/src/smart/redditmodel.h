#ifndef REDDITMODEL_H
#define REDDITMODEL_H

#include "QAbstractListModel"
#include "redditmanager.h"
namespace smart {

class RedditModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(RedditManager * manager READ getManager WRITE setManager)

public:
    explicit RedditModel(QObject *parent = nullptr);

    enum {
        TitleRole,
        SubRedditRole,
        ImageRole,
        AuthorRole,
        NumberOfUpvotesRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    RedditManager *getManager() const;
    void setManager(RedditManager *value);

private:
    RedditManager * mList;
};

}


#endif // REDDITMODEL_H
