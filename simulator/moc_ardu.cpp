/****************************************************************************
** Meta object code from reading C++ file 'ardu.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ardu.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ardu.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_KKComm[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x05,
      18,    7,    7,    7, 0x05,
      28,    7,    7,    7, 0x05,
      45,   39,    7,    7, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_KKComm[] = {
    "KKComm\0\0refresh()\0lightOn()\0lightOff()\0"
    "pin,x\0pinState(int,bool)\0"
};

void KKComm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        KKComm *_t = static_cast<KKComm *>(_o);
        switch (_id) {
        case 0: _t->refresh(); break;
        case 1: _t->lightOn(); break;
        case 2: _t->lightOff(); break;
        case 3: _t->pinState((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData KKComm::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject KKComm::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_KKComm,
      qt_meta_data_KKComm, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &KKComm::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *KKComm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *KKComm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_KKComm))
        return static_cast<void*>(const_cast< KKComm*>(this));
    return QThread::qt_metacast(_clname);
}

int KKComm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void KKComm::refresh()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void KKComm::lightOn()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void KKComm::lightOff()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void KKComm::pinState(int _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
