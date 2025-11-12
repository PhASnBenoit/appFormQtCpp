/****************************************************************************
** Meta object code from reading C++ file 'cgui.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../cgui.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cgui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN4CGuiE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN4CGuiE = QtMocHelpers::stringData(
    "CGui",
    "sig_erreur",
    "",
    "mess",
    "sig_goBp",
    "sig_goCapt",
    "on_pbStartStop_clicked",
    "on_pbOnOffLed_clicked",
    "on_pbLcd_clicked",
    "on_erreur",
    "on_etatBouton",
    "etat",
    "on_timerMes",
    "on_timerSgbd",
    "on_timerServeur",
    "on_timerLcd",
    "on_finished",
    "on_recevoirDataDuPeriph",
    "data",
    "on_pbEnvoyer_clicked"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN4CGuiE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  104,    2, 0x06,    1 /* Public */,
       4,    0,  107,    2, 0x06,    3 /* Public */,
       5,    0,  108,    2, 0x06,    4 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       6,    0,  109,    2, 0x08,    5 /* Private */,
       7,    0,  110,    2, 0x08,    6 /* Private */,
       8,    0,  111,    2, 0x08,    7 /* Private */,
       9,    1,  112,    2, 0x08,    8 /* Private */,
      10,    1,  115,    2, 0x08,   10 /* Private */,
      12,    0,  118,    2, 0x08,   12 /* Private */,
      13,    0,  119,    2, 0x08,   13 /* Private */,
      14,    0,  120,    2, 0x08,   14 /* Private */,
      15,    0,  121,    2, 0x08,   15 /* Private */,
      16,    0,  122,    2, 0x08,   16 /* Private */,
      17,    1,  123,    2, 0x08,   17 /* Private */,
      19,    0,  126,    2, 0x08,   19 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   18,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject CGui::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_ZN4CGuiE.offsetsAndSizes,
    qt_meta_data_ZN4CGuiE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN4CGuiE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<CGui, std::true_type>,
        // method 'sig_erreur'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'sig_goBp'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sig_goCapt'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pbStartStop_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pbOnOffLed_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pbLcd_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_erreur'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'on_etatBouton'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'on_timerMes'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_timerSgbd'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_timerServeur'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_timerLcd'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_finished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_recevoirDataDuPeriph'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'on_pbEnvoyer_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void CGui::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<CGui *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->sig_erreur((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->sig_goBp(); break;
        case 2: _t->sig_goCapt(); break;
        case 3: _t->on_pbStartStop_clicked(); break;
        case 4: _t->on_pbOnOffLed_clicked(); break;
        case 5: _t->on_pbLcd_clicked(); break;
        case 6: _t->on_erreur((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->on_etatBouton((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 8: _t->on_timerMes(); break;
        case 9: _t->on_timerSgbd(); break;
        case 10: _t->on_timerServeur(); break;
        case 11: _t->on_timerLcd(); break;
        case 12: _t->on_finished(); break;
        case 13: _t->on_recevoirDataDuPeriph((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 14: _t->on_pbEnvoyer_clicked(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (CGui::*)(QString );
            if (_q_method_type _q_method = &CGui::sig_erreur; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (CGui::*)();
            if (_q_method_type _q_method = &CGui::sig_goBp; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (CGui::*)();
            if (_q_method_type _q_method = &CGui::sig_goCapt; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject *CGui::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CGui::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN4CGuiE.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int CGui::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void CGui::sig_erreur(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CGui::sig_goBp()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void CGui::sig_goCapt()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
