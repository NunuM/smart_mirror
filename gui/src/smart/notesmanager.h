#ifndef NOTESMANAGER_H
#define NOTESMANAGER_H

#include <QObject>
#include <QVector>
#include <QDateTime>

namespace smart {

struct Note
{
    bool notifiable;
    QString title;
    QDateTime alarm;
};

class NotesManager : public QObject
{
    Q_OBJECT
public:
    explicit NotesManager(QObject *parent = nullptr);


    QVector<Note> items() const;
    void setItems(const QVector<Note> &items);

signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();

    void preItemUpdated(int index);
    void postItemUpdated(int index);

public slots:
    bool appendNote(const QString &title,bool notifiable, const QString alarm);
    bool removeNote(const QString &title);

    bool editNoteTitle(const QString &oldTitle, const QString &newTitle);
    bool editNoteAlarm(const QString &title, const QString &alarm);

private:
    QVector<Note> mItems;

    int exists(const QString &title);
};

}
#endif // NOTESMANAGER_H
