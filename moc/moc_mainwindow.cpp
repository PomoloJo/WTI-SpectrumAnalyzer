/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../include/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[22];
    char stringdata0[433];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 11), // "eventFilter"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 7), // "QEvent*"
QT_MOC_LITERAL(4, 32, 20), // "on_btn_start_clicked"
QT_MOC_LITERAL(5, 53, 20), // "on_btn_close_clicked"
QT_MOC_LITERAL(6, 74, 18), // "on_btn_max_clicked"
QT_MOC_LITERAL(7, 93, 18), // "on_btn_min_clicked"
QT_MOC_LITERAL(8, 112, 39), // "on_horizontalSlider_offset_va..."
QT_MOC_LITERAL(9, 152, 12), // "slider_value"
QT_MOC_LITERAL(10, 165, 30), // "on_spinBox_offset_valueChanged"
QT_MOC_LITERAL(11, 196, 13), // "spinbox_value"
QT_MOC_LITERAL(12, 210, 16), // "plotStatusChange"
QT_MOC_LITERAL(13, 227, 29), // "on_checkBox_threshold_clicked"
QT_MOC_LITERAL(14, 257, 28), // "on_radioButton_level_clicked"
QT_MOC_LITERAL(15, 286, 27), // "on_radioButton_auto_clicked"
QT_MOC_LITERAL(16, 314, 27), // "on_radioButton_peak_clicked"
QT_MOC_LITERAL(17, 342, 30), // "on_radioButton_history_clicked"
QT_MOC_LITERAL(18, 373, 22), // "on_btn_history_clicked"
QT_MOC_LITERAL(19, 396, 12), // "timeToReplot"
QT_MOC_LITERAL(20, 409, 13), // "const double*"
QT_MOC_LITERAL(21, 423, 9) // "point_num"

    },
    "MainWindow\0eventFilter\0\0QEvent*\0"
    "on_btn_start_clicked\0on_btn_close_clicked\0"
    "on_btn_max_clicked\0on_btn_min_clicked\0"
    "on_horizontalSlider_offset_valueChanged\0"
    "slider_value\0on_spinBox_offset_valueChanged\0"
    "spinbox_value\0plotStatusChange\0"
    "on_checkBox_threshold_clicked\0"
    "on_radioButton_level_clicked\0"
    "on_radioButton_auto_clicked\0"
    "on_radioButton_peak_clicked\0"
    "on_radioButton_history_clicked\0"
    "on_btn_history_clicked\0timeToReplot\0"
    "const double*\0point_num"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   89,    2, 0x0a /* Public */,
       4,    0,   94,    2, 0x08 /* Private */,
       5,    0,   95,    2, 0x08 /* Private */,
       6,    0,   96,    2, 0x08 /* Private */,
       7,    0,   97,    2, 0x08 /* Private */,
       8,    1,   98,    2, 0x08 /* Private */,
      10,    1,  101,    2, 0x08 /* Private */,
      12,    0,  104,    2, 0x08 /* Private */,
      13,    0,  105,    2, 0x08 /* Private */,
      14,    0,  106,    2, 0x08 /* Private */,
      15,    0,  107,    2, 0x08 /* Private */,
      16,    0,  108,    2, 0x08 /* Private */,
      17,    0,  109,    2, 0x08 /* Private */,
      18,    0,  110,    2, 0x08 /* Private */,
      19,    2,  111,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Bool, QMetaType::QObjectStar, 0x80000000 | 3,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 20, QMetaType::Int,    2,   21,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { bool _r = _t->eventFilter((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QEvent*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 1: _t->on_btn_start_clicked(); break;
        case 2: _t->on_btn_close_clicked(); break;
        case 3: _t->on_btn_max_clicked(); break;
        case 4: _t->on_btn_min_clicked(); break;
        case 5: _t->on_horizontalSlider_offset_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_spinBox_offset_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->plotStatusChange(); break;
        case 8: _t->on_checkBox_threshold_clicked(); break;
        case 9: _t->on_radioButton_level_clicked(); break;
        case 10: _t->on_radioButton_auto_clicked(); break;
        case 11: _t->on_radioButton_peak_clicked(); break;
        case 12: _t->on_radioButton_history_clicked(); break;
        case 13: _t->on_btn_history_clicked(); break;
        case 14: _t->timeToReplot((*reinterpret_cast< const double*(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
