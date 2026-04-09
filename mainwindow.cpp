#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "src/photogrammetrywidget.h"

#include <QDateTime>
#include <QDebug>
#include <QFontDatabase>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QLCDNumber>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QSpinBox>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>

// ─────────────────────────────────────────────────────────────────────────────
// Construction / destruction
// ─────────────────────────────────────────────────────────────────────────────

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(1200, 800);
    setMinimumSize(900, 600);

    // ── Photogrammetry widget ─────────────────────────────────────────────
    QWidget *modelingPage = ui->stackedWidget->widget(2);
    auto *photogrammetry  = new PhotogrammetryWidget(modelingPage);
    auto *pageLayout      = new QVBoxLayout(modelingPage);
    pageLayout->setContentsMargins(0, 0, 0, 0);
    pageLayout->addWidget(photogrammetry);

    // ── Logo ──────────────────────────────────────────────────────────────
    QPixmap pixmap(":/images/images/rov_logo_complete.png");
    if (pixmap.isNull()) {
        ui->crush_label->setText("Error: Logo not found!");
    } else {
        QPixmap scaled = pixmap.scaled(250, 250,
                                       Qt::KeepAspectRatio,
                                       Qt::SmoothTransformation);
        ui->crush_label->setPixmap(scaled);
        ui->crush_label->setAlignment(Qt::AlignCenter);
    }

    // ── Font ──────────────────────────────────────────────────────────────
    int fontId =
        QFontDatabase::addApplicationFont(":/font/fonts/aileron.black.otf");
    if (fontId == -1) {
        qDebug() << "Warning: Custom font failed to load from resources!";
    } else {
        QString family = QFontDatabase::applicationFontFamilies(fontId).at(0);
        qDebug() << "Success! Font family:" << family;
    }

    // ── Camera graphics scene ─────────────────────────────────────────────
    m_scene      = new QGraphicsScene(this);
    m_pixmapItem = new QGraphicsPixmapItem();
    m_scene->addItem(m_pixmapItem);
    ui->graphicsView->setScene(m_scene);
    ui->graphicsView->setRenderHint(QPainter::SmoothPixmapTransform);

    // ── Mode toggle button (added programmatically to the camera page) ────
    // Placed in the top-right corner of the camera page layout so it doesn't
    // require modifying the .ui file.
    m_modeButton = new QPushButton(ui->cameraPage);
    m_modeButton->setFixedSize(160, 36);
    m_modeButton->move(ui->cameraPage->width() - 170, 4);
    m_modeButton->setStyleSheet(
        "background-color: rgb(44,181,222);"
        "color: white;"
        "border-width: 3px;"
        "border-style: ridge;"
        "border-color: rgb(152,199,65);"
        "border-radius: 6px;"
        "font-size: 13px;"
        "font-weight: bold;"
    );
    updateModeButton();
    connect(m_modeButton, &QPushButton::clicked, this, &MainWindow::onModeToggleClicked);

    // ── Camera receiver ───────────────────────────────────────────────────
    m_cameraReceiver = new CameraReceiver(this);

    connect(m_cameraReceiver, &CameraReceiver::frameReady,
            this, &MainWindow::onCameraFrame);
    connect(m_cameraReceiver, &CameraReceiver::connected,
            this, &MainWindow::onCameraConnected);
    connect(m_cameraReceiver, &CameraReceiver::disconnected,
            this, &MainWindow::onCameraDisconnected);
    connect(m_cameraReceiver, &CameraReceiver::fpsUpdated,
            this, &MainWindow::onFpsUpdated);

    // ── Clock timer ───────────────────────────────────────────────────────
    m_clockTimer = new QTimer(this);
    m_clockTimer->setInterval(1000);
    connect(m_clockTimer, &QTimer::timeout, this, &MainWindow::updateClock);
    m_clockTimer->start();
    updateClock(); // show immediately
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ─────────────────────────────────────────────────────────────────────────────
// Keyboard shortcut: Escape → main menu
// ─────────────────────────────────────────────────────────────────────────────

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        if (ui->stackedWidget->currentIndex() != 0) {
            if (ui->stackedWidget->currentIndex() == 1) {
                // Leaving camera page: stop the stream
                m_cameraReceiver->disconnectFromHost();
            }
            ui->stackedWidget->setCurrentIndex(0);
        }
    } else {
        QMainWindow::keyPressEvent(event);
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// Main menu navigation
// ─────────────────────────────────────────────────────────────────────────────

void MainWindow::on_cameraFeedPushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

    // Connect to the ROV Pi camera server over Ethernet.
    // PI_DEFAULT_HOST / CAM_STREAM_PORT / CAM_COMMAND_PORT are defined in
    // camerareceiver.h – change PI_DEFAULT_HOST to your Pi's static IP.
    m_cameraReceiver->connectToHost();

    // Default to front camera on entry
    ui->camName->setText("Camera:  Front");
    ui->latencyLabel->setText("Latency: connecting…");
    setActiveCamButton("front");
}

void MainWindow::on_modelingPushButton_clicked()  { ui->stackedWidget->setCurrentIndex(2); }
void MainWindow::on_icebergPushButton_clicked()   { ui->stackedWidget->setCurrentIndex(3); }
void MainWindow::on_ednaPushButton_clicked()      { ui->stackedWidget->setCurrentIndex(4); }
void MainWindow::on_floatPushButton_clicked()     { ui->stackedWidget->setCurrentIndex(5); }

// ─────────────────────────────────────────────────────────────────────────────
// Home (back) buttons
// ─────────────────────────────────────────────────────────────────────────────

void MainWindow::on_homePageButton_clicked()
{
    // Camera page → main menu: disconnect stream and reset mode
    m_cameraReceiver->disconnectFromHost();
    m_currentMode = "live";
    updateModeButton();
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_homePageButton_2_clicked() { ui->stackedWidget->setCurrentIndex(0); }
void MainWindow::on_homePageButton_3_clicked() { ui->stackedWidget->setCurrentIndex(0); }
void MainWindow::on_homePageButton_4_clicked() { ui->stackedWidget->setCurrentIndex(0); }
void MainWindow::on_homePageButton_5_clicked() { ui->stackedWidget->setCurrentIndex(0); }
void MainWindow::on_homePageButton_6_clicked() { ui->stackedWidget->setCurrentIndex(0); }

void MainWindow::on_closeProgramButton_clicked() { close(); }

// ─────────────────────────────────────────────────────────────────────────────
// Camera view buttons – each sends a switch command to the Pi
// ─────────────────────────────────────────────────────────────────────────────

void MainWindow::on_frontCamButton_clicked()
{
    m_cameraReceiver->switchCamera("front");
    ui->camName->setText("Camera:  Front");
    setActiveCamButton("front");
}

void MainWindow::on_leftCamButton_clicked()
{
    m_cameraReceiver->switchCamera("left");
    ui->camName->setText("Camera:  Left");
    setActiveCamButton("left");
}

void MainWindow::on_rightCamButton_clicked()
{
    m_cameraReceiver->switchCamera("right");
    ui->camName->setText("Camera:  Right");
    setActiveCamButton("right");
}

void MainWindow::on_botCamButton_clicked()
{
    m_cameraReceiver->switchCamera("bot");
    ui->camName->setText("Camera:  Bottom");
    setActiveCamButton("bot");
}

void MainWindow::on_backCamButton_clicked()
{
    m_cameraReceiver->switchCamera("back");
    ui->camName->setText("Camera:  Back");
    setActiveCamButton("back");
}

// ─────────────────────────────────────────────────────────────────────────────
// Camera receiver callbacks
// ─────────────────────────────────────────────────────────────────────────────

void MainWindow::onCameraFrame(const QImage &image)
{
    if (!m_pixmapItem)
        return;

    QPixmap pm = QPixmap::fromImage(image).scaled(
        ui->graphicsView->viewport()->size(),
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation
    );
    m_pixmapItem->setPixmap(pm);
    m_scene->setSceneRect(m_pixmapItem->boundingRect());
    ui->graphicsView->fitInView(m_pixmapItem, Qt::KeepAspectRatio);
}

void MainWindow::onCameraConnected()
{
    ui->latencyLabel->setText("Latency: connected");
}

void MainWindow::onCameraDisconnected()
{
    ui->latencyLabel->setText("Latency: disconnected");
    if (m_pixmapItem)
        m_pixmapItem->setPixmap(QPixmap()); // clear stale frame
}

void MainWindow::onFpsUpdated(int fps)
{
    ui->latencyLabel->setText(
        QStringLiteral("Stream: %1 fps").arg(fps));
}

// ─────────────────────────────────────────────────────────────────────────────
// Clock
// ─────────────────────────────────────────────────────────────────────────────

void MainWindow::updateClock()
{
    ui->timeLabel->setText(
        QDateTime::currentDateTime().toString("hh:mm:ss"));
}

// ─────────────────────────────────────────────────────────────────────────────
// eDNA percentage calculator
// ─────────────────────────────────────────────────────────────────────────────

void MainWindow::on_pushButtonCalcPercent_clicked()
{
    int snowInput    = ui->spinBoxSnow->value();
    int acadianInput = ui->spinBoxAcadian->value();
    int westernInput = ui->spinBoxWestern->value();
    int urchinInput  = ui->spinBoxUrchin->value();
    int rockInput    = ui->spinBoxRock->value();
    int jonahInput   = ui->spinBoxJonah->value();
    int sunstarInput = ui->spinBoxSunstar->value();
    int greenInput   = ui->spinBoxGreen->value();
    int borealInput  = ui->spinBoxBoreal->value();
    int brittleInput = ui->spinBoxBrittle->value();

    double sum = snowInput + acadianInput + westernInput + urchinInput +
                 rockInput + jonahInput + sunstarInput + greenInput +
                 borealInput + brittleInput;

    if (sum == 0) return;

    ui->snowCrabPercent->display((snowInput    / sum) * 100);
    ui->acadianCrabPercent->display((acadianInput / sum) * 100);
    ui->hairyCrabPercent->display((westernInput / sum) * 100);
    ui->urchinPercent->display((urchinInput  / sum) * 100);
    ui->rockCrabPercent->display((rockInput   / sum) * 100);
    ui->jonahCrabPercent->display((jonahInput  / sum) * 100);
    ui->sunstarPercent->display((sunstarInput / sum) * 100);
    ui->greenCrabPercent->display((greenInput  / sum) * 100);
    ui->borealPercent->display((borealInput  / sum) * 100);
    ui->brittlePercent->display((brittleInput / sum) * 100);
}

// ─────────────────────────────────────────────────────────────────────────────
// Private helpers
// ─────────────────────────────────────────────────────────────────────────────

// ─────────────────────────────────────────────────────────────────────────────
// Mode toggle
// ─────────────────────────────────────────────────────────────────────────────

void MainWindow::onModeToggleClicked()
{
    m_currentMode = (m_currentMode == "live") ? "hq" : "live";
    m_cameraReceiver->setMode(m_currentMode);
    updateModeButton();
}

void MainWindow::updateModeButton()
{
    if (!m_modeButton) return;

    if (m_currentMode == "live") {
        m_modeButton->setText("Live  2048x1536 @ 30fps");
        m_modeButton->setToolTip(
            "Currently: Live streaming mode\nClick to switch to HQ photogrammetry mode");
    } else {
        m_modeButton->setText("HQ  4656x3496 @ 10fps");
        m_modeButton->setToolTip(
            "Currently: High-quality photogrammetry mode\nClick to switch to Live streaming mode");
        // Tint the button gold when in HQ mode so it's obviously different
        m_modeButton->setStyleSheet(
            "background-color: rgb(210,160,20);"
            "color: white;"
            "border-width: 3px;"
            "border-style: ridge;"
            "border-color: rgb(255,220,80);"
            "border-radius: 6px;"
            "font-size: 13px;"
            "font-weight: bold;"
        );
        return;
    }
    // Reset to normal style for live mode
    m_modeButton->setStyleSheet(
        "background-color: rgb(44,181,222);"
        "color: white;"
        "border-width: 3px;"
        "border-style: ridge;"
        "border-color: rgb(152,199,65);"
        "border-radius: 6px;"
        "font-size: 13px;"
        "font-weight: bold;"
    );
}

/**
 * Highlights the active camera button with a bright border and dims the rest.
 * The style keeps the same base colours as the rest of the UI.
 */
void MainWindow::setActiveCamButton(const QString &name)
{
    static const QString activeStyle =
        "background-color: rgb(44,181,222);"
        "border-width: 4px;"
        "border-style: ridge;"
        "border-color: rgb(255, 255, 255);"   // white border = active
        "color: rgb(255,255,255);"
        "font-weight: bold;";

    static const QString inactiveStyle =
        "background-color: rgb(44,181,222);"
        "border-width: 4px;"
        "border-style: ridge;"
        "border-color: rgb(152, 199, 65);"    // green border = inactive
        "selection-color: rgb(255, 255, 255);";

    ui->frontCamButton->setStyleSheet(name == "front"  ? activeStyle : inactiveStyle);
    ui->leftCamButton->setStyleSheet( name == "left"   ? activeStyle : inactiveStyle);
    ui->rightCamButton->setStyleSheet(name == "right"  ? activeStyle : inactiveStyle);
    ui->botCamButton->setStyleSheet(  name == "bot"    ? activeStyle : inactiveStyle);
    ui->backCamButton->setStyleSheet( name == "back"   ? activeStyle : inactiveStyle);
}
