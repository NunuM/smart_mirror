#include "notesmodel.h"

#include <QDebug>

namespace  smart {

NotesModel::NotesModel(QObject *parent)
    : QAbstractListModel(parent), manager(nullptr)
{
}

int NotesModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() || !manager)
        return 0;

    return manager->numbersOfNotes();
}

QVariant NotesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !manager)
        return QVariant();

    auto note = manager->items().at(index.row());

    switch (role) {
    case TitleRole:
        return QVariant(note.title);
    case NotifiableRole:
        return QVariant(note.notifiable);
    case DateTimeRole:
        return  QVariant(note.alarm.toString(Qt::ISODate));
    }

    return QVariant();
}

bool NotesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!manager)
        return false;

    auto item = manager->items().at(index.row());
    switch (role) {
    case NotifiableRole:
        item.notifiable = value.toBool();
        break;
    }

    if (manager->setNoteAt(index.row(), item)) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }

    return false;
}

Qt::ItemFlags NotesModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> NotesModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[TitleRole] = "title";
    names[NotifiableRole] = "notifiable";
    names[DateTimeRole] = "alarm";
    return names;
}

NotesManager *NotesModel::getManager() const
{
    return manager;
}

void NotesModel::setManager(NotesManager *value)
{
    beginResetModel();

    if (manager)
        manager->disconnect(this);

    manager = value;

    if (manager) {
        connect(manager, &NotesManager::preItemAppended, this, [=]() {
            const int index = manager->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(manager, &NotesManager::postItemAppended, this, [=]() {
            endInsertRows();
        });

        connect(manager, &NotesManager::preItemRemoved, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(manager, &NotesManager::postItemRemoved, this, [=]() {
            endRemoveRows();
        });

        connect(manager, &NotesManager::postItemUpdated, this, [=](int index) {
            emit dataChanged(this->index(index),this->index(index));
        });
    }

    endResetModel();
}
}
