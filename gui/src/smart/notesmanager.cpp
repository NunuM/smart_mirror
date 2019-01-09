#include "notesmanager.h"
#include <QDebug>
#include <QtDBus/QDBusConnection>

namespace smart {

NotesManager::NotesManager(QObject *parent) : QObject(parent)
{
    QDBusConnection connection = QDBusConnection::sessionBus();

    connection.registerObject(QStringLiteral("/io/smart/Notes"), this,  QDBusConnection::ExportAllSlots);
    connection.registerService(QStringLiteral("io.smart.Notes"));
}

bool NotesManager::appendNote(const QString &title, bool notifiable, const QString alarm)
{
    if(exists(title) >= 0){
        qDebug() << "Note already exists";

        return false;
    }

    bool state = true;
    auto date = QDateTime::fromString(alarm, QStringLiteral("yyyy-MM-dd hh:mm:ss"));
    state = date.isValid();
    if (!state){
        date = QDateTime::fromString(alarm,QStringLiteral("yyyy-MM-dd hh:mm"));
    }
    state =date.isValid();

    if(!state){
        qDebug() << "Date is not valid";
        return false;
    }

    Note note;

    note.title = title;
    note.notifiable = notifiable;
    note.alarm = date;

    emit preItemAppended();
    mItems.append(note);
    emit postItemAppended();

    return true;
}

bool NotesManager::removeNote(const QString &title)
{
    int index = exists(title);

    if(index >= 0){
        qDebug() << "Deleting note";
        emit preItemRemoved(index);
        mItems.remove(index);
        emit postItemRemoved();
        return true;
    }

    return false;
}

bool NotesManager::editNoteTitle(const QString &oldTitle, const QString &newTitle)
{
    int index = exists(oldTitle);

    if(index >= 0){
        qDebug() << "Updating note";
        emit preItemUpdated(index);
        mItems.operator[](index).title = newTitle;
        emit postItemUpdated(index);
        return true;
    }

    return false;
}

bool NotesManager::editNoteAlarm(const QString &title, const QString &alarm)
{
    int index = exists(title);

    if(index >= 0){
        qDebug() << "Updating note";

        auto date = QDateTime::fromString(alarm, QStringLiteral("yyyy-MM-dd hh:mm"));

        if(!date.isValid()){
            qDebug() << "Date is not valid";
            return false;
        }

        emit preItemUpdated(index);
        mItems.operator[](index).alarm = date;
        emit postItemUpdated(index);
        return true;
    }

    return false;
}

int NotesManager::numbersOfNotes()
{
    return mItems.size();
}

QVector<Note> NotesManager::items() const
{
    return mItems;
}

void NotesManager::setItems(const QVector<Note> &items)
{
    mItems = items;
}

bool NotesManager::setNoteAt(int index, const Note &note)
{
    if (index < 0 || index >= mItems.size())
            return false;

        auto oldItem = mItems.at(index);
        if (oldItem.notifiable == note.notifiable)
            return false;

        mItems[index] = note;
        return true;
}

int NotesManager::exists(const QString &title)
{
    int index = -1;

    for(int i=0; i < mItems.size(); i++){
        if(mItems.at(i).title == title){
            return i;
        }
    }

    return index;
}

}
