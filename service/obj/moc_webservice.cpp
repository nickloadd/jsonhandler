/****************************************************************************
** Meta object code from reading C++ file 'webservice.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/webservice.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'webservice.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WebService_t {
    QByteArrayData data[13];
    char stringdata0[155];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WebService_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WebService_t qt_meta_stringdata_WebService = {
    {
QT_MOC_LITERAL(0, 0, 10), // "WebService"
QT_MOC_LITERAL(1, 11, 6), // "closed"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 8), // "haveData"
QT_MOC_LITERAL(4, 28, 3), // "uid"
QT_MOC_LITERAL(5, 32, 4), // "data"
QT_MOC_LITERAL(6, 37, 15), // "sendTextMessage"
QT_MOC_LITERAL(7, 53, 18), // "sendTextMessageAll"
QT_MOC_LITERAL(8, 72, 15), // "onNewConnection"
QT_MOC_LITERAL(9, 88, 18), // "processTextMessage"
QT_MOC_LITERAL(10, 107, 7), // "message"
QT_MOC_LITERAL(11, 115, 20), // "processBinaryMessage"
QT_MOC_LITERAL(12, 136, 18) // "socketDisconnected"

    },
    "WebService\0closed\0\0haveData\0uid\0data\0"
    "sendTextMessage\0sendTextMessageAll\0"
    "onNewConnection\0processTextMessage\0"
    "message\0processBinaryMessage\0"
    "socketDisconnected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WebService[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    2,   55,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    2,   60,    2, 0x0a /* Public */,
       7,    1,   65,    2, 0x0a /* Public */,
       8,    0,   68,    2, 0x08 /* Private */,
       9,    1,   69,    2, 0x08 /* Private */,
      11,    1,   72,    2, 0x08 /* Private */,
      12,    0,   75,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QJsonDocument,    4,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QJsonDocument,    4,    5,
    QMetaType::Void, QMetaType::QJsonDocument,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QByteArray,   10,
    QMetaType::Void,

       0        // eod
};

void WebService::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WebService *_t = static_cast<WebService *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->closed(); break;
        case 1: _t->haveData((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QJsonDocument(*)>(_a[2]))); break;
        case 2: _t->sendTextMessage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QJsonDocument(*)>(_a[2]))); break;
        case 3: _t->sendTextMessageAll((*reinterpret_cast< QJsonDocument(*)>(_a[1]))); break;
        case 4: _t->onNewConnection(); break;
        case 5: _t->processTextMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->processBinaryMessage((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 7: _t->socketDisconnected(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (WebService::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WebService::closed)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (WebService::*_t)(QString , QJsonDocument );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WebService::haveData)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject WebService::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_WebService.data,
      qt_meta_data_WebService,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *WebService::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WebService::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WebService.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int WebService::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void WebService::closed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void WebService::haveData(QString _t1, QJsonDocument _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
