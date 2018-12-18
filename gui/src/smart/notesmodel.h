#ifndef NOTESMODEL_H
#define NOTESMODEL_H

#include <QAbstractListModel>
#include "notesmanager.h"

namespace smart{

class NotesModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(NotesManager * manager READ getManager WRITE setManager)

public:
    explicit NotesModel(QObject *parent = nullptr);

    enum {
        TitleRole,
        NotifiableRole,
        DateTimeRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value,int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;


    virtual QHash<int, QByteArray> roleNames() const override;

    NotesManager *getManager() const;
    void setManager(NotesManager *value);

private:
    NotesManager * manager;
};

}

#endif // NOTESMODEL_H
