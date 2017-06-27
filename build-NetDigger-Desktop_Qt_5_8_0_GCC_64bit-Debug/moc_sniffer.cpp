/****************************************************************************
** Meta object code from reading C++ file 'sniffer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../NetDigger/sniffer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sniffer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CQTSniffer_t {
    QByteArrayData data[15];
    char stringdata0[140];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CQTSniffer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CQTSniffer_t qt_meta_stringdata_CQTSniffer = {
    {
QT_MOC_LITERAL(0, 0, 10), // "CQTSniffer"
QT_MOC_LITERAL(1, 11, 9), // "stop_loop"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 12), // "packet_ready"
QT_MOC_LITERAL(4, 35, 11), // "packet_data"
QT_MOC_LITERAL(5, 47, 14), // "set_graph_data"
QT_MOC_LITERAL(6, 62, 8), // "protocol"
QT_MOC_LITERAL(7, 71, 4), // "size"
QT_MOC_LITERAL(8, 76, 4), // "time"
QT_MOC_LITERAL(9, 81, 11), // "start_sniff"
QT_MOC_LITERAL(10, 93, 10), // "stop_sniff"
QT_MOC_LITERAL(11, 104, 10), // "set_filter"
QT_MOC_LITERAL(12, 115, 6), // "filter"
QT_MOC_LITERAL(13, 122, 12), // "safe_in_file"
QT_MOC_LITERAL(14, 135, 4) // "safe"

    },
    "CQTSniffer\0stop_loop\0\0packet_ready\0"
    "packet_data\0set_graph_data\0protocol\0"
    "size\0time\0start_sniff\0stop_sniff\0"
    "set_filter\0filter\0safe_in_file\0safe"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CQTSniffer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    1,   50,    2, 0x06 /* Public */,
       5,    3,   53,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   60,    2, 0x0a /* Public */,
      10,    0,   61,    2, 0x0a /* Public */,
      11,    1,   62,    2, 0x0a /* Public */,
      13,    1,   65,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::UChar, QMetaType::UInt, QMetaType::ULongLong,    6,    7,    8,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, QMetaType::Bool,   14,

       0        // eod
};

void CQTSniffer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CQTSniffer *_t = static_cast<CQTSniffer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->stop_loop(); break;
        case 1: _t->packet_ready((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->set_graph_data((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< quint32(*)>(_a[2])),(*reinterpret_cast< quint64(*)>(_a[3]))); break;
        case 3: _t->start_sniff(); break;
        case 4: _t->stop_sniff(); break;
        case 5: _t->set_filter((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->safe_in_file((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CQTSniffer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CQTSniffer::stop_loop)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CQTSniffer::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CQTSniffer::packet_ready)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (CQTSniffer::*_t)(quint8 , quint32 , quint64 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CQTSniffer::set_graph_data)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject CQTSniffer::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_CQTSniffer.data,
      qt_meta_data_CQTSniffer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CQTSniffer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CQTSniffer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CQTSniffer.stringdata0))
        return static_cast<void*>(const_cast< CQTSniffer*>(this));
    return QThread::qt_metacast(_clname);
}

int CQTSniffer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void CQTSniffer::stop_loop()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void CQTSniffer::packet_ready(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CQTSniffer::set_graph_data(quint8 _t1, quint32 _t2, quint64 _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
