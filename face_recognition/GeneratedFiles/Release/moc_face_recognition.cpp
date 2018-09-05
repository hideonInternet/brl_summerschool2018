/****************************************************************************
** Meta object code from reading C++ file 'face_recognition.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../face_recognition.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'face_recognition.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_face_recognition_t {
    QByteArrayData data[13];
    char stringdata0[155];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_face_recognition_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_face_recognition_t qt_meta_stringdata_face_recognition = {
    {
QT_MOC_LITERAL(0, 0, 16), // "face_recognition"
QT_MOC_LITERAL(1, 17, 6), // "search"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 6), // "rsopen"
QT_MOC_LITERAL(4, 32, 9), // "rstime_on"
QT_MOC_LITERAL(5, 42, 10), // "rstime_off"
QT_MOC_LITERAL(6, 53, 19), // "setStackCurrentPage"
QT_MOC_LITERAL(7, 73, 5), // "index"
QT_MOC_LITERAL(8, 79, 15), // "click_enroll_on"
QT_MOC_LITERAL(9, 95, 13), // "click_home_on"
QT_MOC_LITERAL(10, 109, 15), // "click_search_on"
QT_MOC_LITERAL(11, 125, 17), // "RGB_D_img_capture"
QT_MOC_LITERAL(12, 143, 11) // "recognition"

    },
    "face_recognition\0search\0\0rsopen\0"
    "rstime_on\0rstime_off\0setStackCurrentPage\0"
    "index\0click_enroll_on\0click_home_on\0"
    "click_search_on\0RGB_D_img_capture\0"
    "recognition"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_face_recognition[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    0,   67,    2, 0x08 /* Private */,
       6,    1,   68,    2, 0x08 /* Private */,
       8,    0,   71,    2, 0x08 /* Private */,
       9,    0,   72,    2, 0x08 /* Private */,
      10,    0,   73,    2, 0x08 /* Private */,
      11,    0,   74,    2, 0x08 /* Private */,
      12,    0,   75,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UChar,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void face_recognition::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        face_recognition *_t = static_cast<face_recognition *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->search(); break;
        case 1: _t->rsopen(); break;
        case 2: _t->rstime_on(); break;
        case 3: _t->rstime_off(); break;
        case 4: _t->setStackCurrentPage((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 5: _t->click_enroll_on(); break;
        case 6: _t->click_home_on(); break;
        case 7: _t->click_search_on(); break;
        case 8: _t->RGB_D_img_capture(); break;
        case 9: _t->recognition(); break;
        default: ;
        }
    }
}

const QMetaObject face_recognition::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_face_recognition.data,
      qt_meta_data_face_recognition,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *face_recognition::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *face_recognition::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_face_recognition.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int face_recognition::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
