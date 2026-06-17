#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "camerareceiver.h"
#include "crabdetector.h"
#include "src/colmaprunner.h"

#include <QChart>
#include <QChartView>
#include <QFutureWatcher>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QLineSeries>
#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include <QValueAxis>

/*//%temp for testing on laptop (comment out later for actual cameras)
#include <QCamera>
#include <QMediaCaptureSession>
#include <QVideoSink>
#include <QVideoFrame>
//%*/


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class RovSetupPage;

class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // ── Main menu navigation ──────────────────────────────────────────────
    void on_cameraFeedPushButton_clicked();
    void on_modelingPushButton_clicked();
    void on_icebergPushButton_clicked();
    void on_ednaPushButton_clicked();
    void on_floatPushButton_clicked();

    // ── Home (back) buttons ───────────────────────────────────────────────
    void on_homePageButton_clicked();
    void on_homePageButton_2_clicked();
    void on_homePageButton_3_clicked();
    void on_homePageButton_4_clicked();
    void on_homePageButton_5_clicked();
    void on_homePageButton_6_clicked();

    // ── Misc ──────────────────────────────────────────────────────────────
    void on_pushButton_clicked();   // bottom-left settings → ROV Setup page
    void on_closeProgramButton_clicked();
    void on_pushButtonCalcPercent_clicked();

    // ── Camera view buttons ───────────────────────────────────────────────
    void on_frontCamButton_clicked();
    void on_leftCamButton_clicked();
    void on_rightCamButton_clicked();
    void on_botCamButton_clicked();
    void on_backCamButton_clicked();

    // ── Resolution / FPS mode toggle ──────────────────────────────────────
    void on_modeButton_clicked();

    // ── Frame capture to photogram_images ────────────────────────────────
    void on_captureFramesButton_clicked();

    // ── Camera receiver callbacks ─────────────────────────────────────────
    void onCameraFrame(const QImage &image);
    void onCameraConnected();
    void onCameraDisconnected();
    void onFpsUpdated(int fps);

    // ── Clock ─────────────────────────────────────────────────────────────
    void updateClock();

    // ── ALS telemetry ──────────────────────────────────────────────────────
    void onAlsDataReady(bool als, double pitch, double yaw);

    // ── Depth / pressure telemetry ────────────────────────────────────────
    void onTelemetryUpdated(double depth, double pressure);
    void on_btnRecordDepth_clicked();
    void updateLiveDepthDisplay(double depth);
    void on_btnUndoDepth_clicked();
    void updateIcebergPosition(double x, double y);

    // ── Photogrammetry ────────────────────────────────────────────────────
    void on_importImagesButton_clicked();
    void on_importVideoButton_clicked();
    void on_clearButton_clicked();
    void on_runButton_clicked();
    void on_cancelButton_clicked();
    void on_resetCameraButton_clicked();
    void on_loadPlyButton_clicked();
    void on_scaleButton_toggled(bool checked);
    void on_measureButton_toggled(bool checked);

    void onStepStarted(const QString &step);
    void onProgressOutput(const QString &line);
    void onStepFinished(const QString &step, bool success);
    void onPipelineFinished(bool success);
    void onError(const QString &error);
    void onScalePointsPicked(float measuredModelDist);

private:
    Ui::MainWindow *ui;

    // Crab detector
    CrabDetector m_crabDetector;

    // Camera network stream
    CameraReceiver *m_cameraReceiver = nullptr;

    /*//%temp for testing on laptop (comment out later for actual cameras)
    QCamera *m_webcam = nullptr;
    QMediaCaptureSession m_captureSession;
    QVideoSink *m_videoSink = nullptr;
    //%*/

    QGraphicsScene *m_scene = nullptr;
    QGraphicsPixmapItem *m_pixmapItem = nullptr;

    // HUD overlay labels (children of graphicsView, always on top)
    QLabel *m_hudDepth = nullptr;
    QLabel *m_hudPressure = nullptr;
    QLabel *m_hudLatency = nullptr;
    QLabel *m_hudAls = nullptr;

    // Clock timer (updates timeLabel every second)
    QTimer *m_clockTimer = nullptr;

    // Current capture mode ("live" or "hq")
    QString m_currentMode = "live";

    // Helpers
    void setActiveCamButton(const QString &name);
    void updateModeButton();

    // Helper for float charts
    void setupPressureChart();
    void setupDepthChart();
    void setupFloatDataTable();

    // Tactical Map
    QGraphicsScene *m_tacticalScene = nullptr;
    QGraphicsEllipseItem *m_icebergMarker = nullptr;
    QGraphicsLineItem *m_headingVector = nullptr;
    QGraphicsPolygonItem *m_icebergPerimeter = nullptr;

    int m_currentDepthIndex = 0;
    double m_maxKeelDepth = 0.0;
    double m_currentDepth = 0.0;

    void updateIcebergTracking(double iceX,
                               double iceY,
                               double headingDeg,
                               double maxKeelDepth,
                               QVector<QPointF> perimeterPoints);

    // Photogrammetry
    void setupPhotogrammetry();
    void setRunning(bool running);
    void refreshThumbnails();
    QString detectColmapPath();
    void convertAndLoadModel();

    ColmapRunner *m_runner = nullptr;
    QString m_workspacePath;
    QString m_imagePath;

    // ROV setup submenu (settingsPage)
    RovSetupPage *m_rovSetup = nullptr;

    // Frame capture
    bool m_capturingFrames = false;
    int m_frameCounter = 0;
    int m_captureCount = 0;
    QString m_photogramPath;

    // Crab detection keypress controls
    QVector<CrabDetector::Detection> m_lastDetections;

  // Detection runs on a worker thread so it never blocks the video display.
  QFutureWatcher<QVector<CrabDetector::Detection>> m_detWatcher;
  bool m_detRunning = false;
  int  m_detDispatchCounter = 0;
    int m_greenCrabCount = 0;
    bool m_detectionEnabled = true;
};

#endif // MAINWINDOW_H
