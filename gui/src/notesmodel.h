#ifndef NOTESMODEL_H
#define NOTESMODEL_H

#include <QAbstractListModel>

class NotesModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit NotesModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
};

#endif // NOTESMODEL_H
