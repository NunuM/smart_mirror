#ifndef NEWSMODEL_H
#define NEWSMODEL_H

#include <QAbstractListModel>
#include "newsmanager.h"

namespace smart {

class NewsModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(NewsManager * manager READ getManager WRITE setManager)

public:
    explicit NewsModel(QObject *parent = nullptr);

    enum {
        TitleRole,
        DescriptionRole,
        ContentRole,
        ImageRole,
        PublishRole,
        AuthorRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    NewsManager *getManager() const;
    void setManager(NewsManager *value);

private:
    NewsManager * mList;
};

}
#endif // NEWSMODEL_H
