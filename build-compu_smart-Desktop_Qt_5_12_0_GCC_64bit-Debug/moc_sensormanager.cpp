/****************************************************************************
** Meta object code from reading C++ file 'sensormanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../gui/src/smart/sensormanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sensormanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_smart__SensorManager_t {
    QByteArrayData data[20];
    char stringdata0[248];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_smart__SensorManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_smart__SensorManager_t qt_meta_stringdata_smart__SensorManager = {
    {
QT_MOC_LITERAL(0, 0, 20), // "smart::SensorManager"
QT_MOC_LITERAL(1, 21, 15), // "D-Bus Interface"
QT_MOC_LITERAL(2, 37, 15), // "io.smart.Sensor"
QT_MOC_LITERAL(3, 53, 15), // "preItemAppended"
QT_MOC_LITERAL(4, 69, 0), // ""
QT_MOC_LITERAL(5, 70, 16), // "postItemAppended"
QT_MOC_LITERAL(6, 87, 14), // "preItemRemoved"
QT_MOC_LITERAL(7, 102, 5), // "index"
QT_MOC_LITERAL(8, 108, 15), // "postItemRemoved"
QT_MOC_LITERAL(9, 124, 14), // "preItemUpdated"
QT_MOC_LITERAL(10, 139, 15), // "postItemUpdated"
QT_MOC_LITERAL(11, 155, 12), // "appendSensor"
QT_MOC_LITERAL(12, 168, 4), // "name"
QT_MOC_LITERAL(13, 173, 4), // "unit"
QT_MOC_LITERAL(14, 178, 14), // "QVector<qreal>"
QT_MOC_LITERAL(15, 193, 7), // "reading"
QT_MOC_LITERAL(16, 201, 10), // "addReading"
QT_MOC_LITERAL(17, 212, 5), // "value"
QT_MOC_LITERAL(18, 218, 12), // "removeSensor"
QT_MOC_LITERAL(19, 231, 16) // "numbersOfSensors"

    },
    "smart::SensorManager\0D-Bus Interface\0"
    "io.smart.Sensor\0preItemAppended\0\0"
    "postItemAppended\0preItemRemoved\0index\0"
    "postItemRemoved\0preItemUpdated\0"
    "postItemUpdated\0appendSensor\0name\0"
    "unit\0QVector<qreal>\0reading\0addReading\0"
    "value\0removeSensor\0numbersOfSensors"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_smart__SensorManager[] = {

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
      11,    3,   78,    4, 0x0a /* Public */,
      16,    2,   85,    4, 0x0a /* Public */,
      18,    1,   90,    4, 0x0a /* Public */,
      19,    0,   93,    4, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,

 // slots: parameters
    QMetaType::Bool, QMetaType::QString, QMetaType::QString, 0x80000000 | 14,   12,   13,   15,
    QMetaType::Bool, QMetaType::QString, QMetaType::QReal,   12,   17,
    QMetaType::Bool, QMetaType::QString,   12,
    QMetaType::Int,

       0        // eod
};

void smart::SensorManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SensorManager *_t = static_cast<SensorManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->preItemAppended(); break;
        case 1: _t->postItemAppended(); break;
        case 2: _t->preItemRemoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->postItemRemoved(); break;
        case 4: _t->preItemUpdated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->postItemUpdated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: { bool _r = _t->appendSensor((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QVector<qreal>(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 7: { bool _r = _t->addReading((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 8: { bool _r = _t->removeSensor((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 9: { int _r = _t->numbersOfSensors();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<qreal> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SensorManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SensorManager::preItemAppended)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SensorManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SensorManager::postItemAppended)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SensorManager::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SensorManager::preItemRemoved)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SensorManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SensorManager::postItemRemoved)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (SensorManager::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SensorManager::preItemUpdated)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (SensorManager::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SensorManager::postItemUpdated)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject smart::SensorManager::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_smart__SensorManager.data,
    qt_meta_data_smart__SensorManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *smart::SensorManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *smart::SensorManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_smart__SensorManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int smart::SensorManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void smart::SensorManager::preItemAppended()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void smart::SensorManager::postItemAppended()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void smart::SensorManager::preItemRemoved(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void smart::SensorManager::postItemRemoved()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void smart::SensorManager::preItemUpdated(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void smart::SensorManager::postItemUpdated(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
