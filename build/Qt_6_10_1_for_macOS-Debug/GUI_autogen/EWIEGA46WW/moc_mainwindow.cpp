/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.1. It"
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
struct qt_meta_tag_ZN10MainWindowE_t {};
} // unnamed namespace

template <> constexpr inline auto MainWindow::qt_create_metaobjectdata<qt_meta_tag_ZN10MainWindowE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MainWindow",
        "on_cameraFeedPushButton_clicked",
        "",
        "on_modelingPushButton_clicked",
        "on_icebergPushButton_clicked",
        "on_ednaPushButton_clicked",
        "on_floatPushButton_clicked",
        "on_homePageButton_clicked",
        "on_homePageButton_2_clicked",
        "on_homePageButton_3_clicked",
        "on_homePageButton_4_clicked",
        "on_homePageButton_5_clicked",
        "on_homePageButton_6_clicked",
        "on_pushButton_clicked",
        "on_closeProgramButton_clicked",
        "on_pushButtonCalcPercent_clicked",
        "on_frontCamButton_clicked",
        "on_leftCamButton_clicked",
        "on_rightCamButton_clicked",
        "on_botCamButton_clicked",
        "on_backCamButton_clicked",
        "on_modeButton_clicked",
        "on_captureFramesButton_clicked",
        "onCameraFrame",
        "QImage",
        "image",
        "onCameraConnected",
        "onCameraDisconnected",
        "onFpsUpdated",
        "fps",
        "updateClock",
        "onAlsDataReady",
        "als",
        "pitch",
        "yaw",
        "onTelemetryUpdated",
        "depth",
        "pressure",
        "on_btnRecordDepth_clicked",
        "updateLiveDepthDisplay",
        "updateIcebergAnalysis",
        "updateIcebergPosition",
        "x",
        "y",
        "on_importImagesButton_clicked",
        "on_importVideoButton_clicked",
        "on_clearButton_clicked",
        "on_runButton_clicked",
        "on_cancelButton_clicked",
        "on_resetCameraButton_clicked",
        "on_loadPlyButton_clicked",
        "on_scaleButton_toggled",
        "checked",
        "on_measureButton_toggled",
        "onStepStarted",
        "step",
        "onProgressOutput",
        "line",
        "onStepFinished",
        "success",
        "onPipelineFinished",
        "onError",
        "error",
        "onScalePointsPicked",
        "measuredModelDist"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'on_cameraFeedPushButton_clicked'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_modelingPushButton_clicked'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_icebergPushButton_clicked'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_ednaPushButton_clicked'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_floatPushButton_clicked'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_homePageButton_clicked'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_homePageButton_2_clicked'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_homePageButton_3_clicked'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_homePageButton_4_clicked'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_homePageButton_5_clicked'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_homePageButton_6_clicked'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_clicked'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_closeProgramButton_clicked'
        QtMocHelpers::SlotData<void()>(14, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButtonCalcPercent_clicked'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_frontCamButton_clicked'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_leftCamButton_clicked'
        QtMocHelpers::SlotData<void()>(17, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_rightCamButton_clicked'
        QtMocHelpers::SlotData<void()>(18, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_botCamButton_clicked'
        QtMocHelpers::SlotData<void()>(19, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_backCamButton_clicked'
        QtMocHelpers::SlotData<void()>(20, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_modeButton_clicked'
        QtMocHelpers::SlotData<void()>(21, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_captureFramesButton_clicked'
        QtMocHelpers::SlotData<void()>(22, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onCameraFrame'
        QtMocHelpers::SlotData<void(const QImage &)>(23, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 24, 25 },
        }}),
        // Slot 'onCameraConnected'
        QtMocHelpers::SlotData<void()>(26, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onCameraDisconnected'
        QtMocHelpers::SlotData<void()>(27, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onFpsUpdated'
        QtMocHelpers::SlotData<void(int)>(28, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 29 },
        }}),
        // Slot 'updateClock'
        QtMocHelpers::SlotData<void()>(30, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onAlsDataReady'
        QtMocHelpers::SlotData<void(bool, double, double)>(31, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 32 }, { QMetaType::Double, 33 }, { QMetaType::Double, 34 },
        }}),
        // Slot 'onTelemetryUpdated'
        QtMocHelpers::SlotData<void(double, double)>(35, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Double, 36 }, { QMetaType::Double, 37 },
        }}),
        // Slot 'on_btnRecordDepth_clicked'
        QtMocHelpers::SlotData<void()>(38, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'updateLiveDepthDisplay'
        QtMocHelpers::SlotData<void(double)>(39, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Double, 36 },
        }}),
        // Slot 'updateIcebergAnalysis'
        QtMocHelpers::SlotData<void()>(40, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'updateIcebergPosition'
        QtMocHelpers::SlotData<void(double, double)>(41, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Double, 42 }, { QMetaType::Double, 43 },
        }}),
        // Slot 'on_importImagesButton_clicked'
        QtMocHelpers::SlotData<void()>(44, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_importVideoButton_clicked'
        QtMocHelpers::SlotData<void()>(45, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_clearButton_clicked'
        QtMocHelpers::SlotData<void()>(46, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_runButton_clicked'
        QtMocHelpers::SlotData<void()>(47, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_cancelButton_clicked'
        QtMocHelpers::SlotData<void()>(48, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_resetCameraButton_clicked'
        QtMocHelpers::SlotData<void()>(49, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_loadPlyButton_clicked'
        QtMocHelpers::SlotData<void()>(50, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_scaleButton_toggled'
        QtMocHelpers::SlotData<void(bool)>(51, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 52 },
        }}),
        // Slot 'on_measureButton_toggled'
        QtMocHelpers::SlotData<void(bool)>(53, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 52 },
        }}),
        // Slot 'onStepStarted'
        QtMocHelpers::SlotData<void(const QString &)>(54, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 55 },
        }}),
        // Slot 'onProgressOutput'
        QtMocHelpers::SlotData<void(const QString &)>(56, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 57 },
        }}),
        // Slot 'onStepFinished'
        QtMocHelpers::SlotData<void(const QString &, bool)>(58, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 55 }, { QMetaType::Bool, 59 },
        }}),
        // Slot 'onPipelineFinished'
        QtMocHelpers::SlotData<void(bool)>(60, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 59 },
        }}),
        // Slot 'onError'
        QtMocHelpers::SlotData<void(const QString &)>(61, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 62 },
        }}),
        // Slot 'onScalePointsPicked'
        QtMocHelpers::SlotData<void(float)>(63, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Float, 64 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<MainWindow, qt_meta_tag_ZN10MainWindowE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10MainWindowE_t>.metaTypes,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MainWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->on_cameraFeedPushButton_clicked(); break;
        case 1: _t->on_modelingPushButton_clicked(); break;
        case 2: _t->on_icebergPushButton_clicked(); break;
        case 3: _t->on_ednaPushButton_clicked(); break;
        case 4: _t->on_floatPushButton_clicked(); break;
        case 5: _t->on_homePageButton_clicked(); break;
        case 6: _t->on_homePageButton_2_clicked(); break;
        case 7: _t->on_homePageButton_3_clicked(); break;
        case 8: _t->on_homePageButton_4_clicked(); break;
        case 9: _t->on_homePageButton_5_clicked(); break;
        case 10: _t->on_homePageButton_6_clicked(); break;
        case 11: _t->on_pushButton_clicked(); break;
        case 12: _t->on_closeProgramButton_clicked(); break;
        case 13: _t->on_pushButtonCalcPercent_clicked(); break;
        case 14: _t->on_frontCamButton_clicked(); break;
        case 15: _t->on_leftCamButton_clicked(); break;
        case 16: _t->on_rightCamButton_clicked(); break;
        case 17: _t->on_botCamButton_clicked(); break;
        case 18: _t->on_backCamButton_clicked(); break;
        case 19: _t->on_modeButton_clicked(); break;
        case 20: _t->on_captureFramesButton_clicked(); break;
        case 21: _t->onCameraFrame((*reinterpret_cast<std::add_pointer_t<QImage>>(_a[1]))); break;
        case 22: _t->onCameraConnected(); break;
        case 23: _t->onCameraDisconnected(); break;
        case 24: _t->onFpsUpdated((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 25: _t->updateClock(); break;
        case 26: _t->onAlsDataReady((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[3]))); break;
        case 27: _t->onTelemetryUpdated((*reinterpret_cast<std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[2]))); break;
        case 28: _t->on_btnRecordDepth_clicked(); break;
        case 29: _t->updateLiveDepthDisplay((*reinterpret_cast<std::add_pointer_t<double>>(_a[1]))); break;
        case 30: _t->updateIcebergAnalysis(); break;
        case 31: _t->updateIcebergPosition((*reinterpret_cast<std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[2]))); break;
        case 32: _t->on_importImagesButton_clicked(); break;
        case 33: _t->on_importVideoButton_clicked(); break;
        case 34: _t->on_clearButton_clicked(); break;
        case 35: _t->on_runButton_clicked(); break;
        case 36: _t->on_cancelButton_clicked(); break;
        case 37: _t->on_resetCameraButton_clicked(); break;
        case 38: _t->on_loadPlyButton_clicked(); break;
        case 39: _t->on_scaleButton_toggled((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 40: _t->on_measureButton_toggled((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 41: _t->onStepStarted((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 42: _t->onProgressOutput((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 43: _t->onStepFinished((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[2]))); break;
        case 44: _t->onPipelineFinished((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 45: _t->onError((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 46: _t->onScalePointsPicked((*reinterpret_cast<std::add_pointer_t<float>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.strings))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 47)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 47;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 47)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 47;
    }
    return _id;
}
QT_WARNING_POP
