/****************************************************************************
** Meta object code from reading C++ file 'conproddialog.h'
**
** Created: Wed Apr 13 16:04:27 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "conproddialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'conproddialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ConProdDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   30,   39,   39, 0x0a,
      40,   56,   39,   39, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ConProdDialog[] = {
    "ConProdDialog\0settemp(double)\0usertemp\0"
    "\0setmilk(double)\0usermilk\0"
};

void ConProdDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ConProdDialog *_t = static_cast<ConProdDialog *>(_o);
        switch (_id) {
        case 0: _t->settemp((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->setmilk((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ConProdDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ConProdDialog::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ConProdDialog,
      qt_meta_data_ConProdDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ConProdDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ConProdDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ConProdDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ConProdDialog))
        return static_cast<void*>(const_cast< ConProdDialog*>(this));
    return QWidget::qt_metacast(_clname);
}

int ConProdDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
