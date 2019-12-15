/****************************************************************************
** Meta object code from reading C++ file 'view.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ui/view.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'view.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_View_t {
    QByteArrayData data[24];
    char stringdata0[286];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_View_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_View_t qt_meta_stringdata_View = {
    {
QT_MOC_LITERAL(0, 0, 4), // "View"
QT_MOC_LITERAL(1, 5, 10), // "addUniform"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 21), // "UniformVariable::Type"
QT_MOC_LITERAL(4, 39, 4), // "type"
QT_MOC_LITERAL(5, 44, 4), // "name"
QT_MOC_LITERAL(6, 49, 8), // "editable"
QT_MOC_LITERAL(7, 58, 4), // "size"
QT_MOC_LITERAL(8, 63, 16), // "UniformVariable*"
QT_MOC_LITERAL(9, 80, 7), // "uniform"
QT_MOC_LITERAL(10, 88, 13), // "changeUniform"
QT_MOC_LITERAL(11, 102, 22), // "const UniformVariable*"
QT_MOC_LITERAL(12, 125, 6), // "newVal"
QT_MOC_LITERAL(13, 132, 14), // "uniformDeleted"
QT_MOC_LITERAL(14, 147, 12), // "uniformAdded"
QT_MOC_LITERAL(15, 160, 11), // "viewChanged"
QT_MOC_LITERAL(16, 172, 9), // "glm::mat4"
QT_MOC_LITERAL(17, 182, 9), // "modelview"
QT_MOC_LITERAL(18, 192, 17), // "projectionChanged"
QT_MOC_LITERAL(19, 210, 10), // "projection"
QT_MOC_LITERAL(20, 221, 26), // "modelviewProjectionChanged"
QT_MOC_LITERAL(21, 248, 19), // "modelviewProjection"
QT_MOC_LITERAL(22, 268, 12), // "modelChanged"
QT_MOC_LITERAL(23, 281, 4) // "tick"

    },
    "View\0addUniform\0\0UniformVariable::Type\0"
    "type\0name\0editable\0size\0UniformVariable*\0"
    "uniform\0changeUniform\0const UniformVariable*\0"
    "newVal\0uniformDeleted\0uniformAdded\0"
    "viewChanged\0glm::mat4\0modelview\0"
    "projectionChanged\0projection\0"
    "modelviewProjectionChanged\0"
    "modelviewProjection\0modelChanged\0tick"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_View[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   84,    2, 0x06 /* Public */,
       1,    3,   93,    2, 0x26 /* Public | MethodCloned */,
       1,    2,  100,    2, 0x26 /* Public | MethodCloned */,
       1,    2,  105,    2, 0x06 /* Public */,
       1,    1,  110,    2, 0x26 /* Public | MethodCloned */,
      10,    2,  113,    2, 0x06 /* Public */,
      10,    2,  118,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    1,  123,    2, 0x0a /* Public */,
      14,    1,  126,    2, 0x0a /* Public */,
      15,    1,  129,    2, 0x0a /* Public */,
      18,    1,  132,    2, 0x0a /* Public */,
      20,    1,  135,    2, 0x0a /* Public */,
      22,    1,  138,    2, 0x0a /* Public */,
      23,    0,  141,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString, QMetaType::Bool, QMetaType::Int,    4,    5,    6,    7,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString, QMetaType::Bool,    4,    5,    6,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString,    4,    5,
    QMetaType::Void, 0x80000000 | 8, QMetaType::Bool,    9,    6,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 11, QMetaType::QString,    9,   12,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    5,   12,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 11,    9,
    QMetaType::Void, 0x80000000 | 11,    9,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, 0x80000000 | 16,   19,
    QMetaType::Void, 0x80000000 | 16,   21,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void,

       0        // eod
};

void View::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        View *_t = static_cast<View *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->addUniform((*reinterpret_cast< UniformVariable::Type(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 1: _t->addUniform((*reinterpret_cast< UniformVariable::Type(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 2: _t->addUniform((*reinterpret_cast< UniformVariable::Type(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: _t->addUniform((*reinterpret_cast< UniformVariable*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 4: _t->addUniform((*reinterpret_cast< UniformVariable*(*)>(_a[1]))); break;
        case 5: _t->changeUniform((*reinterpret_cast< const UniformVariable*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 6: _t->changeUniform((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 7: _t->uniformDeleted((*reinterpret_cast< const UniformVariable*(*)>(_a[1]))); break;
        case 8: _t->uniformAdded((*reinterpret_cast< const UniformVariable*(*)>(_a[1]))); break;
        case 9: _t->viewChanged((*reinterpret_cast< const glm::mat4(*)>(_a[1]))); break;
        case 10: _t->projectionChanged((*reinterpret_cast< const glm::mat4(*)>(_a[1]))); break;
        case 11: _t->modelviewProjectionChanged((*reinterpret_cast< const glm::mat4(*)>(_a[1]))); break;
        case 12: _t->modelChanged((*reinterpret_cast< const glm::mat4(*)>(_a[1]))); break;
        case 13: _t->tick(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (View::*)(UniformVariable::Type , const QString & , bool , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&View::addUniform)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (View::*)(UniformVariable * , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&View::addUniform)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (View::*)(const UniformVariable * , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&View::changeUniform)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (View::*)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&View::changeUniform)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject View::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_View.data,
      qt_meta_data_View,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *View::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *View::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_View.stringdata0))
        return static_cast<void*>(this);
    return QGLWidget::qt_metacast(_clname);
}

int View::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
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
void View::addUniform(UniformVariable::Type _t1, const QString & _t2, bool _t3, int _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 3
void View::addUniform(UniformVariable * _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 5
void View::changeUniform(const UniformVariable * _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void View::changeUniform(const QString & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
