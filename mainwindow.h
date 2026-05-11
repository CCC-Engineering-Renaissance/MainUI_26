#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "camerareceiver.h"
#include "src/colmaprunner.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include <QChart>
#include <QChartView>
#include <QValueAxis>
#include <QLineSeries>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

protected:
  void keyPressEvent(QKeyEvent *event) override;

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

  // ── Camera receiver callbacks ─────────────────────────────────────────
  void onCameraFrame(const QImage &image);
  void onCameraConnected();
  void onCameraDisconnected();
  void onFpsUpdated(int fps);

  // ── Clock ─────────────────────────────────────────────────────────────
  void updateClock();

  void on_btnRecordDepth_clicked();

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

  // Camera network stream
  CameraReceiver       *m_cameraReceiver = nullptr;
  QGraphicsScene       *m_scene          = nullptr;
  QGraphicsPixmapItem  *m_pixmapItem     = nullptr;

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
  QGraphicsScene       *m_tacticalScene = nullptr;
  QGraphicsEllipseItem *m_icebergMarker = nullptr;
  QGraphicsLineItem    *m_headingVector = nullptr;
  QGraphicsPolygonItem *m_icebergPerimeter = nullptr;

  int m_currentDepthIndex = 0;
  double m_maxKeelDepth = 0.0;

  void updateIcebergTracking(double iceX, double iceY, double headingDeg, double maxKeelDepth, QVector<QPointF> perimeterPoints);

  // Photogrammetry
  void setupPhotogrammetry();
  void setRunning(bool running);
  void refreshThumbnails();
  QString detectColmapPath();
  void convertAndLoadModel();

  ColmapRunner *m_runner       = nullptr;
  QString       m_workspacePath;
  QString       m_imagePath;
};

#endif // MAINWINDOW_H
