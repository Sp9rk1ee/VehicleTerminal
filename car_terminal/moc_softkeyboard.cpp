/****************************************************************************
** Meta object code from reading C++ file 'softkeyboard.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "softkeyboard/softkeyboard.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'softkeyboard.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SoftKeyboard_t {
    QByteArrayData data[17];
    char stringdata0[289];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SoftKeyboard_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SoftKeyboard_t qt_meta_stringdata_SoftKeyboard = {
    {
QT_MOC_LITERAL(0, 0, 12), // "SoftKeyboard"
QT_MOC_LITERAL(1, 13, 23), // "sendInputBufferAreaText"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 4), // "text"
QT_MOC_LITERAL(4, 43, 26), // "candidateLetterChangedSlot"
QT_MOC_LITERAL(5, 70, 20), // "candidateWordBtnSlot"
QT_MOC_LITERAL(6, 91, 24), // "candidateWordPrePageSlot"
QT_MOC_LITERAL(7, 116, 25), // "candidateWordNextPageSlot"
QT_MOC_LITERAL(8, 142, 19), // "numberLetterBtnSlot"
QT_MOC_LITERAL(9, 162, 20), // "changeUpperLowerSlot"
QT_MOC_LITERAL(10, 183, 14), // "deleteTextSlot"
QT_MOC_LITERAL(11, 198, 14), // "changeSkinSlot"
QT_MOC_LITERAL(12, 213, 22), // "changeLetterSymbolSlot"
QT_MOC_LITERAL(13, 236, 9), // "spaceSlot"
QT_MOC_LITERAL(14, 246, 14), // "changeChEnSlot"
QT_MOC_LITERAL(15, 261, 9), // "enterSlot"
QT_MOC_LITERAL(16, 271, 17) // "clearAndCloseSlot"

    },
    "SoftKeyboard\0sendInputBufferAreaText\0"
    "\0text\0candidateLetterChangedSlot\0"
    "candidateWordBtnSlot\0candidateWordPrePageSlot\0"
    "candidateWordNextPageSlot\0numberLetterBtnSlot\0"
    "changeUpperLowerSlot\0deleteTextSlot\0"
    "changeSkinSlot\0changeLetterSymbolSlot\0"
    "spaceSlot\0changeChEnSlot\0enterSlot\0"
    "clearAndCloseSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SoftKeyboard[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   87,    2, 0x0a /* Public */,
       5,    0,   90,    2, 0x0a /* Public */,
       6,    0,   91,    2, 0x0a /* Public */,
       7,    0,   92,    2, 0x0a /* Public */,
       8,    0,   93,    2, 0x0a /* Public */,
       9,    0,   94,    2, 0x0a /* Public */,
      10,    0,   95,    2, 0x0a /* Public */,
      11,    0,   96,    2, 0x0a /* Public */,
      12,    0,   97,    2, 0x0a /* Public */,
      13,    0,   98,    2, 0x0a /* Public */,
      14,    0,   99,    2, 0x0a /* Public */,
      15,    0,  100,    2, 0x0a /* Public */,
      16,    0,  101,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SoftKeyboard::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SoftKeyboard *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendInputBufferAreaText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->candidateLetterChangedSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->candidateWordBtnSlot(); break;
        case 3: _t->candidateWordPrePageSlot(); break;
        case 4: _t->candidateWordNextPageSlot(); break;
        case 5: _t->numberLetterBtnSlot(); break;
        case 6: _t->changeUpperLowerSlot(); break;
        case 7: _t->deleteTextSlot(); break;
        case 8: _t->changeSkinSlot(); break;
        case 9: _t->changeLetterSymbolSlot(); break;
        case 10: _t->spaceSlot(); break;
        case 11: _t->changeChEnSlot(); break;
        case 12: _t->enterSlot(); break;
        case 13: _t->clearAndCloseSlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SoftKeyboard::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SoftKeyboard::sendInputBufferAreaText)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SoftKeyboard::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_SoftKeyboard.data,
    qt_meta_data_SoftKeyboard,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SoftKeyboard::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SoftKeyboard::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SoftKeyboard.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SoftKeyboard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void SoftKeyboard::sendInputBufferAreaText(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
