/****************************************************************************
** Meta object code from reading C++ file 'Downloader.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/Downloader.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Downloader.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Downloader_t {
    QByteArrayData data[9];
    char stringdata0[150];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Downloader_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Downloader_t qt_meta_stringdata_Downloader = {
    {
QT_MOC_LITERAL(0, 0, 10), // "Downloader"
QT_MOC_LITERAL(1, 11, 13), // "createMessage"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 21), // "loadDifferenceCounted"
QT_MOC_LITERAL(4, 48, 14), // "loadDifference"
QT_MOC_LITERAL(5, 63, 14), // "BeforeDownload"
QT_MOC_LITERAL(6, 78, 23), // "QWebEngineDownloadItem*"
QT_MOC_LITERAL(7, 102, 9), // "ShowError"
QT_MOC_LITERAL(8, 112, 37) // "QWebEngineDownloadItem::Downl..."

    },
    "Downloader\0createMessage\0\0"
    "loadDifferenceCounted\0loadDifference\0"
    "BeforeDownload\0QWebEngineDownloadItem*\0"
    "ShowError\0QWebEngineDownloadItem::DownloadState"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Downloader[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       3,    1,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   45,    2, 0x08 /* Private */,
       5,    1,   48,    2, 0x08 /* Private */,
       7,    1,   51,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void, 0x80000000 | 8,    2,

       0        // eod
};

void Downloader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Downloader *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->createMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->loadDifferenceCounted((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->loadDifference((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->BeforeDownload((*reinterpret_cast< QWebEngineDownloadItem*(*)>(_a[1]))); break;
        case 4: _t->ShowError((*reinterpret_cast< QWebEngineDownloadItem::DownloadState(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWebEngineDownloadItem* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Downloader::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Downloader::createMessage)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Downloader::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Downloader::loadDifferenceCounted)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Downloader::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Downloader.data,
    qt_meta_data_Downloader,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Downloader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Downloader::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Downloader.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Downloader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void Downloader::createMessage(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Downloader::loadDifferenceCounted(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
