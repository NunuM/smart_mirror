/****************************************************************************
** Meta object code from reading C++ file 'trafficmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../gui/src/smart/trafficmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'trafficmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_smart__TrafficManager_t {
    QByteArrayData data[21];
    char stringdata0[301];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_smart__TrafficManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_smart__TrafficManager_t qt_meta_stringdata_smart__TrafficManager = {
    {
QT_MOC_LITERAL(0, 0, 21), // "smart::TrafficManager"
QT_MOC_LITERAL(1, 22, 15), // "D-Bus Interface"
QT_MOC_LITERAL(2, 38, 16), // "io.smart.Traffic"
QT_MOC_LITERAL(3, 55, 15), // "preItemAppended"
QT_MOC_LITERAL(4, 71, 0), // ""
QT_MOC_LITERAL(5, 72, 16), // "postItemAppended"
QT_MOC_LITERAL(6, 89, 14), // "preItemRemoved"
QT_MOC_LITERAL(7, 104, 5), // "index"
QT_MOC_LITERAL(8, 110, 15), // "postItemRemoved"
QT_MOC_LITERAL(9, 126, 14), // "preItemUpdated"
QT_MOC_LITERAL(10, 141, 15), // "postItemUpdated"
QT_MOC_LITERAL(11, 157, 33), // "appendTrafficIncidentsAsJsonA..."
QT_MOC_LITERAL(12, 191, 7), // "traffic"
QT_MOC_LITERAL(13, 199, 13), // "appendTraffic"
QT_MOC_LITERAL(14, 213, 10), // "incidentId"
QT_MOC_LITERAL(15, 224, 8), // "latitude"
QT_MOC_LITERAL(16, 233, 9), // "longitude"
QT_MOC_LITERAL(17, 243, 11), // "description"
QT_MOC_LITERAL(18, 255, 12), // "isRoadClosed"
QT_MOC_LITERAL(19, 268, 14), // "removeIncident"
QT_MOC_LITERAL(20, 283, 17) // "numberOfIncidents"

    },
    "smart::TrafficManager\0D-Bus Interface\0"
    "io.smart.Traffic\0preItemAppended\0\0"
    "postItemAppended\0preItemRemoved\0index\0"
    "postItemRemoved\0preItemUpdated\0"
    "postItemUpdated\0appendTrafficIncidentsAsJsonArray\0"
    "traffic\0appendTraffic\0incidentId\0"
    "latitude\0longitude\0description\0"
    "isRoadClosed\0removeIncident\0"
    "numberOfIncidents"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_smart__TrafficManager[] = {

 // content:
       8,       // revision
       0,       // classname
       1,   14, // classinfo
      10,   16, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // classinfo: key, value
       1,    2,

 // signals: name, argc, parameters, tag, flags
       3,    0,   66,    4, 0x06 /* Public */,
       5,    0,   67,    4, 0x06 /* Public */,
       6,    1,   68,    4, 0x06 /* Public */,
       8,    0,   71,    4, 0x06 /* Public */,
       9,    1,   72,    4, 0x06 /* Public */,
      10,    1,   75,    4, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    1,   78,    4, 0x0a /* Public */,
      13,    5,   81,    4, 0x0a /* Public */,
      19,    1,   92,    4, 0x0a /* Public */,
      20,    0,   95,    4, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,

 // slots: parameters
    QMetaType::Bool, QMetaType::QString,   12,
    QMetaType::Bool, QMetaType::QString, QMetaType::QReal, QMetaType::QReal, QMetaType::QString, QMetaType::Bool,   14,   15,   16,   17,   18,
    QMetaType::Bool, QMetaType::QString,   14,
    QMetaType::Int,

       0        // eod
};

void smart::TrafficManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TrafficManager *_t = static_cast<TrafficManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->preItemAppended(); break;
        case 1: _t->postItemAppended(); break;
        case 2: _t->preItemRemoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->postItemRemoved(); break;
        case 4: _t->preItemUpdated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->postItemUpdated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: { bool _r = _t->appendTrafficIncidentsAsJsonArray((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 7: { bool _r = _t->appendTraffic((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2])),(*reinterpret_cast< qreal(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 8: { bool _r = _t->removeIncident((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 9: { int _r = _t->numberOfIncidents();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TrafficManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TrafficManager::preItemAppended)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TrafficManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TrafficManager::postItemAppended)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (TrafficManager::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TrafficManager::preItemRemoved)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (TrafficManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TrafficManager::postItemRemoved)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (TrafficManager::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TrafficManager::preItemUpdated)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (TrafficManager::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TrafficManager::postItemUpdated)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject smart::TrafficManager::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_smart__TrafficManager.data,
    qt_meta_data_smart__TrafficManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *smart::TrafficManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *smart::TrafficManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_smart__TrafficManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int smart::TrafficManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
    return _id;
}

// SIGNAL 0
void smart::TrafficManager::preItemAppended()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void smart::TrafficManager::postItemAppended()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void smart::TrafficManager::preItemRemoved(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void smart::TrafficManager::postItemRemoved()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void smart::TrafficManager::preItemUpdated(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void smart::TrafficManager::postItemUpdated(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
