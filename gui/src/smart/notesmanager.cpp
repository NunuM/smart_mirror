#include "notesmanager.h"
#include <QDebug>

namespace smart {

NotesManager::NotesManager(QObject *parent) : QObject(parent)
{

}

bool NotesManager::appendNote(const QString &title, bool notifiable, const QString alarm)
{
    if(exists(title) >= 0){
        qDebug() << "Note already exists";

        return false;
    }


    auto date = QDateTime::fromString(alarm, QStringLiteral("yyyy-MM-dd hh:mm"));

    if(!date.isValid()){
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
        mItems.takeAt(index).title = newTitle;
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
        mItems.takeAt(index).alarm = date;
        emit postItemUpdated(index);
        return true;
    }

    return false;
}

int NotesManager::exists(const QString &title)
{
    int index = -1;

    for(int i=0; i < mItems.size(); i++){
        if(mItems.at(i).title == title){
            return index;
        }
    }

    return index;
}

}
