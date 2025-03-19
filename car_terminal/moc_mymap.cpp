/****************************************************************************
** Meta object code from reading C++ file 'mymap.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "myMap/mymap.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mymap.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyMap_t {
    QByteArrayData data[16];
    char stringdata0[221];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyMap_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyMap_t qt_meta_stringdata_MyMap = {
    {
QT_MOC_LITERAL(0, 0, 5), // "MyMap"
QT_MOC_LITERAL(1, 6, 7), // "get_map"
QT_MOC_LITERAL(2, 14, 0), // ""
QT_MOC_LITERAL(3, 15, 9), // "longitude"
QT_MOC_LITERAL(4, 25, 8), // "latitude"
QT_MOC_LITERAL(5, 34, 14), // "map_image_show"
QT_MOC_LITERAL(6, 49, 7), // "QImage*"
QT_MOC_LITERAL(7, 57, 9), // "map_image"
QT_MOC_LITERAL(8, 67, 26), // "on_pushButton_seek_clicked"
QT_MOC_LITERAL(9, 94, 15), // "mousePressEvent"
QT_MOC_LITERAL(10, 110, 12), // "QMouseEvent*"
QT_MOC_LITERAL(11, 123, 5), // "event"
QT_MOC_LITERAL(12, 129, 17), // "mouseReleaseEvent"
QT_MOC_LITERAL(13, 147, 14), // "mouseMoveEvent"
QT_MOC_LITERAL(14, 162, 29), // "on_pushButton_magnify_clicked"
QT_MOC_LITERAL(15, 192, 28) // "on_pushButton_reduce_clicked"

    },
    "MyMap\0get_map\0\0longitude\0latitude\0"
    "map_image_show\0QImage*\0map_image\0"
    "on_pushButton_seek_clicked\0mousePressEvent\0"
    "QMouseEvent*\0event\0mouseReleaseEvent\0"
    "mouseMoveEvent\0on_pushButton_magnify_clicked\0"
    "on_pushButton_reduce_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyMap[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   54,    2, 0x0a /* Public */,
       5,    1,   59,    2, 0x08 /* Private */,
       8,    0,   62,    2, 0x08 /* Private */,
       9,    1,   63,    2, 0x08 /* Private */,
      12,    1,   66,    2, 0x08 /* Private */,
      13,    1,   69,    2, 0x08 /* Private */,
      14,    0,   72,    2, 0x08 /* Private */,
      15,    0,   73,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MyMap::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MyMap *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->get_map((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 1: _t->map_image_show((*reinterpret_cast< QImage*(*)>(_a[1]))); break;
        case 2: _t->on_pushButton_seek_clicked(); break;
        case 3: _t->mousePressEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 4: _t->mouseReleaseEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 5: _t->mouseMoveEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 6: _t->on_pushButton_magnify_clicked(); break;
        case 7: _t->on_pushButton_reduce_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MyMap::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_MyMap.data,
    qt_meta_data_MyMap,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MyMap::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyMap::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyMap.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MyMap::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
