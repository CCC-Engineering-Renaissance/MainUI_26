#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "camerareceiver.h"

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
  void onModeToggleClicked();

  // ── Camera receiver callbacks ─────────────────────────────────────────
  void onCameraFrame(const QImage &image);
  void onCameraConnected();
  void onCameraDisconnected();
  void onFpsUpdated(int fps);

  // ── Clock ─────────────────────────────────────────────────────────────
  void updateClock();

private:
  Ui::MainWindow *ui;

  // Camera network stream
  CameraReceiver       *m_cameraReceiver = nullptr;
  QGraphicsScene       *m_scene          = nullptr;
  QGraphicsPixmapItem  *m_pixmapItem     = nullptr;

  // Clock timer (updates timeLabel every second)
  QTimer *m_clockTimer = nullptr;

  // Current capture mode ("live" or "hq")
  QString      m_currentMode   = "live";
  QPushButton *m_modeButton    = nullptr;

  // Helpers
  void setActiveCamButton(const QString &name);
  void updateModeButton();

  // Helper for float charts
  void setupPressureChart();
  void setupDepthChart();
  void setupFloatDataTable();
};

#endif // MAINWINDOW_H
