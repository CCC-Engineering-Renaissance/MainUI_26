#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QLabel>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QTimer>
#include <opencv2/opencv.hpp>


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

    void startFrontCamera();

    void stopCamera();

    void updateFrame();

private:
    Ui::MainWindow *ui;

    cv::VideoCapture cap;
    QTimer *timer;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *pixmapItem;
};
#endif // MAINWINDOW_H
