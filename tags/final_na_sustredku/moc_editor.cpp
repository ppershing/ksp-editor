/****************************************************************************
** Meta object code from reading C++ file 'editor.h'
**
** Created: Thu Apr 15 12:19:00 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "editor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'editor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Editor[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
      27,   20,    7,    7, 0x0a,
      64,    7,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Editor[] = {
    "Editor\0\0keystroke()\0source\0"
    "insertFromMimeData(const QMimeData*)\0"
    "delayedKey()\0"
};

const QMetaObject Editor::staticMetaObject = {
    { &QTextEdit::staticMetaObject, qt_meta_stringdata_Editor,
      qt_meta_data_Editor, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Editor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Editor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Editor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Editor))
        return static_cast<void*>(const_cast< Editor*>(this));
    return QTextEdit::qt_metacast(_clname);
}

int Editor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTextEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: keystroke(); break;
        case 1: insertFromMimeData((*reinterpret_cast< const QMimeData*(*)>(_a[1]))); break;
        case 2: delayedKey(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void Editor::keystroke()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
static const uint qt_meta_data_InputEditor[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_InputEditor[] = {
    "InputEditor\0"
};

const QMetaObject InputEditor::staticMetaObject = {
    { &QPlainTextEdit::staticMetaObject, qt_meta_stringdata_InputEditor,
      qt_meta_data_InputEditor, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &InputEditor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *InputEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *InputEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_InputEditor))
        return static_cast<void*>(const_cast< InputEditor*>(this));
    return QPlainTextEdit::qt_metacast(_clname);
}

int InputEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPlainTextEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
