#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QCheckBox>
#include <QCoreApplication>
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QFontDatabase>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QInputDialog>
#include <QKeyEvent>
#include <QLCDNumber>
#include <QLabel>
#include <QListWidget>
#include <QMessageBox>
#include <QPixmap>
#include <QProcess>
#include <QProgressBar>
#include <QPushButton>
#include <QScrollBar>
#include <QSpinBox>
#include <QSplitter>
#include <QStandardPaths>
#include <QString>
#include <QSysInfo>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>
#include <cmath>

namespace {
bool isRealColmap(const QString &path) {
    QProcess probe;
    probe.setProcessChannelMode(QProcess::MergedChannels);
    probe.start(path, {"help"});
    if (!probe.waitForStarted(2000) || !probe.waitForFinished(3000))
        return false;
    return probe.readAll().contains("Structure-from-Motion");
}
}

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

    m_tacticalScene = new QGraphicsScene(this);
    ui->tacticalview->setScene(m_tacticalScene);

    // 1. Plot all 4 Platforms
    m_tacticalScene->addEllipse(50, 50, 15, 15, QPen(Qt::black), QBrush(Qt::darkGray));   // Plat 1
    m_tacticalScene->addEllipse(-100, 80, 15, 15, QPen(Qt::black), QBrush(Qt::darkGray)); // Plat 2
    m_tacticalScene->addEllipse(120, -60, 15, 15, QPen(Qt::black), QBrush(Qt::darkGray)); // Plat 3
    m_tacticalScene->addEllipse(-80, -90, 15, 15, QPen(Qt::black), QBrush(Qt::darkGray)); // Plat 4

    // 2. Initialize the dynamic tracking items
    m_icebergMarker = m_tacticalScene->addEllipse(0, 0, 30, 30, QPen(Qt::blue), QBrush(Qt::cyan));
    m_headingVector = m_tacticalScene->addLine(0, 0, 0, 0, QPen(Qt::red, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    m_icebergPerimeter = m_tacticalScene->addPolygon(QPolygonF(), QPen(Qt::cyan, 1, Qt::DashLine));
    // ------------------------------------------------------


    ui->stackedWidget->setCurrentIndex(0);

    // ── Photogrammetry ────────────────────────────────────────────────────
    setupPhotogrammetry();

    // ── Frame capture output folder ───────────────────────────────────────
    m_photogramPath = QCoreApplication::applicationDirPath() + "/photogram_images";
    QDir().mkpath(m_photogramPath);

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

    // ── HUD overlay labels (children of graphicsView, always on top) ─────
    auto makeHud = [](QWidget *parent, const QString &text, const QString &color) -> QLabel* {
        auto *lbl = new QLabel(text, parent);
        lbl->setStyleSheet(
            QString("QLabel { background-color: rgba(0,0,0,160);"
                    " color: %1;"
                    " font: bold 15px 'Aileron';"
                    " padding: 3px 8px;"
                    " border-radius: 4px; }").arg(color));
        lbl->setAttribute(Qt::WA_TransparentForMouseEvents);
        lbl->adjustSize();
        lbl->show();
        return lbl;
    };
    m_hudDepth    = makeHud(ui->graphicsView, "Depth: --",    "#00ccff");
    m_hudPressure = makeHud(ui->graphicsView, "Pressure: --", "#00ccff");
    m_hudLatency  = makeHud(ui->graphicsView, "Stream: --",   "#ffffff");
    m_hudAls      = makeHud(ui->graphicsView, "ALS: OFF",     "#ff4444");

    // Stack them in the top-left corner
    const int margin = 10;
    const int step   = 30;
    m_hudDepth   ->move(margin, margin);
    m_hudPressure->move(margin, margin + step);
    m_hudLatency ->move(margin, margin + step * 2);
    m_hudAls     ->move(margin, margin + step * 3);

    // ── Mode toggle button ────────────────────────────────────────────────
    updateModeButton();

    // ── Camera receiver ───────────────────────────────────────────────────
    m_cameraReceiver = new CameraReceiver(this);

    connect(m_cameraReceiver, &CameraReceiver::depthUpdated, this, &MainWindow::updateLiveDepthDisplay);

    connect(m_cameraReceiver, &CameraReceiver::icebergMoved, this, &MainWindow::updateIcebergPosition);

    connect(m_cameraReceiver, &CameraReceiver::frameReady,
            this, &MainWindow::onCameraFrame);
    connect(m_cameraReceiver, &CameraReceiver::connected,
            this, &MainWindow::onCameraConnected);
    connect(m_cameraReceiver, &CameraReceiver::disconnected,
            this, &MainWindow::onCameraDisconnected);
    connect(m_cameraReceiver, &CameraReceiver::fpsUpdated,
            this, &MainWindow::onFpsUpdated);
    connect(m_cameraReceiver, &CameraReceiver::alsUpdated,
            this, &MainWindow::onAlsDataReady);
    connect(m_cameraReceiver, &CameraReceiver::telemetryUpdated,
            this, &MainWindow::onTelemetryUpdated);

    // ── Clock timer ───────────────────────────────────────────────────────
    m_clockTimer = new QTimer(this);
    m_clockTimer->setInterval(1000);
    connect(m_clockTimer, &QTimer::timeout, this, &MainWindow::updateClock);
    m_clockTimer->start();
    updateClock(); // show immediately

    // ── Call Float Chart Functions ───────────────────────────────────────────────────────
    setupPressureChart();
    setupDepthChart();
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
// Float Page logic
// ─────────────────────────────────────────────────────────────────────────────

void MainWindow::setupPressureChart() {

    auto series = new QLineSeries();

    // Add static data points
    series->append(0, 5);
    series->append(5, 10);
    series->append(10, 5);

    // Create chart
    auto chart = new QChart();
    chart->addSeries(series);
    chart->createDefaultAxes();

    chart->setTitle("Pressure Chart");

    chart->setTheme(QChart::ChartThemeBlueCerulean);

    chart->axes(Qt::Horizontal).first()->setRange(0, 10);
    chart->axes(Qt::Vertical).first()->setRange(0, 10);
    chart->axes(Qt::Horizontal).back()->setTitleText("Time (seconds)");
    chart->axes(Qt::Vertical).back()->setTitleText("Pressure (kpa)");

    QPen pen(Qt::red);
    pen.setWidth(3);
    series->setPen(pen);
    series->setVisible(true);

    // Attach to the UI widget (Promoted QChartView)
    ui->pressureChart->setChart(chart);
}

void MainWindow::setupDepthChart() {

    auto series = new QLineSeries();

    // Add static data points
    series->append(1, 5);
    series->append(2, 10);
    series->append(3, 5);

    // Create chart
    auto chart = new QChart();
    chart->addSeries(series);
    chart->createDefaultAxes();

    chart->setTitle("Depth Chart");

    chart->setTheme(QChart::ChartThemeBlueCerulean);

    chart->axes(Qt::Horizontal).first()->setRange(0, 10);
    chart->axes(Qt::Vertical).first()->setRange(0, 10);
    chart->axes(Qt::Horizontal).back()->setTitleText("Time (seconds)");
    chart->axes(Qt::Vertical).back()->setTitleText("Depth (meters)");

    QPen pen(Qt::red);
    pen.setWidth(3);
    series->setPen(pen);
    series->setVisible(true);

    // Attach to the UI widget (Promoted QChartView)
    ui->depthChart->setChart(chart);
}

void MainWindow::setupFloatDataTable(){

}

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


    if (m_capturingFrames) {
        m_frameCounter++;
        if (m_frameCounter % 10 == 0) {
            QString filename = m_photogramPath
                + QString("/frame_%1.jpg").arg(m_captureCount, 4, 10, QChar('0'));
            bool ok = image.save(filename, "JPEG", 95);
            if (ok) {
                m_captureCount++;
                ui->captureCountLabel->setText(QString("%1 frames").arg(m_captureCount));
                if (m_captureCount == 1)
                    qDebug() << "Capture started, saving to:" << m_photogramPath;
            } else {
                qDebug() << "Failed to save frame to:" << filename;
            }
        }
    }
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
    const QString text = QStringLiteral("Stream: %1 fps").arg(fps);
    ui->latencyLabel->setText(text);
    if (m_hudLatency) {
        m_hudLatency->setText(text);
        m_hudLatency->adjustSize();
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// Frame capture toggle
// ─────────────────────────────────────────────────────────────────────────────

void MainWindow::on_captureFramesButton_clicked()
{
    m_capturingFrames = !m_capturingFrames;
    if (m_capturingFrames) {
        m_frameCounter = 0;
        m_captureCount = 0;
        ui->captureCountLabel->setText("0 frames");
        ui->captureFramesButton->setText("Stop Capture");
        ui->captureFramesButton->setStyleSheet(
            "background-color: rgb(210,80,80);"
            "color: white;"
            "border-width: 3px;"
            "border-style: ridge;"
            "border-color: rgb(255,60,60);");
    } else {
        ui->captureFramesButton->setText("Capture Frames");
        ui->captureFramesButton->setStyleSheet(
            "background-color: rgb(44,181,222);"
            "color: white;"
            "border-width: 3px;"
            "border-style: ridge;"
            "border-color: rgb(152,199,65);");
    }
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
// ALS telemetry
// ─────────────────────────────────────────────────────────────────────────────

void MainWindow::onAlsDataReady(bool als, double pitch, double yaw)
{
    if (als) {
        const QString text = QString("ALS: ON  P:%1  Y:%2")
                                 .arg(pitch, 0, 'f', 2)
                                 .arg(yaw,   0, 'f', 2);
        ui->alsStatusLabel->setText(text);
        ui->alsStatusLabel->setStyleSheet("color: #00ff88; font-weight: bold;");
        if (m_hudAls) {
            m_hudAls->setText(text);
            m_hudAls->setStyleSheet(
                "QLabel { background-color: rgba(0,0,0,160); color: #00ff88;"
                " font: bold 15px 'Aileron'; padding: 3px 8px; border-radius: 4px; }");
            m_hudAls->adjustSize();
        }
    } else {
        ui->alsStatusLabel->setText("ALS: OFF");
        ui->alsStatusLabel->setStyleSheet("color: #ff4444; font-weight: bold;");
        if (m_hudAls) {
            m_hudAls->setText("ALS: OFF");
            m_hudAls->setStyleSheet(
                "QLabel { background-color: rgba(0,0,0,160); color: #ff4444;"
                " font: bold 15px 'Aileron'; padding: 3px 8px; border-radius: 4px; }");
            m_hudAls->adjustSize();
        }
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// Depth / pressure telemetry
// ─────────────────────────────────────────────────────────────────────────────

void MainWindow::onTelemetryUpdated(double depth, double pressure)
{
    if (m_hudDepth) {
        m_hudDepth->setText(QString("Depth: %1 m").arg(depth, 0, 'f', 2));
        m_hudDepth->adjustSize();
    }
    if (m_hudPressure) {
        m_hudPressure->setText(QString("Pressure: %1 mbar").arg(pressure, 0, 'f', 1));
        m_hudPressure->adjustSize();
    }
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

void MainWindow::on_modeButton_clicked()
{
    m_currentMode = (m_currentMode == "live") ? "hq" : "live";
    m_cameraReceiver->setMode(m_currentMode);
    updateModeButton();
}

void MainWindow::updateModeButton()
{
    if (m_currentMode == "live") {
        ui->modeButton->setText("Live  2048x1536 @ 30fps");
        ui->modeButton->setToolTip(
            "Currently: Live streaming mode\nClick to switch to HQ photogrammetry mode");
        ui->modeButton->setStyleSheet(
            "background-color: rgb(44,181,222);"
            "color: white;"
            "border-width: 3px;"
            "border-style: ridge;"
            "border-color: rgb(152,199,65);"
            "border-radius: 6px;"
            "font-size: 13px;"
            "font-weight: bold;"
        );
    } else {
        ui->modeButton->setText("HQ  4656x3496 @ 10fps");
        ui->modeButton->setToolTip(
            "Currently: High-quality photogrammetry mode\nClick to switch to Live streaming mode");
        ui->modeButton->setStyleSheet(
            "background-color: rgb(210,160,20);"
            "color: white;"
            "border-width: 3px;"
            "border-style: ridge;"
            "border-color: rgb(255,220,80);"
            "border-radius: 6px;"
            "font-size: 13px;"
            "font-weight: bold;"
        );
    }
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
void MainWindow::updateIcebergTracking(double iceX, double iceY, double headingDeg, double maxKeelDepth, QVector<QPointF> perimeterPoints)
{
    // 1. Update the visual map position
    m_icebergMarker->setPos(iceX, -iceY);

    // Update Heading Arrow (Vector length of 80 pixels so it's easier to see)
    double rads = qDegreesToRadians(headingDeg);
    double endX = iceX + (80 * qCos(rads));
    double endY = -iceY - (80 * qSin(rads));
    m_headingVector->setLine(iceX, -iceY, endX, endY);

    // --- NEW: Draw the Perimeter Polygon ---
    QPolygonF poly;
    for (int i = 0; i < perimeterPoints.size(); ++i) {
        // We invert the Y coordinate here because Qt's Y-axis goes down
        poly << QPointF(perimeterPoints[i].x(), -perimeterPoints[i].y());
    }
    m_icebergPerimeter->setPolygon(poly);
    // ---------------------------------------

    // 2. Calculate Distance to Platforms for Threat Level
    QPointF platforms[4] = { QPointF(50, -50), QPointF(-100, -80), QPointF(120, 60), QPointF(-80, 90) };
    QProgressBar* threatBars[4] = { ui->ProgThreat1, ui->ProgThreat2, ui->ProgThreat3, ui->ProgThreat4 };

    double threatRadius = 150.0;

    for(int i = 0; i < 4; i++) {
        double dist = qSqrt(qPow(platforms[i].x() - iceX, 2) + qPow(platforms[i].y() - (-iceY), 2));

        int threatPercent = 0;
        if (dist < threatRadius) {
            threatPercent = 100 - static_cast<int>((dist / threatRadius) * 100);
        }
        threatBars[i]->setValue(threatPercent);
    }

    // 3. Subsea Asset Threat
    double subseaAssetDepth = 85.0;

    if (maxKeelDepth >= subseaAssetDepth) {
        ui->progThreatSubsea->setValue(100);
        ui->progThreatSubsea->setStyleSheet("QProgressBar::chunk { background-color: red; }");
    } else {
        ui->progThreatSubsea->setValue(0);
        ui->progThreatSubsea->setStyleSheet("QProgressBar::chunk { background-color: green; }");
    }
}

void MainWindow::on_btnRecordDepth_clicked()
{
    if (m_currentDepthIndex >= 5) {
        return;
    }

    double currentLiveDepth = m_cameraReceiver->getLiveDepth();

    if (currentLiveDepth > m_maxKeelDepth) {
        m_maxKeelDepth = currentLiveDepth;
    }

    switch (m_currentDepthIndex) {
    case 0: ui->lcdKeelDepth1->display(currentLiveDepth); break;
    case 1: ui->lcdKeelDepth2->display(currentLiveDepth); break;
    case 2: ui->lcdKeelDepth3->display(currentLiveDepth); break;
    case 3: ui->lcdKeelDepth4->display(currentLiveDepth); break;
    case 4:
        ui->lcdKeelDepth5->display(currentLiveDepth);
        // Once the 5th point is recorded, you have the final max depth.
        // updateIcebergTracking(..., m_maxKeelDepth, ...);
        break;
    }

    m_currentDepthIndex++;
}

// ─────────────────────────────────────────────────────────────────────────────
// Photogrammetry setup
// ─────────────────────────────────────────────────────────────────────────────

void MainWindow::setupPhotogrammetry()
{
    QString base = QCoreApplication::applicationDirPath();
    m_workspacePath = base + "/workspace";
    m_imagePath = m_workspacePath + "/images";
    QDir().mkpath(m_imagePath);

    m_runner = new ColmapRunner(this);
    m_runner->setColmapPath(detectColmapPath());
    m_runner->setWorkspacePath(m_workspacePath);
    m_runner->setImagePath(m_imagePath);

    connect(m_runner, &ColmapRunner::stepStarted,      this, &MainWindow::onStepStarted);
    connect(m_runner, &ColmapRunner::progressOutput,   this, &MainWindow::onProgressOutput);
    connect(m_runner, &ColmapRunner::stepFinished,     this, &MainWindow::onStepFinished);
    connect(m_runner, &ColmapRunner::pipelineFinished, this, &MainWindow::onPipelineFinished);
    connect(m_runner, &ColmapRunner::errorOccurred,    this, &MainWindow::onError);

    connect(ui->viewer, &ModelViewer::scalePointsPicked,
            this, &MainWindow::onScalePointsPicked);

    connect(ui->viewer, &ModelViewer::scaleApplied,
            [this](float w, float h, float d) {
                ui->statusLabel->setText(
                    QString("Scale set — W:%1 m  H:%2 m  D:%3 m")
                    .arg(w,0,'f',3).arg(h,0,'f',3).arg(d,0,'f',3));
                ui->scaleButton->setChecked(false);
            });

    connect(ui->viewer, &ModelViewer::measurementReady,
            [this](float total, float dx, float dy, float dz) {
                ui->statusLabel->setText(
                    QString("A→B: %1 m    ΔX:%2  ΔY:%3  ΔZ:%4")
                    .arg(total,0,'f',3).arg(dx,0,'f',3).arg(dy,0,'f',3).arg(dz,0,'f',3));
                ui->measureButton->setChecked(false);
            });

    ui->scaleButton->setToolTip("Click two points of known distance to set real-world scale");
    ui->measureButton->setToolTip("Click two points to measure the distance between them");
#if defined(Q_OS_WIN)
    ui->denseCheckBox->setToolTip("Enables CUDA for COLMAP dense stereo on Windows.\nFeature extraction/matching and patch_match_stereo use the GPU when CUDA is available.\nSparse mapper and stereo_fusion remain CPU-bound.");
#else
    ui->denseCheckBox->setToolTip("Runs CPU-based dense reconstruction via OpenMVS DensifyPointCloud.\nSlower than CUDA but works on any hardware.");
#endif

    // mainSplitter fills all remaining vertical space in the page layout
    ui->modelingPageLayout->setStretchFactor(ui->mainSplitter, 1);

    // Internal splitter ratios
    ui->mainSplitter->setStretchFactor(0, 0);
    ui->mainSplitter->setStretchFactor(1, 1);
    ui->rightSplitter->setStretchFactor(0, 3);
    ui->rightSplitter->setStretchFactor(1, 1);

    refreshThumbnails();
}

// ─────────────────────────────────────────────────────────────────────────────
// Photogrammetry — COLMAP path detection
// ─────────────────────────────────────────────────────────────────────────────

QString MainWindow::detectColmapPath()
{
    QString base = QCoreApplication::applicationDirPath();

#ifdef Q_OS_WIN
    QString winPath = base + "/tools/win64/colmap.exe";
    if (QFileInfo::exists(winPath))
        return winPath;

    for (const QString &dir : {
             QString("C:/Program Files/COLMAP"),
             QString("C:/Program Files (x86)/COLMAP"),
             base
         }) {
        QString p = dir + "/colmap.exe";
        if (QFileInfo::exists(p))
            return p;
    }
#elif defined(Q_OS_MACOS)
    QString macPath = base + "/tools/macos/bin/colmap";
    if (QFileInfo::exists(macPath) &&
        QSysInfo::currentCpuArchitecture() == "arm64")
        return macPath;
#else
    QString linuxPath = base + "/tools/linux/bin/colmap";
    if (QFileInfo::exists(linuxPath))
        return linuxPath;
#endif

    QString onPath = QStandardPaths::findExecutable("colmap");
    if (!onPath.isEmpty() && isRealColmap(onPath))
        return onPath;

    QString chosen = QFileDialog::getOpenFileName(
        this,
        "Locate COLMAP executable",
        QString(),
#ifdef Q_OS_WIN
        "COLMAP (colmap.exe)"
#else
        "COLMAP (colmap)"
#endif
    );
    return chosen.isEmpty() ? "colmap" : chosen;
}

// ─────────────────────────────────────────────────────────────────────────────
// Photogrammetry — image management
// ─────────────────────────────────────────────────────────────────────────────

void MainWindow::on_importImagesButton_clicked()
{
    QStringList files = QFileDialog::getOpenFileNames(
        this, "Import Images", QString(),
        "Images (*.jpg *.jpeg *.png *.tiff *.tif *.bmp)");

    if (files.isEmpty())
        return;

    QDir imgDir(m_imagePath);
    int imported = 0;

    for (const QString &src : files) {
        QFileInfo fi(src);
        QString dest = imgDir.filePath(fi.fileName());

        if (QFile::exists(dest)) {
            QString base = fi.baseName();
            QString ext = fi.suffix();
            int i = 1;
            while (QFile::exists(dest))
                dest = imgDir.filePath(QString("%1_%2.%3").arg(base).arg(i++).arg(ext));
        }

        if (QFile::copy(src, dest))
            imported++;
    }

    ui->statusLabel->setText(QString("Imported %1 images").arg(imported));
    refreshThumbnails();
}

void MainWindow::on_importVideoButton_clicked()
{
    QString videoPath = QFileDialog::getOpenFileName(
        this, "Import Video", QString(),
        "Video (*.mp4 *.avi *.mov *.mkv *.webm)");

    if (videoPath.isEmpty())
        return;

    ui->statusLabel->setText("Extracting frames from video...");
    setRunning(true);

    QProcess *ffmpeg = new QProcess(this);
    QString outputPattern = m_imagePath + "/frame_%04d.jpg";
    QString filter = "select=not(mod(n\\,10))";

    ffmpeg->start("ffmpeg", {"-i", videoPath, "-vf", filter, "-vsync", "vfr",
                             "-q:v", "2", outputPattern});

    connect(ffmpeg, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            [this, ffmpeg](int exitCode, QProcess::ExitStatus) {
                ffmpeg->deleteLater();
                setRunning(false);

                if (exitCode == 0) {
                    refreshThumbnails();
                    int count = QDir(m_imagePath)
                                    .entryList({"*.jpg", "*.jpeg", "*.png", "*.tiff"},
                                               QDir::Files)
                                    .count();
                    ui->statusLabel->setText(
                        QString("Extracted frames — %1 images ready").arg(count));
                } else {
                    ui->statusLabel->setText(
                        "Frame extraction failed. Is ffmpeg installed?");
                    ui->logOutput->append("[ERROR] ffmpeg exited with code " +
                                         QString::number(exitCode));
                }
            });

    if (!ffmpeg->waitForStarted(3000)) {
        ffmpeg->deleteLater();
        setRunning(false);
        ui->statusLabel->setText(
            "Could not start ffmpeg. Make sure it's installed and on PATH.");
    }
}

void MainWindow::on_clearButton_clicked()
{
    QDir imgDir(m_imagePath);
    QStringList images = imgDir.entryList(
        {"*.jpg", "*.jpeg", "*.png", "*.tiff", "*.tif", "*.bmp"}, QDir::Files);

    if (images.isEmpty())
        return;

    auto answer = QMessageBox::question(
        this, "Clear Images",
        QString("Remove %1 images from workspace?").arg(images.count()));

    if (answer != QMessageBox::Yes)
        return;

    for (const QString &f : images)
        imgDir.remove(f);

    QDir(m_workspacePath + "/sparse").removeRecursively();
    QDir(m_workspacePath + "/dense").removeRecursively();
    QFile::remove(m_workspacePath + "/database.db");
    QFile::remove(m_workspacePath + "/model.ply");

    QDir wsDir(m_workspacePath);
    for (const QString &f : wsDir.entryList({"depth*.dmap", "scene*.mvs", "dense*.mvs", "*.ply"}, QDir::Files))
        wsDir.remove(f);

    ui->viewer->clear();
    refreshThumbnails();
    ui->statusLabel->setText("Workspace cleared");
    ui->logOutput->clear();
    ui->progressBar->setValue(0);
}

void MainWindow::refreshThumbnails()
{
    ui->imageList->clear();

    QDir imgDir(m_imagePath);
    QStringList images =
        imgDir.entryList({"*.jpg", "*.jpeg", "*.png", "*.tiff", "*.tif", "*.bmp"},
                         QDir::Files, QDir::Name);

    for (const QString &filename : images) {
        QPixmap pix(imgDir.filePath(filename));
        if (pix.isNull())
            continue;

        auto *item = new QListWidgetItem(
            QIcon(pix.scaled(120, 90, Qt::KeepAspectRatio, Qt::SmoothTransformation)),
            filename);
        ui->imageList->addItem(item);
    }

    bool hasImages = !images.isEmpty();
    ui->runButton->setEnabled(hasImages);

    if (hasImages)
        ui->statusLabel->setText(QString("%1 images ready").arg(images.count()));
}

// ─────────────────────────────────────────────────────────────────────────────
// Photogrammetry — pipeline control
// ─────────────────────────────────────────────────────────────────────────────

void MainWindow::on_runButton_clicked()
{
    QDir imgDir(m_imagePath);
    int count =
        imgDir.entryList({"*.jpg", "*.jpeg", "*.png", "*.tiff"}, QDir::Files)
            .count();
    if (count < 3) {
        ui->statusLabel->setText("Need at least 3 images to reconstruct");
        return;
    }

#if !defined(Q_OS_WIN)
    if (ui->denseCheckBox->isChecked()) {
        QStringList missing;
        if (QStandardPaths::findExecutable("InterfaceCOLMAP").isEmpty())
            missing << "InterfaceCOLMAP";
        if (QStandardPaths::findExecutable("DensifyPointCloud").isEmpty())
            missing << "DensifyPointCloud";
        if (!missing.isEmpty()) {
            QMessageBox box(this);
            box.setIcon(QMessageBox::Warning);
            box.setWindowTitle("OpenMVS tools missing");
            box.setText("Dense reconstruction needs OpenMVS binaries on PATH but "
                        "these were not found:\n\n  • " +
                        missing.join("\n  • ") +
                        "\n\nInstall OpenMVS, or run sparse reconstruction only?");
            auto *sparseBtn = box.addButton("Run sparse only", QMessageBox::AcceptRole);
            box.addButton(QMessageBox::Cancel);
            box.exec();
            if (box.clickedButton() != sparseBtn)
                return;
            ui->denseCheckBox->setChecked(false);
        }
    }
#endif

    ui->logOutput->clear();
    ui->progressBar->setValue(0);
    ui->viewer->clear();
    setRunning(true);

    m_runner->setWorkspacePath(m_workspacePath);
    m_runner->setImagePath(m_imagePath);
    m_runner->setDenseEnabled(ui->denseCheckBox->isChecked());
    m_runner->runFullPipeline();

    ui->progressBar->setRange(0, m_runner->totalSteps());
}

void MainWindow::on_cancelButton_clicked()
{
    m_runner->cancel();
    setRunning(false);
    ui->statusLabel->setText("Cancelled.");
}

void MainWindow::setRunning(bool running)
{
    ui->runButton->setEnabled(!running);
    ui->cancelButton->setEnabled(running);
    ui->importImagesButton->setEnabled(!running);
    ui->importVideoButton->setEnabled(!running);
    ui->clearButton->setEnabled(!running);
}

void MainWindow::onStepStarted(const QString &step)
{
    ui->statusLabel->setText("Running: " + step);
    ui->logOutput->append("\n=== " + step + " ===");
}

void MainWindow::onProgressOutput(const QString &line)
{
    ui->logOutput->append(line);
    ui->logOutput->verticalScrollBar()->setValue(
        ui->logOutput->verticalScrollBar()->maximum());
}

void MainWindow::onStepFinished(const QString &step, bool success)
{
    ui->progressBar->setValue(ui->progressBar->value() + 1);
    ui->logOutput->append(success
                              ? QString::fromUtf8("✓ ") + step + " complete."
                              : QString::fromUtf8("✗ ") + step + " failed.");
}

void MainWindow::onPipelineFinished(bool success)
{
    setRunning(false);

    if (success) {
        ui->statusLabel->setText("Converting to point cloud...");
        convertAndLoadModel();
    } else {
        ui->statusLabel->setText("Pipeline failed — check log for details");
    }
}

void MainWindow::onError(const QString &error)
{
    ui->logOutput->append("\n[ERROR] " + error);
}

void MainWindow::on_resetCameraButton_clicked() { ui->viewer->resetCamera(); }

void MainWindow::on_loadPlyButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(
        this, "Open PLY File", QString(), "PLY Files (*.ply)");
    if (path.isEmpty())
        return;
    ui->viewer->loadPLY(path);
    ui->statusLabel->setText("Loaded: " + QFileInfo(path).fileName());
}

void MainWindow::on_scaleButton_toggled(bool on)
{
    if (on) { ui->measureButton->setChecked(false); ui->viewer->enterScaleMode(); }
    else      ui->viewer->exitPickMode();
}

void MainWindow::on_measureButton_toggled(bool on)
{
    if (on) { ui->scaleButton->setChecked(false); ui->viewer->enterMeasureMode(); }
    else      ui->viewer->exitPickMode();
}

void MainWindow::onScalePointsPicked(float /*measuredModelDist*/)
{
    bool ok;
    double val = QInputDialog::getDouble(
        this, "Set Scale",
        "Real-world distance between the two selected points (metres):",
        0.1, 0.001, 10000.0, 4, &ok);
    if (ok && val > 0)
        ui->viewer->applyScale(static_cast<float>(val));
    ui->scaleButton->setChecked(false);
}

// ─────────────────────────────────────────────────────────────────────────────
// Photogrammetry — model conversion
// ─────────────────────────────────────────────────────────────────────────────

void MainWindow::convertAndLoadModel()
{
    if (ui->denseCheckBox->isChecked()) {
#if defined(Q_OS_WIN)
        QString densePly = m_workspacePath + "/dense/fused.ply";
#else
        QString densePly = m_workspacePath + "/dense.ply";
#endif
        if (QFile::exists(densePly)) {
            ui->logOutput->append("\n=== Loading Dense Model ===");
            ui->viewer->loadPLY(densePly);
            ui->statusLabel->setText(
                "Dense reconstruction complete — use mouse to orbit/pan/zoom");
            ui->logOutput->append(QString::fromUtf8("✓ ") +
                                  "Dense model loaded into viewer.");
            return;
        }
        ui->logOutput->append("[WARN] Dense output not found — falling back to sparse.");
    }

    QString sparsePath = m_workspacePath + "/sparse/0";
    if (!QDir(sparsePath).exists()) {
        sparsePath = m_workspacePath + "/sparse";
        if (!QDir(sparsePath).exists()) {
            ui->statusLabel->setText("No reconstruction found in sparse/");
            return;
        }
    }

    QString plyPath = m_workspacePath + "/model.ply";

    QProcess *converter = new QProcess(this);

    QString base = QCoreApplication::applicationDirPath();
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    env.insert("QT_QPA_PLATFORM", "offscreen");
    env.insert("OPENBLAS_NUM_THREADS", "1");

#if defined(Q_OS_MACOS)
    QString toolsBase = base + "/tools/macos";
    QString libVar = "DYLD_LIBRARY_PATH";
#elif defined(Q_OS_WIN)
    QString toolsBase = base + "/tools/win64";
    QString libVar = "";
#else
    QString toolsBase = base + "/tools/linux";
    QString libVar = "LD_LIBRARY_PATH";
#endif

#ifndef Q_OS_WIN
    QString libPath = toolsBase + "/lib";
    if (QDir(libPath).exists()) {
        QString existing = env.value(libVar);
        env.insert(libVar, libPath + (existing.isEmpty() ? "" : ":" + existing));
    }
#endif

    QString pluginPath = toolsBase + "/plugins";
    if (QDir(pluginPath).exists())
        env.insert("QT_PLUGIN_PATH", pluginPath);

    converter->setProcessEnvironment(env);

    connect(
        converter, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
        [this, converter, plyPath](int exitCode, QProcess::ExitStatus) {
            converter->deleteLater();

            if (exitCode == 0 && QFile::exists(plyPath)) {
                ui->logOutput->append("\n=== Loading 3D Model ===");
                ui->viewer->loadPLY(plyPath);
                ui->statusLabel->setText(
                    "Reconstruction complete — use mouse to orbit/pan/zoom");
                ui->logOutput->append(QString::fromUtf8("✓ ") +
                                      "Model loaded into viewer.");
            } else {
                ui->statusLabel->setText("Model conversion failed");
                ui->logOutput->append("[ERROR] model_converter failed with exit code " +
                                      QString::number(exitCode));
                ui->logOutput->append(
                    QString::fromUtf8(converter->readAllStandardError()));
            }
        });

    QString colmapPath = detectColmapPath();
    converter->start(colmapPath,
                     {"model_converter", "--input_path", sparsePath,
                      "--output_path", plyPath, "--output_type", "PLY"});

    if (!converter->waitForStarted(5000)) {
        converter->deleteLater();
        ui->statusLabel->setText("Failed to start model converter");
    }
}
// Instantly updates the live LCD whenever a UDP packet arrives
void MainWindow::updateLiveDepthDisplay(double depth)
{
    ui->lcdLiveDepth->display(depth);
}

// Steps the tracker backward one slot and clears the screen
void MainWindow::on_btnUndoDepth_clicked()
{
    if (m_currentDepthIndex > 0) {
        // Move the hidden tracker back by 1
        m_currentDepthIndex--;

        // Clear the specific LCD screen so the pilot knows it is empty
        switch (m_currentDepthIndex) {
        case 0: ui->lcdKeelDepth1->display(0); break;
        case 1: ui->lcdKeelDepth2->display(0); break;
        case 2: ui->lcdKeelDepth3->display(0); break;
        case 3: ui->lcdKeelDepth4->display(0); break;
        case 4: ui->lcdKeelDepth5->display(0); break;
        }
    }
}
// Instantly moves the blue dot and calculates real-time threat levels
void MainWindow::updateIcebergPosition(double x, double y)
{
    // 1. Move the physical blue dot on the map
    if (m_icebergMarker != nullptr) {
        m_icebergMarker->setPos(x, y);
    }

    // 2. Define the exact coordinates of your stationary platforms
    // (These match the addEllipse numbers from your constructor)
    double p1_x = 50,   p1_y = 50;
    double p2_x = -100, p2_y = 80;
    double p3_x = 120,  p3_y = -60;
    double p4_x = -80,  p4_y = -90;
    double asset_x = 0, asset_y = 0; // Assuming Subsea Asset is dead center

    // 3. Calculate the true distance from the iceberg to each platform
    double dist1 = std::hypot(x - p1_x, y - p1_y);
    double dist2 = std::hypot(x - p2_x, y - p2_y);
    double dist3 = std::hypot(x - p3_x, y - p3_y);
    double dist4 = std::hypot(x - p4_x, y - p4_y);
    double distAsset = std::hypot(x - asset_x, y - asset_y);

    // 4. The Threat Algorithm (Closer distance + Deeper keel = Higher Danger)
    auto calculateThreat = [this](double distance) -> int {
        // Start with a base danger level based on distance
        double baseThreat = 100.0 - (distance * 0.4);

        // Add a penalty if the iceberg's keel is reaching dangerously deep
        double depthPenalty = m_currentDepth * 0.5;

        int totalThreat = static_cast<int>(baseThreat + depthPenalty);

        // Lock the percentage cleanly between 0% and 100%
        if (totalThreat > 100) return 100;
        if (totalThreat < 0) return 0;
        return totalThreat;
    };

    ui->ProgThreat1->setValue(calculateThreat(dist1));
    ui->ProgThreat2->setValue(calculateThreat(dist2));
    ui->ProgThreat3->setValue(calculateThreat(dist3));
    ui->ProgThreat4->setValue(calculateThreat(dist4));
    ui->progThreatSubsea->setValue(calculateThreat(distAsset));
}
