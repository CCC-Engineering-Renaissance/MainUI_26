#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCamera>
#include <QGraphicsScene>
#include <QGraphicsVideoItem>
#include <QLabel>
#include <QMainWindow>
#include <QMediaCaptureSession>
#include <QMediaPlayer>
#include <QScopedPointer>
#include <QVideoWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
protected:
    void keyPressEvent(QKeyEvent *event) override;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_cameraFeedPushButton_clicked();

    void on_modelingPushButton_clicked();

    void on_icebergPushButton_clicked();

    void on_ednaPushButton_clicked();

    void on_floatPushButton_clicked();

    void on_homePageButton_clicked();

    void on_homePageButton_2_clicked();

    void on_homePageButton_5_clicked();

    void on_homePageButton_4_clicked();

    void on_homePageButton_3_clicked();

    void on_closeProgramButton_clicked();

    void on_homePageButton_6_clicked();

    void on_pushButtonCalcPercent_clicked();

    void on_frontCamButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *m_scene = nullptr;
    QGraphicsVideoItem *m_videoItem = nullptr;
    QScopedPointer<QCamera> m_camera;
    QScopedPointer<QMediaCaptureSession> m_captureSession;
};
#endif // MAINWINDOW_H
