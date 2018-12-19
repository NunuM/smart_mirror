/****************************************************************************
** Meta object code from reading C++ file 'notesmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../gui/src/smart/notesmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'notesmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_smart__NotesManager_t {
    QByteArrayData data[21];
    char stringdata0[259];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_smart__NotesManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_smart__NotesManager_t qt_meta_stringdata_smart__NotesManager = {
    {
QT_MOC_LITERAL(0, 0, 19), // "smart::NotesManager"
QT_MOC_LITERAL(1, 20, 15), // "D-Bus Interface"
QT_MOC_LITERAL(2, 36, 14), // "io.smart.Notes"
QT_MOC_LITERAL(3, 51, 15), // "preItemAppended"
QT_MOC_LITERAL(4, 67, 0), // ""
QT_MOC_LITERAL(5, 68, 16), // "postItemAppended"
QT_MOC_LITERAL(6, 85, 14), // "preItemRemoved"
QT_MOC_LITERAL(7, 100, 5), // "index"
QT_MOC_LITERAL(8, 106, 15), // "postItemRemoved"
QT_MOC_LITERAL(9, 122, 14), // "preItemUpdated"
QT_MOC_LITERAL(10, 137, 15), // "postItemUpdated"
QT_MOC_LITERAL(11, 153, 10), // "appendNote"
QT_MOC_LITERAL(12, 164, 5), // "title"
QT_MOC_LITERAL(13, 170, 10), // "notifiable"
QT_MOC_LITERAL(14, 181, 5), // "alarm"
QT_MOC_LITERAL(15, 187, 10), // "removeNote"
QT_MOC_LITERAL(16, 198, 13), // "editNoteTitle"
QT_MOC_LITERAL(17, 212, 8), // "oldTitle"
QT_MOC_LITERAL(18, 221, 8), // "newTitle"
QT_MOC_LITERAL(19, 230, 13), // "editNoteAlarm"
QT_MOC_LITERAL(20, 244, 14) // "numbersOfNotes"

    },
    "smart::NotesManager\0D-Bus Interface\0"
    "io.smart.Notes\0preItemAppended\0\0"
    "postItemAppended\0preItemRemoved\0index\0"
    "postItemRemoved\0preItemUpdated\0"
    "postItemUpdated\0appendNote\0title\0"
    "notifiable\0alarm\0removeNote\0editNoteTitle\0"
    "oldTitle\0newTitle\0editNoteAlarm\0"
    "numbersOfNotes"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_smart__NotesManager[] = {

 // content:
       8,       // revision
       0,       // classname
       1,   14, // classinfo
      11,   16, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // classinfo: key, value
       1,    2,

 // signals: name, argc, parameters, tag, flags
       3,    0,   71,    4, 0x06 /* Public */,
       5,    0,   72,    4, 0x06 /* Public */,
       6,    1,   73,    4, 0x06 /* Public */,
       8,    0,   76,    4, 0x06 /* Public */,
       9,    1,   77,    4, 0x06 /* Public */,
      10,    1,   80,    4, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    3,   83,    4, 0x0a /* Public */,
      15,    1,   90,    4, 0x0a /* Public */,
      16,    2,   93,    4, 0x0a /* Public */,
      19,    2,   98,    4, 0x0a /* Public */,
      20,    0,  103,    4, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,

 // slots: parameters
    QMetaType::Bool, QMetaType::QString, QMetaType::Bool, QMetaType::QString,   12,   13,   14,
    QMetaType::Bool, QMetaType::QString,   12,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString,   17,   18,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString,   12,   14,
    QMetaType::Int,

       0        // eod
};

void smart::NotesManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NotesManager *_t = static_cast<NotesManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->preItemAppended(); break;
        case 1: _t->postItemAppended(); break;
        case 2: _t->preItemRemoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->postItemRemoved(); break;
        case 4: _t->preItemUpdated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->postItemUpdated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: { bool _r = _t->appendNote((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 7: { bool _r = _t->removeNote((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 8: { bool _r = _t->editNoteTitle((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 9: { bool _r = _t->editNoteAlarm((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 10: { int _r = _t->numbersOfNotes();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (NotesManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NotesManager::preItemAppended)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (NotesManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NotesManager::postItemAppended)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (NotesManager::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NotesManager::preItemRemoved)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (NotesManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NotesManager::postItemRemoved)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (NotesManager::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NotesManager::preItemUpdated)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (NotesManager::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NotesManager::postItemUpdated)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject smart::NotesManager::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_smart__NotesManager.data,
    qt_meta_data_smart__NotesManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *smart::NotesManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *smart::NotesManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_smart__NotesManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int smart::NotesManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void smart::NotesManager::preItemAppended()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void smart::NotesManager::postItemAppended()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void smart::NotesManager::preItemRemoved(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void smart::NotesManager::postItemRemoved()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void smart::NotesManager::preItemUpdated(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void smart::NotesManager::postItemUpdated(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
