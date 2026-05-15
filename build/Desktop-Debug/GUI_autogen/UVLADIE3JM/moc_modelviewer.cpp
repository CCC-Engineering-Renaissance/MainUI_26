/****************************************************************************
** Meta object code from reading C++ file 'modelviewer.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/modelviewer.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modelviewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.2. It"
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
struct qt_meta_tag_ZN11ModelViewerE_t {};
} // unnamed namespace

template <> constexpr inline auto ModelViewer::qt_create_metaobjectdata<qt_meta_tag_ZN11ModelViewerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ModelViewer",
        "scalePointsPicked",
        "",
        "measuredModelDist",
        "scaleApplied",
        "widthM",
        "heightM",
        "depthM",
        "measurementReady",
        "totalM",
        "dxM",
        "dyM",
        "dzM"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'scalePointsPicked'
        QtMocHelpers::SignalData<void(float)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Float, 3 },
        }}),
        // Signal 'scaleApplied'
        QtMocHelpers::SignalData<void(float, float, float)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Float, 5 }, { QMetaType::Float, 6 }, { QMetaType::Float, 7 },
        }}),
        // Signal 'measurementReady'
        QtMocHelpers::SignalData<void(float, float, float, float)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Float, 9 }, { QMetaType::Float, 10 }, { QMetaType::Float, 11 }, { QMetaType::Float, 12 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ModelViewer, qt_meta_tag_ZN11ModelViewerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ModelViewer::staticMetaObject = { {
    QMetaObject::SuperData::link<QOpenGLWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11ModelViewerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11ModelViewerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11ModelViewerE_t>.metaTypes,
    nullptr
} };

void ModelViewer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ModelViewer *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->scalePointsPicked((*reinterpret_cast<std::add_pointer_t<float>>(_a[1]))); break;
        case 1: _t->scaleApplied((*reinterpret_cast<std::add_pointer_t<float>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<float>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<float>>(_a[3]))); break;
        case 2: _t->measurementReady((*reinterpret_cast<std::add_pointer_t<float>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<float>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<float>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<float>>(_a[4]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ModelViewer::*)(float )>(_a, &ModelViewer::scalePointsPicked, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ModelViewer::*)(float , float , float )>(_a, &ModelViewer::scaleApplied, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (ModelViewer::*)(float , float , float , float )>(_a, &ModelViewer::measurementReady, 2))
            return;
    }
}

const QMetaObject *ModelViewer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ModelViewer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11ModelViewerE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QOpenGLFunctions"))
        return static_cast< QOpenGLFunctions*>(this);
    return QOpenGLWidget::qt_metacast(_clname);
}

int ModelViewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QOpenGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void ModelViewer::scalePointsPicked(float _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void ModelViewer::scaleApplied(float _t1, float _t2, float _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1, _t2, _t3);
}

// SIGNAL 2
void ModelViewer::measurementReady(float _t1, float _t2, float _t3, float _t4)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1, _t2, _t3, _t4);
}
QT_WARNING_POP
