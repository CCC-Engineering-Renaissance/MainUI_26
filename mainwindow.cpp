#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "src/photogrammetrywidget.h"
#include <QCamera>
#include <QCoreApplication>
#include <QDateTime>
#include <QFontDatabase>
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <QGraphicsVideoItem>
#include <QKeyEvent>
#include <QLCDNumber>
#include <QLabel>
#include <QMediaCaptureSession>
#include <QMediaDevices>
#include <QMediaPlayer>
#include <QPermissions>
#include <QPixmap>
#include <QSpinBox>
#include <QString>
#include <QVBoxLayout>
#include <QVideoWidget>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(1200, 800);
    setMinimumSize(900, 600);

    // Embed photogrammetry widget into the modeling page (stacked widget index 2)
    QWidget *modelingPage = ui->stackedWidget->widget(2);
    auto *photogrammetry = new PhotogrammetryWidget(modelingPage);
    auto *pageLayout = new QVBoxLayout(modelingPage);
    pageLayout->setContentsMargins(0, 0, 0, 0);
    pageLayout->addWidget(photogrammetry);

    // image setup
    QPixmap pixmap(":/images/images/rov_logo_complete.png");
    if (pixmap.isNull()) {
        ui->crush_label->setText("Error: Logo not found!");
    } else {
        int maxWidth = 250;
        int maxHeight = 250;
        QPixmap scaledPixmap = pixmap.scaled(
            maxWidth, maxHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->crush_label->setPixmap(scaledPixmap);
        ui->crush_label->setAlignment(Qt::AlignCenter);
    }

    // font correction
    int fontId =
        QFontDatabase::addApplicationFont(":/font/fonts/aileron.black.otf");

    if (fontId == -1) {
        qDebug() << "Warning: Custom font failed to load from resources!";
    } else {
        QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
        qDebug() << "Success! The font family name is:" << fontFamily;
    }
}

MainWindow::~MainWindow() { delete ui; }

/// User can press escape at any screen to go back to the main menu

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        if (ui->stackedWidget->currentIndex() != 0) {
            ui->stackedWidget->setCurrentIndex(0);
        }
    } else {
        QMainWindow::keyPressEvent(event);
    }
}

/// Main menu button logic

void MainWindow::on_cameraFeedPushButton_clicked() {
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_modelingPushButton_clicked() {
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_icebergPushButton_clicked() {
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_ednaPushButton_clicked() {
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_floatPushButton_clicked() {
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_homePageButton_clicked() {
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_homePageButton_2_clicked() {
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_homePageButton_3_clicked() {
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_homePageButton_4_clicked() {
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_homePageButton_5_clicked() {
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_homePageButton_6_clicked() {
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_closeProgramButton_clicked() { close(); }

/// eDNA Percentage Calculator Function

void MainWindow::on_pushButtonCalcPercent_clicked() {
    int snowInput = ui->spinBoxSnow->value();
    int acadianInput = ui->spinBoxAcadian->value();
    int westernInput = ui->spinBoxWestern->value();
    int urchinInput = ui->spinBoxUrchin->value();
    int rockInput = ui->spinBoxRock->value();
    int jonahInput = ui->spinBoxJonah->value();
    int sunstarInput = ui->spinBoxSunstar->value();
    int greenInput = ui->spinBoxGreen->value();
    int borealInput = ui->spinBoxBoreal->value();
    int brittleInput = ui->spinBoxBrittle->value();
    double sumOfInputs = snowInput + acadianInput + westernInput + urchinInput +
                         rockInput + jonahInput + sunstarInput + greenInput +
                         borealInput + brittleInput;

    double snowPercent = (snowInput / sumOfInputs) * 100;
    double acadianPercent = (acadianInput / sumOfInputs) * 100;
    double westernPercent = (westernInput / sumOfInputs) * 100;
    double seaUrchinPercent = (urchinInput / sumOfInputs) * 100;
    double rockPercent = (rockInput / sumOfInputs) * 100;
    double jonahPercent = (jonahInput / sumOfInputs) * 100;
    double spinySunstarPercent = (sunstarInput / sumOfInputs) * 100;
    double greenPercent = (greenInput / sumOfInputs) * 100;
    double borealStarPercent = (borealInput / sumOfInputs) * 100;
    double brittleStarPercent = (brittleInput / sumOfInputs) * 100;

    ui->snowCrabPercent->display(snowPercent);
    ui->acadianCrabPercent->display(acadianPercent);
    ui->hairyCrabPercent->display(westernPercent);
    ui->urchinPercent->display(seaUrchinPercent);
    ui->rockCrabPercent->display(rockPercent);
    ui->jonahCrabPercent->display(jonahPercent);
    ui->sunstarPercent->display(spinySunstarPercent);
    ui->greenCrabPercent->display(greenPercent);
    ui->borealPercent->display(borealStarPercent);
    ui->brittlePercent->display(brittleStarPercent);
}

void MainWindow::on_frontCamButton_clicked() {
    QCameraPermission cameraPermission;

    switch (qApp->checkPermission(cameraPermission)) {
    case Qt::PermissionStatus::Undetermined:
        qApp->requestPermission(cameraPermission, this,
                                &MainWindow::on_frontCamButton_clicked);
        return;
    case Qt::PermissionStatus::Denied:
        qDebug() << "Camera permission was denied.";
        return;
    case Qt::PermissionStatus::Granted:
        break;
    }

    m_scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(m_scene);

    m_videoItem = new QGraphicsVideoItem();
    m_scene->addItem(m_videoItem);
    m_videoItem->setSize(ui->graphicsView->size());

    QCameraDevice defaultCam = QMediaDevices::defaultVideoInput();
    if (defaultCam.isNull())
        return;

    m_camera.reset(new QCamera(defaultCam));
    m_captureSession.reset(new QMediaCaptureSession);

    m_captureSession->setCamera(m_camera.data());
    m_captureSession->setVideoOutput(m_videoItem);

    m_camera->start();
}
