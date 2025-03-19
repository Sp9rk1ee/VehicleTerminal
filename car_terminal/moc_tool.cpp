/****************************************************************************
** Meta object code from reading C++ file 'tool.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "tool.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tool.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Tool_t {
    QByteArrayData data[12];
    char stringdata0[226];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Tool_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Tool_t qt_meta_stringdata_Tool = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Tool"
QT_MOC_LITERAL(1, 5, 10), // "wifi_judge"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 14), // "hide_show_tool"
QT_MOC_LITERAL(4, 32, 9), // "bizi_path"
QT_MOC_LITERAL(5, 42, 8), // "use_name"
QT_MOC_LITERAL(6, 51, 28), // "on_pushButton_folder_clicked"
QT_MOC_LITERAL(7, 80, 27), // "on_pushButton_light_clicked"
QT_MOC_LITERAL(8, 108, 29), // "on_pushButton_backcar_clicked"
QT_MOC_LITERAL(9, 138, 26), // "on_pushButton_wifi_clicked"
QT_MOC_LITERAL(10, 165, 34), // "on_pushButton_instructions_cl..."
QT_MOC_LITERAL(11, 200, 25) // "on_pushButton_set_clicked"

    },
    "Tool\0wifi_judge\0\0hide_show_tool\0"
    "bizi_path\0use_name\0on_pushButton_folder_clicked\0"
    "on_pushButton_light_clicked\0"
    "on_pushButton_backcar_clicked\0"
    "on_pushButton_wifi_clicked\0"
    "on_pushButton_instructions_clicked\0"
    "on_pushButton_set_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Tool[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       3,    0,   67,    2, 0x06 /* Public */,
       4,    1,   68,    2, 0x06 /* Public */,
       5,    1,   71,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   74,    2, 0x08 /* Private */,
       7,    0,   75,    2, 0x08 /* Private */,
       8,    0,   76,    2, 0x08 /* Private */,
       9,    0,   77,    2, 0x08 /* Private */,
      10,    0,   78,    2, 0x08 /* Private */,
      11,    0,   79,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Tool::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Tool *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->wifi_judge((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->hide_show_tool(); break;
        case 2: _t->bizi_path((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->use_name((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->on_pushButton_folder_clicked(); break;
        case 5: _t->on_pushButton_light_clicked(); break;
        case 6: _t->on_pushButton_backcar_clicked(); break;
        case 7: _t->on_pushButton_wifi_clicked(); break;
        case 8: _t->on_pushButton_instructions_clicked(); break;
        case 9: _t->on_pushButton_set_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Tool::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Tool::wifi_judge)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Tool::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Tool::hide_show_tool)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Tool::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Tool::bizi_path)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Tool::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Tool::use_name)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Tool::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_Tool.data,
    qt_meta_data_Tool,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Tool::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Tool::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Tool.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Tool::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void Tool::wifi_judge(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Tool::hide_show_tool()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Tool::bizi_path(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Tool::use_name(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
