/****************************************************************************
** Meta object code from reading C++ file 'navigationmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../gui/src/smart/navigationmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'navigationmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_smart__NavigationManager_t {
    QByteArrayData data[16];
    char stringdata0[251];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_smart__NavigationManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_smart__NavigationManager_t qt_meta_stringdata_smart__NavigationManager = {
    {
QT_MOC_LITERAL(0, 0, 24), // "smart::NavigationManager"
QT_MOC_LITERAL(1, 25, 15), // "D-Bus Interface"
QT_MOC_LITERAL(2, 41, 19), // "io.smart.Navigation"
QT_MOC_LITERAL(3, 61, 12), // "changeViewTo"
QT_MOC_LITERAL(4, 74, 0), // ""
QT_MOC_LITERAL(5, 75, 4), // "view"
QT_MOC_LITERAL(6, 80, 10), // "appendView"
QT_MOC_LITERAL(7, 91, 8), // "viewName"
QT_MOC_LITERAL(8, 100, 8), // "viewPath"
QT_MOC_LITERAL(9, 109, 25), // "setApplicationsViewAsRoot"
QT_MOC_LITERAL(10, 135, 17), // "setNewsViewAsRoot"
QT_MOC_LITERAL(11, 153, 20), // "setSensorsViewAsRoot"
QT_MOC_LITERAL(12, 174, 18), // "setMediaViewAsRoot"
QT_MOC_LITERAL(13, 193, 18), // "setNotesViewAsRoot"
QT_MOC_LITERAL(14, 212, 20), // "setWeatherViewAsRoot"
QT_MOC_LITERAL(15, 233, 17) // "setHomeViewAsRoot"

    },
    "smart::NavigationManager\0D-Bus Interface\0"
    "io.smart.Navigation\0changeViewTo\0\0"
    "view\0appendView\0viewName\0viewPath\0"
    "setApplicationsViewAsRoot\0setNewsViewAsRoot\0"
    "setSensorsViewAsRoot\0setMediaViewAsRoot\0"
    "setNotesViewAsRoot\0setWeatherViewAsRoot\0"
    "setHomeViewAsRoot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_smart__NavigationManager[] = {

 // content:
       8,       // revision
       0,       // classname
       1,   14, // classinfo
       9,   16, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // classinfo: key, value
       1,    2,

 // signals: name, argc, parameters, tag, flags
       3,    1,   61,    4, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    2,   64,    4, 0x0a /* Public */,
       9,    0,   69,    4, 0x0a /* Public */,
      10,    0,   70,    4, 0x0a /* Public */,
      11,    0,   71,    4, 0x0a /* Public */,
      12,    0,   72,    4, 0x0a /* Public */,
      13,    0,   73,    4, 0x0a /* Public */,
      14,    0,   74,    4, 0x0a /* Public */,
      15,    0,   75,    4, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    5,

 // slots: parameters
    QMetaType::Bool, QMetaType::QString, QMetaType::QString,    7,    8,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,

       0        // eod
};

void smart::NavigationManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NavigationManager *_t = static_cast<NavigationManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changeViewTo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: { bool _r = _t->appendView((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 2: { bool _r = _t->setApplicationsViewAsRoot();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 3: { bool _r = _t->setNewsViewAsRoot();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 4: { bool _r = _t->setSensorsViewAsRoot();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 5: { bool _r = _t->setMediaViewAsRoot();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 6: { bool _r = _t->setNotesViewAsRoot();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 7: { bool _r = _t->setWeatherViewAsRoot();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 8: { bool _r = _t->setHomeViewAsRoot();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (NavigationManager::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NavigationManager::changeViewTo)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject smart::NavigationManager::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_smart__NavigationManager.data,
    qt_meta_data_smart__NavigationManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *smart::NavigationManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *smart::NavigationManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_smart__NavigationManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int smart::NavigationManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
    return _id;
}

// SIGNAL 0
void smart::NavigationManager::changeViewTo(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
