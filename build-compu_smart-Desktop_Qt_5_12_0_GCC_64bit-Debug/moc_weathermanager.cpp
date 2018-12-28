/****************************************************************************
** Meta object code from reading C++ file 'weathermanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../gui/src/smart/weathermanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'weathermanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_smart__WeatherManager_t {
    QByteArrayData data[27];
    char stringdata0[311];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_smart__WeatherManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_smart__WeatherManager_t qt_meta_stringdata_smart__WeatherManager = {
    {
QT_MOC_LITERAL(0, 0, 21), // "smart::WeatherManager"
QT_MOC_LITERAL(1, 22, 15), // "D-Bus Interface"
QT_MOC_LITERAL(2, 38, 16), // "io.smart.Weather"
QT_MOC_LITERAL(3, 55, 15), // "preItemAppended"
QT_MOC_LITERAL(4, 71, 0), // ""
QT_MOC_LITERAL(5, 72, 16), // "postItemAppended"
QT_MOC_LITERAL(6, 89, 14), // "preItemRemoved"
QT_MOC_LITERAL(7, 104, 5), // "index"
QT_MOC_LITERAL(8, 110, 15), // "postItemRemoved"
QT_MOC_LITERAL(9, 126, 15), // "todayWasChanged"
QT_MOC_LITERAL(10, 142, 18), // "tomorrowWasChanged"
QT_MOC_LITERAL(11, 161, 13), // "appendWeather"
QT_MOC_LITERAL(12, 175, 4), // "date"
QT_MOC_LITERAL(13, 180, 8), // "humidity"
QT_MOC_LITERAL(14, 189, 8), // "pressure"
QT_MOC_LITERAL(15, 198, 4), // "temp"
QT_MOC_LITERAL(16, 203, 7), // "tempMax"
QT_MOC_LITERAL(17, 211, 7), // "tempMin"
QT_MOC_LITERAL(18, 219, 11), // "description"
QT_MOC_LITERAL(19, 231, 4), // "icon"
QT_MOC_LITERAL(20, 236, 7), // "windDeg"
QT_MOC_LITERAL(21, 244, 9), // "windSpeed"
QT_MOC_LITERAL(22, 254, 19), // "appendWeatherAsJson"
QT_MOC_LITERAL(23, 274, 7), // "weather"
QT_MOC_LITERAL(24, 282, 13), // "removeWeather"
QT_MOC_LITERAL(25, 296, 5), // "today"
QT_MOC_LITERAL(26, 302, 8) // "tomorrow"

    },
    "smart::WeatherManager\0D-Bus Interface\0"
    "io.smart.Weather\0preItemAppended\0\0"
    "postItemAppended\0preItemRemoved\0index\0"
    "postItemRemoved\0todayWasChanged\0"
    "tomorrowWasChanged\0appendWeather\0date\0"
    "humidity\0pressure\0temp\0tempMax\0tempMin\0"
    "description\0icon\0windDeg\0windSpeed\0"
    "appendWeatherAsJson\0weather\0removeWeather\0"
    "today\0tomorrow"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_smart__WeatherManager[] = {

 // content:
       8,       // revision
       0,       // classname
       1,   14, // classinfo
       9,   16, // methods
       2,   96, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // classinfo: key, value
       1,    2,

 // signals: name, argc, parameters, tag, flags
       3,    0,   61,    4, 0x06 /* Public */,
       5,    0,   62,    4, 0x06 /* Public */,
       6,    1,   63,    4, 0x06 /* Public */,
       8,    0,   66,    4, 0x06 /* Public */,
       9,    0,   67,    4, 0x06 /* Public */,
      10,    0,   68,    4, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,   10,   69,    4, 0x0a /* Public */,
      22,    1,   90,    4, 0x0a /* Public */,
      24,    1,   93,    4, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Bool, QMetaType::QString, QMetaType::QReal, QMetaType::QReal, QMetaType::QReal, QMetaType::QReal, QMetaType::QReal, QMetaType::QString, QMetaType::QString, QMetaType::QReal, QMetaType::QReal,   12,   13,   14,   15,   16,   17,   18,   19,   20,   21,
    QMetaType::Bool, QMetaType::QString,   23,
    QMetaType::Bool, QMetaType::QString,   12,

 // properties: name, type, flags
      25, QMetaType::QVariantMap, 0x00495001,
      26, QMetaType::QVariantMap, 0x00495001,

 // properties: notify_signal_id
       4,
       5,

       0        // eod
};

void smart::WeatherManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WeatherManager *_t = static_cast<WeatherManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->preItemAppended(); break;
        case 1: _t->postItemAppended(); break;
        case 2: _t->preItemRemoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->postItemRemoved(); break;
        case 4: _t->todayWasChanged(); break;
        case 5: _t->tomorrowWasChanged(); break;
        case 6: { bool _r = _t->appendWeather((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2])),(*reinterpret_cast< qreal(*)>(_a[3])),(*reinterpret_cast< qreal(*)>(_a[4])),(*reinterpret_cast< qreal(*)>(_a[5])),(*reinterpret_cast< qreal(*)>(_a[6])),(*reinterpret_cast< QString(*)>(_a[7])),(*reinterpret_cast< QString(*)>(_a[8])),(*reinterpret_cast< qreal(*)>(_a[9])),(*reinterpret_cast< qreal(*)>(_a[10])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 7: { bool _r = _t->appendWeatherAsJson((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 8: { bool _r = _t->removeWeather((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WeatherManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WeatherManager::preItemAppended)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (WeatherManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WeatherManager::postItemAppended)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (WeatherManager::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WeatherManager::preItemRemoved)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (WeatherManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WeatherManager::postItemRemoved)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (WeatherManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WeatherManager::todayWasChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (WeatherManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WeatherManager::tomorrowWasChanged)) {
                *result = 5;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        WeatherManager *_t = static_cast<WeatherManager *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QVariantMap*>(_v) = _t->todayWeather(); break;
        case 1: *reinterpret_cast< QVariantMap*>(_v) = _t->tomorrowWeather(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject smart::WeatherManager::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_smart__WeatherManager.data,
    qt_meta_data_smart__WeatherManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *smart::WeatherManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *smart::WeatherManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_smart__WeatherManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int smart::WeatherManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void smart::WeatherManager::preItemAppended()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void smart::WeatherManager::postItemAppended()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void smart::WeatherManager::preItemRemoved(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void smart::WeatherManager::postItemRemoved()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void smart::WeatherManager::todayWasChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void smart::WeatherManager::tomorrowWasChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
