/****************************************************************************
** Meta object code from reading C++ file 'SimpleReminder.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../SimpleReminder.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SimpleReminder.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SimpleReminder_t {
    QByteArrayData data[16];
    char stringdata0[250];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SimpleReminder_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SimpleReminder_t qt_meta_stringdata_SimpleReminder = {
    {
QT_MOC_LITERAL(0, 0, 14), // "SimpleReminder"
QT_MOC_LITERAL(1, 15, 16), // "clickedRightMenu"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 3), // "pos"
QT_MOC_LITERAL(4, 37, 18), // "addActionTriggered"
QT_MOC_LITERAL(5, 56, 21), // "deleteActionTriggered"
QT_MOC_LITERAL(6, 78, 19), // "hideActionTriggered"
QT_MOC_LITERAL(7, 98, 22), // "showAllActionTriggered"
QT_MOC_LITERAL(8, 121, 21), // "periodActionTriggered"
QT_MOC_LITERAL(9, 143, 21), // "detailActionTriggered"
QT_MOC_LITERAL(10, 165, 13), // "doubleClicked"
QT_MOC_LITERAL(11, 179, 11), // "QModelIndex"
QT_MOC_LITERAL(12, 191, 14), // "showDockWidget"
QT_MOC_LITERAL(13, 206, 14), // "hideDockWidget"
QT_MOC_LITERAL(14, 221, 12), // "expireUpdate"
QT_MOC_LITERAL(15, 234, 15) // "dataPersistence"

    },
    "SimpleReminder\0clickedRightMenu\0\0pos\0"
    "addActionTriggered\0deleteActionTriggered\0"
    "hideActionTriggered\0showAllActionTriggered\0"
    "periodActionTriggered\0detailActionTriggered\0"
    "doubleClicked\0QModelIndex\0showDockWidget\0"
    "hideDockWidget\0expireUpdate\0dataPersistence"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SimpleReminder[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x0a /* Public */,
       4,    0,   77,    2, 0x0a /* Public */,
       5,    0,   78,    2, 0x0a /* Public */,
       6,    0,   79,    2, 0x0a /* Public */,
       7,    0,   80,    2, 0x0a /* Public */,
       8,    0,   81,    2, 0x0a /* Public */,
       9,    0,   82,    2, 0x0a /* Public */,
      10,    1,   83,    2, 0x0a /* Public */,
      12,    0,   86,    2, 0x0a /* Public */,
      13,    0,   87,    2, 0x0a /* Public */,
      14,    0,   88,    2, 0x0a /* Public */,
      15,    0,   89,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QPoint,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SimpleReminder::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SimpleReminder *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->clickedRightMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 1: _t->addActionTriggered(); break;
        case 2: _t->deleteActionTriggered(); break;
        case 3: _t->hideActionTriggered(); break;
        case 4: _t->showAllActionTriggered(); break;
        case 5: _t->periodActionTriggered(); break;
        case 6: _t->detailActionTriggered(); break;
        case 7: _t->doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 8: _t->showDockWidget(); break;
        case 9: _t->hideDockWidget(); break;
        case 10: _t->expireUpdate(); break;
        case 11: _t->dataPersistence(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SimpleReminder::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_SimpleReminder.data,
    qt_meta_data_SimpleReminder,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SimpleReminder::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SimpleReminder::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SimpleReminder.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int SimpleReminder::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
