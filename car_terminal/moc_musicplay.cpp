/****************************************************************************
** Meta object code from reading C++ file 'musicplay.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "musicplay/musicplay.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'musicplay.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MusicPlay_t {
    QByteArrayData data[17];
    char stringdata0[365];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MusicPlay_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MusicPlay_t qt_meta_stringdata_MusicPlay = {
    {
QT_MOC_LITERAL(0, 0, 9), // "MusicPlay"
QT_MOC_LITERAL(1, 10, 26), // "on_pushButton_page_clicked"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 29), // "on_pushButton_pattern_clicked"
QT_MOC_LITERAL(4, 68, 26), // "on_pushButton_play_clicked"
QT_MOC_LITERAL(5, 95, 19), // "onItemDoubleClicked"
QT_MOC_LITERAL(6, 115, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(7, 132, 27), // "on_pushButton_under_clicked"
QT_MOC_LITERAL(8, 160, 24), // "on_pushButton_on_clicked"
QT_MOC_LITERAL(9, 185, 31), // "mediaPlylistCurrentIndexChanged"
QT_MOC_LITERAL(10, 217, 25), // "musicPlyerDurationChanged"
QT_MOC_LITERAL(11, 243, 25), // "musicPlyerPositionChanged"
QT_MOC_LITERAL(12, 269, 22), // "musicPlyerStateChanged"
QT_MOC_LITERAL(13, 292, 19), // "QMediaPlayer::State"
QT_MOC_LITERAL(14, 312, 22), // "durationSliderReleased"
QT_MOC_LITERAL(15, 335, 17), // "on_volume_clicked"
QT_MOC_LITERAL(16, 353, 11) // "alter_lyric"

    },
    "MusicPlay\0on_pushButton_page_clicked\0"
    "\0on_pushButton_pattern_clicked\0"
    "on_pushButton_play_clicked\0"
    "onItemDoubleClicked\0QListWidgetItem*\0"
    "on_pushButton_under_clicked\0"
    "on_pushButton_on_clicked\0"
    "mediaPlylistCurrentIndexChanged\0"
    "musicPlyerDurationChanged\0"
    "musicPlyerPositionChanged\0"
    "musicPlyerStateChanged\0QMediaPlayer::State\0"
    "durationSliderReleased\0on_volume_clicked\0"
    "alter_lyric"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MusicPlay[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
       3,    0,   80,    2, 0x08 /* Private */,
       4,    0,   81,    2, 0x08 /* Private */,
       5,    1,   82,    2, 0x08 /* Private */,
       7,    0,   85,    2, 0x08 /* Private */,
       8,    0,   86,    2, 0x08 /* Private */,
       9,    1,   87,    2, 0x08 /* Private */,
      10,    1,   90,    2, 0x08 /* Private */,
      11,    1,   93,    2, 0x08 /* Private */,
      12,    1,   96,    2, 0x08 /* Private */,
      14,    0,   99,    2, 0x08 /* Private */,
      15,    0,  100,    2, 0x08 /* Private */,
      16,    1,  101,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::LongLong,    2,
    QMetaType::Void, QMetaType::LongLong,    2,
    QMetaType::Void, 0x80000000 | 13,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong,    2,

       0        // eod
};

void MusicPlay::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MusicPlay *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButton_page_clicked(); break;
        case 1: _t->on_pushButton_pattern_clicked(); break;
        case 2: _t->on_pushButton_play_clicked(); break;
        case 3: _t->onItemDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 4: _t->on_pushButton_under_clicked(); break;
        case 5: _t->on_pushButton_on_clicked(); break;
        case 6: _t->mediaPlylistCurrentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->musicPlyerDurationChanged((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 8: _t->musicPlyerPositionChanged((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 9: _t->musicPlyerStateChanged((*reinterpret_cast< QMediaPlayer::State(*)>(_a[1]))); break;
        case 10: _t->durationSliderReleased(); break;
        case 11: _t->on_volume_clicked(); break;
        case 12: _t->alter_lyric((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QMediaPlayer::State >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MusicPlay::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_MusicPlay.data,
    qt_meta_data_MusicPlay,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MusicPlay::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MusicPlay::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MusicPlay.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MusicPlay::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
