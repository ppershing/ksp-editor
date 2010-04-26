/****************************************************************************
** Meta object code from reading C++ file 'testdialog.h'
**
** Created: Thu Apr 15 12:19:02 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "testdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'testdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TestDialog[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      25,   11,   11,   11, 0x0a,
      40,   32,   11,   11, 0x08,
      79,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_TestDialog[] = {
    "TestDialog\0\0submitting()\0show()\0checked\0"
    "on_radioButtonManualTest_toggled(bool)\0"
    "on_pushButton_clicked()\0"
};

const QMetaObject TestDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_TestDialog,
      qt_meta_data_TestDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TestDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TestDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TestDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TestDialog))
        return static_cast<void*>(const_cast< TestDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int TestDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: submitting(); break;
        case 1: show(); break;
        case 2: on_radioButtonManualTest_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: on_pushButton_clicked(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void TestDialog::submitting()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
