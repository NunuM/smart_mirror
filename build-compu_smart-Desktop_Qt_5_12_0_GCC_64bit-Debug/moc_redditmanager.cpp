/****************************************************************************
** Meta object code from reading C++ file 'redditmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../gui/src/smart/redditmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'redditmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_smart__RedditManager_t {
    QByteArrayData data[17];
    char stringdata0[230];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_smart__RedditManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_smart__RedditManager_t qt_meta_stringdata_smart__RedditManager = {
    {
QT_MOC_LITERAL(0, 0, 20), // "smart::RedditManager"
QT_MOC_LITERAL(1, 21, 15), // "D-Bus Interface"
QT_MOC_LITERAL(2, 37, 15), // "io.smart.Reddit"
QT_MOC_LITERAL(3, 53, 15), // "preItemAppended"
QT_MOC_LITERAL(4, 69, 0), // ""
QT_MOC_LITERAL(5, 70, 16), // "postItemAppended"
QT_MOC_LITERAL(6, 87, 14), // "preItemRemoved"
QT_MOC_LITERAL(7, 102, 5), // "index"
QT_MOC_LITERAL(8, 108, 15), // "postItemRemoved"
QT_MOC_LITERAL(9, 124, 14), // "preItemUpdated"
QT_MOC_LITERAL(10, 139, 15), // "postItemUpdated"
QT_MOC_LITERAL(11, 155, 11), // "lastChanged"
QT_MOC_LITERAL(12, 167, 17), // "appendRedditPosts"
QT_MOC_LITERAL(13, 185, 5), // "posts"
QT_MOC_LITERAL(14, 191, 19), // "clearAllRedditPosts"
QT_MOC_LITERAL(15, 211, 13), // "numberOfPosts"
QT_MOC_LITERAL(16, 225, 4) // "last"

    },
    "smart::RedditManager\0D-Bus Interface\0"
    "io.smart.Reddit\0preItemAppended\0\0"
    "postItemAppended\0preItemRemoved\0index\0"
    "postItemRemoved\0preItemUpdated\0"
    "postItemUpdated\0lastChanged\0"
    "appendRedditPosts\0posts\0clearAllRedditPosts\0"
    "numberOfPosts\0last"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_smart__RedditManager[] = {

 // content:
       8,       // revision
       0,       // classname
       1,   14, // classinfo
      10,   16, // methods
       1,   84, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // classinfo: key, value
       1,    2,

 // signals: name, argc, parameters, tag, flags
       3,    0,   66,    4, 0x06 /* Public */,
       5,    0,   67,    4, 0x06 /* Public */,
       6,    1,   68,    4, 0x06 /* Public */,
       8,    0,   71,    4, 0x06 /* Public */,
       9,    1,   72,    4, 0x06 /* Public */,
      10,    1,   75,    4, 0x06 /* Public */,
      11,    0,   78,    4, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    1,   79,    4, 0x0a /* Public */,
      14,    0,   82,    4, 0x0a /* Public */,
      15,    0,   83,    4, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Bool, QMetaType::QString,   13,
    QMetaType::Bool,
    QMetaType::Int,

 // properties: name, type, flags
      16, QMetaType::QVariantMap, 0x00495001,

 // properties: notify_signal_id
       6,

       0        // eod
};

void smart::RedditManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RedditManager *_t = static_cast<RedditManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->preItemAppended(); break;
        case 1: _t->postItemAppended(); break;
        case 2: _t->preItemRemoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->postItemRemoved(); break;
        case 4: _t->preItemUpdated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->postItemUpdated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->lastChanged(); break;
        case 7: { bool _r = _t->appendRedditPosts((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 8: { bool _r = _t->clearAllRedditPosts();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 9: { int _r = _t->numberOfPosts();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (RedditManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RedditManager::preItemAppended)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (RedditManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RedditManager::postItemAppended)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (RedditManager::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RedditManager::preItemRemoved)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (RedditManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RedditManager::postItemRemoved)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (RedditManager::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RedditManager::preItemUpdated)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (RedditManager::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RedditManager::postItemUpdated)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (RedditManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RedditManager::lastChanged)) {
                *result = 6;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        RedditManager *_t = static_cast<RedditManager *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QVariantMap*>(_v) = _t->lastInsertedPosts(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject smart::RedditManager::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_smart__RedditManager.data,
    qt_meta_data_smart__RedditManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *smart::RedditManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *smart::RedditManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_smart__RedditManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int smart::RedditManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void smart::RedditManager::preItemAppended()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void smart::RedditManager::postItemAppended()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void smart::RedditManager::preItemRemoved(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void smart::RedditManager::postItemRemoved()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void smart::RedditManager::preItemUpdated(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void smart::RedditManager::postItemUpdated(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void smart::RedditManager::lastChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
