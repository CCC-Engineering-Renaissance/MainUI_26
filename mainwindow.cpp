#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "src/rovsetuppage.h"

#include <QCheckBox>
#include <QCloseEvent>
#include <QCoreApplication>
#include <QDateTime>
#include <QDebug>
#include <QDoubleSpinBox>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QFontDatabase>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGroupBox>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QAbstractItemView>
#include <QInputDialog>
#include <QKeyEvent>
#include <QLCDNumber>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMessageBox>
#include <QNetworkDatagram>
#include <QPainter>
#include <QPixmap>
#include <QPlainTextEdit>
#include <QProcess>
#include <QPushButton>
#include <QRegularExpression>
#include <QtConcurrent>
#include <QScrollBar>
#include <QSpinBox>
#include <QSplitter>
#include <QStandardPaths>
#include <QString>
#include <QSysInfo>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTextEdit>
#include <QTextStream>
#include <QUdpSocket>
#include <QVBoxLayout>
#include <QWidget>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtMath>
#include <algorithm>
#include <cmath>

#include <QMediaDevices>
#include <QCameraDevice>
#include <QtCore/QPermissions>

namespace {
bool isRealColmap(const QString &path)
{
    QProcess probe;
    probe.setProcessChannelMode(QProcess::MergedChannels);
    probe.start(path, {"help"});
    if (!probe.waitForStarted(2000) || !probe.waitForFinished(3000))
        return false;
    return probe.readAll().contains("Structure-from-Motion");
}

struct PlatformInfo {
    const char *name;
    double latitude;
    double longitude;
    double depthMeters;
};

const PlatformInfo kPlatforms[] = {
    {"Hibernia", 43.7504, -48.7819, 78.0},
    {"Sea Rose", 46.7895, -48.1417, 107.0},
    {"Terra Nova", 46.4, -48.4, 91.0},
    {"Hebron", 46.544, -48.498, 93.0},
};

constexpr double kDepthHoldMinMeters = 2.27;
constexpr double kDepthHoldMaxMeters = 2.83;
constexpr double kShallowHoldMinMeters = 0.07;
constexpr double kShallowHoldMaxMeters = 0.73;

bool isFloatMeasurementUnit(const QString &token)
{
    const QString unit = token.toLower();
    return unit == "kpa" || unit == "pa" || unit == "meters" || unit == "meter" ||
           unit == "metres" || unit == "metre" || unit == "m" || unit == "cm";
}

} // namespace

// ─────────────────────────────────────────────────────────────────────────────
// Construction / destruction
// ─────────────────────────────────────────────────────────────────────────────

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //+
    // ── YOLOv8 crab detector model ────────────────────────────────────────────────────
    const QString modelFile = QCoreApplication::applicationDirPath() + "/models/crabs_yolov8n.onnx";

    if (!m_crabDetector.loadModel(modelFile))
    {
        qWarning() << "CrabDetector: no ONNX model found – detection disabled.";
    }
    else
    {
        m_crabDetector.setConfidenceThreshold(0.60f);
        // ^ adjust to 50 to identify more crabs (less accuracy), 70 for more accuracy (less identifiable crabs)
        m_crabDetector.setNmsThreshold(0.45f);
        qDebug() << "CrabDetector: ready";
    }
    //+

    resize(1200, 800);
    setMinimumSize(900, 600);

    setupIcebergPage();

    m_tacticalScene = new QGraphicsScene(this);
    if (m_tacticalView)
        m_tacticalView->setScene(m_tacticalScene);

    // 1. Plot all 4 Platforms
    m_tacticalScene->addEllipse(50, 50, 15, 15, QPen(Qt::black), QBrush(Qt::darkGray));   // Plat 1
    m_tacticalScene->addEllipse(-100, 80, 15, 15, QPen(Qt::black), QBrush(Qt::darkGray)); // Plat 2
    m_tacticalScene->addEllipse(120, -60, 15, 15, QPen(Qt::black), QBrush(Qt::darkGray)); // Plat 3
    m_tacticalScene->addEllipse(-80, -90, 15, 15, QPen(Qt::black), QBrush(Qt::darkGray)); // Plat 4

    // 2. Initialize the dynamic tracking items
    m_icebergMarker = m_tacticalScene->addEllipse(0, 0, 30, 30, QPen(Qt::blue), QBrush(Qt::cyan));
    m_headingVector = m_tacticalScene->addLine(
        0, 0, 0, 0, QPen(Qt::red, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    m_icebergPerimeter = m_tacticalScene->addPolygon(QPolygonF(), QPen(Qt::cyan, 1, Qt::DashLine));
    // ------------------------------------------------------
    updateIcebergAnalysis();

    ui->stackedWidget->setCurrentIndex(0);

    // ── ROV Setup submenu (settingsPage, index 6) ─────────────────────────
    {
        auto *settingsLayout = new QVBoxLayout(ui->settingsPage);
        // Top margin clears the absolutely-positioned back button.
        settingsLayout->setContentsMargins(12, 36, 12, 12);
        m_rovSetup = new RovSetupPage(ui->settingsPage);
        settingsLayout->addWidget(m_rovSetup);
        ui->homePageButton_6->raise();
    }

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
        QPixmap scaled = pixmap.scaled(250, 250, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->crush_label->setPixmap(scaled);
        ui->crush_label->setAlignment(Qt::AlignCenter);
    }

    // ── Font ──────────────────────────────────────────────────────────────
    int fontId = QFontDatabase::addApplicationFont(":/font/fonts/aileron.black.otf");
    if (fontId == -1) {
        qDebug() << "Warning: Custom font failed to load from resources!";
    } else {
        QString family = QFontDatabase::applicationFontFamilies(fontId).at(0);
        qDebug() << "Success! Font family:" << family;
    }

    // ── Camera graphics scene ─────────────────────────────────────────────
    m_scene = new QGraphicsScene(this);
    m_pixmapItem = new QGraphicsPixmapItem();
    m_scene->addItem(m_pixmapItem);
    ui->graphicsView->setScene(m_scene);
    ui->graphicsView->setRenderHint(QPainter::SmoothPixmapTransform);

    // ── HUD overlay labels (children of graphicsView, always on top) ─────
    auto makeHud = [](QWidget *parent, const QString &text, const QString &color) -> QLabel * {
        auto *lbl = new QLabel(text, parent);
        lbl->setStyleSheet(QString("QLabel { background-color: rgba(0,0,0,160);"
                                   " color: %1;"
                                   " font: bold 15px 'Aileron';"
                                   " padding: 3px 8px;"
                                   " border-radius: 4px; }")
                               .arg(color));
        lbl->setAttribute(Qt::WA_TransparentForMouseEvents);
        lbl->adjustSize();
        lbl->show();
        return lbl;
    };
    m_hudDepth = makeHud(ui->graphicsView, "Depth: --", "#00ccff");
    m_hudPressure = makeHud(ui->graphicsView, "Pressure: --", "#00ccff");
    m_hudLatency = makeHud(ui->graphicsView, "Stream: --", "#ffffff");
    m_hudAls = makeHud(ui->graphicsView, "ALS: OFF", "#ff4444");

    // Stack them in the top-left corner
    const int margin = 10;
    const int step = 30;
    m_hudDepth->move(margin, margin);
    m_hudPressure->move(margin, margin + step);
    m_hudLatency->move(margin, margin + step * 2);
    m_hudAls->move(margin, margin + step * 3);

    // ── Mode toggle button ────────────────────────────────────────────────
    updateModeButton();

    // ── Camera receiver ───────────────────────────────────────────────────
    m_cameraReceiver = new CameraReceiver(this);

    connect(m_cameraReceiver,
            &CameraReceiver::depthUpdated,
            this,
            &MainWindow::updateLiveDepthDisplay);

    connect(m_cameraReceiver,
            &CameraReceiver::icebergMoved,
            this,
            &MainWindow::updateIcebergPosition);

    connect(m_cameraReceiver, &CameraReceiver::frameReady, this, &MainWindow::onCameraFrame);

    // Async crab detection: when a worker-thread inference finishes, store its
    // results (overlaid on subsequent frames) and free the slot for the next.
    connect(&m_detWatcher, &QFutureWatcherBase::finished, this, [this]() {
        if (m_detectionEnabled)
            m_lastDetections = m_detWatcher.result();
        m_detRunning = false;
    });
    connect(m_cameraReceiver, &CameraReceiver::connected, this, &MainWindow::onCameraConnected);
    connect(m_cameraReceiver,
            &CameraReceiver::disconnected,
            this,
            &MainWindow::onCameraDisconnected);
    connect(m_cameraReceiver, &CameraReceiver::fpsUpdated, this, &MainWindow::onFpsUpdated);
    connect(m_cameraReceiver, &CameraReceiver::alsUpdated, this, &MainWindow::onAlsDataReady);
    connect(m_cameraReceiver,
            &CameraReceiver::telemetryUpdated,
            this,
            &MainWindow::onTelemetryUpdated);

    // ── Clock timer ───────────────────────────────────────────────────────
    m_clockTimer = new QTimer(this);
    m_clockTimer->setInterval(1000);
    connect(m_clockTimer, &QTimer::timeout, this, &MainWindow::updateClock);
    m_clockTimer->start();
    updateClock(); // show immediately

    // ── Float mission station ─────────────────────────────────────────────
    setupFloatMissionPage();

    // The local webcam test feed starts on demand via the Webcam Test button on
    // the camera page (see on_webcamTestButton_toggled / startWebcam).
}

MainWindow::~MainWindow()
{
    // A detection task may still be running on a worker thread and references
    // this object + m_crabDetector — wait for it before tearing them down.
    if (m_detRunning)
        m_detWatcher.waitForFinished();
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
                // Leaving camera page: stop the stream and release the webcam.
                m_cameraReceiver->disconnectFromHost();
                if (m_webcamActive) {
                    ui->webcamTestButton->setChecked(false); // triggers stopWebcam()
                }
            }
            ui->stackedWidget->setCurrentIndex(0);
        }
    }
    else if (event->key() == Qt::Key_0) {
        // Toggle detection on/off
        m_detectionEnabled = !m_detectionEnabled;
        qDebug() << "Detection:" << (m_detectionEnabled ? "ON" : "OFF");
    }
    else if (event->key() == Qt::Key_Minus) {
        // Remove one green crab from count
        if (m_greenCrabCount > 0)
        {
            m_greenCrabCount--;
            ui->lcdNumber_3->display(m_greenCrabCount);
        }
    }
    else if (event->key() == Qt::Key_Plus ||
               event->key() == Qt::Key_Equal) {
        // Count green crabs in current frame
        int greenCount = 0;
        for (const auto &det : m_lastDetections)
        {
            if (det.species == "European-Green-Crabs")
                greenCount++;
        }
        m_greenCrabCount += greenCount;
        ui->lcdNumber_3->display(m_greenCrabCount);
    }
    else {
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

    //uncomment later after webcam test
    m_cameraReceiver->connectToHost();

    // Default to front camera on entry
    ui->camName->setText("Camera:  Front");
    ui->latencyLabel->setText("Latency: connecting…");
    setActiveCamButton("front");
}

void MainWindow::on_modelingPushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}
void MainWindow::on_icebergPushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}
void MainWindow::on_ednaPushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}
void MainWindow::on_floatPushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::setupIcebergPage()
{
    m_tacticalView = ui->tacticalview;
    m_liveDepthLcd = ui->lcdLiveDepth;
    m_surveyNumberEdits[0] = ui->lineSurveyNumber1;
    m_surveyNumberEdits[1] = ui->lineSurveyNumber2;
    m_surveyNumberEdits[2] = ui->lineSurveyNumber3;
    m_surveyNumberEdits[3] = ui->lineSurveyNumber4;
    m_surveyNumberEdits[4] = ui->lineSurveyNumber5;
    m_manualKeelSpin = ui->spinFinalKeelDepth;
    m_icebergLatSpin = ui->spinIcebergLatitude;
    m_icebergLonSpin = ui->spinIcebergLongitude;
    m_icebergHeadingSpin = ui->spinIcebergHeading;
    m_platformThreatTable = ui->tablePlatformThreats;
    m_judgeSummary = ui->txtJudgeSummary;

    ui->gridLayout_6->setColumnStretch(0, 1);
    ui->gridLayout_6->setColumnStretch(1, 1);
    ui->gridLayout_6->setColumnStretch(2, 2);
    ui->gridLayout_6->setRowStretch(1, 1);

    if (m_platformThreatTable) {
        m_platformThreatTable->verticalHeader()->setVisible(false);
        m_platformThreatTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        m_platformThreatTable->horizontalHeader()->setStretchLastSection(false);
        m_platformThreatTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        m_platformThreatTable->setSelectionMode(QAbstractItemView::NoSelection);
    }

    if (m_tacticalView)
        m_tacticalView->setRenderHint(QPainter::Antialiasing);

    for (QLineEdit *edit : m_surveyNumberEdits) {
        if (edit)
            connect(edit, &QLineEdit::textChanged, this, &MainWindow::updateIcebergAnalysis);
    }
    connect(m_icebergLatSpin, qOverload<double>(&QDoubleSpinBox::valueChanged),
            this, &MainWindow::updateIcebergAnalysis);
    connect(m_icebergLonSpin, qOverload<double>(&QDoubleSpinBox::valueChanged),
            this, &MainWindow::updateIcebergAnalysis);
    connect(m_icebergHeadingSpin, qOverload<double>(&QDoubleSpinBox::valueChanged),
            this, &MainWindow::updateIcebergAnalysis);
    connect(m_manualKeelSpin, qOverload<double>(&QDoubleSpinBox::valueChanged),
            this, &MainWindow::updateIcebergAnalysis);

    updateIcebergAnalysis();
}

// ─────────────────────────────────────────────────────────────────────────────
// Float Page logic
// ─────────────────────────────────────────────────────────────────────────────

void MainWindow::setupFloatMissionPage()
{
    m_floatPortSpin = ui->floatPortSpin;
    m_floatRxStatus = ui->floatRxStatusLabel;
    m_floatBottomOffsetSpin = ui->spinFloatBottomOffset;
    m_floatTopOffsetSpin = ui->spinFloatTopOffset;
    m_floatPacketInput = ui->txtFloatPacketInput;
    m_floatPacketTable = ui->floatPacketTable;

    ui->floatMainSplitter->setStretchFactor(0, 3);
    ui->floatMainSplitter->setStretchFactor(1, 2);

    m_floatSocket = new QUdpSocket(this);
    connect(m_floatSocket, &QUdpSocket::readyRead, this, [this]() {
        while (m_floatSocket->hasPendingDatagrams()) {
            const QByteArray data = m_floatSocket->receiveDatagram().data();
            appendFloatPacketText(QString::fromUtf8(data));
        }
    });

    connect(ui->btnFloatStartReceiver, &QPushButton::clicked, this, [this]() {
        if (m_floatSocket->state() != QAbstractSocket::UnconnectedState)
            m_floatSocket->close();
        const quint16 port = static_cast<quint16>(m_floatPortSpin->value());
        const bool ok = m_floatSocket->bind(QHostAddress::AnyIPv4, port,
                                            QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
        m_floatRxStatus->setText(ok ? QString("Listening on %1").arg(port) : "Bind failed");
    });
    connect(ui->btnFloatStopReceiver, &QPushButton::clicked, this, [this]() {
        m_floatSocket->close();
        m_floatRxStatus->setText("Receiver idle");
    });
    connect(ui->btnFloatAddPackets, &QPushButton::clicked, this, [this]() {
        appendFloatPacketText(m_floatPacketInput->toPlainText());
        m_floatPacketInput->clear();
    });
    connect(ui->btnFloatImportPackets, &QPushButton::clicked, this, [this]() {
        const QString path = QFileDialog::getOpenFileName(this, "Import float packets", QString(),
                                                          "Packet logs (*.txt *.csv *.log);;All files (*)");
        if (path.isEmpty())
            return;
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Float packets", "Could not open selected file.");
            return;
        }
        appendFloatPacketText(QString::fromUtf8(file.readAll()));
    });
    connect(ui->btnFloatLoadSample, &QPushButton::clicked, this, [this]() {
        m_floatPackets.clear();
        QStringList rows;
        rows << "EX01 0 float 0.0 kpa 0.00 meters";
        const QVector<double> depths = {
            0.15, 0.80, 1.60, 2.35, 2.48, 2.51, 2.53, 2.50, 2.49, 2.52, 2.51, 1.70, 0.62, 0.42,
            0.41, 0.40, 0.39, 0.42, 0.41, 0.40, 0.38, 0.90, 1.80, 2.43, 2.50, 2.52, 2.51, 2.49,
            2.48, 2.51, 2.50, 1.60, 0.58, 0.43, 0.40, 0.41, 0.39, 0.40, 0.42, 0.41};
        for (int i = 0; i < depths.size(); ++i) {
            const int t = (i + 1) * 5;
            const double pressure = depths[i] * 10.05;
            rows << QString("EX01 %1 float %2 kpa %3 meters")
                        .arg(t)
                        .arg(pressure, 0, 'f', 2)
                        .arg(depths[i], 0, 'f', 2);
        }
        appendFloatPacketText(rows.join('\n'));
    });
    connect(ui->btnFloatClear, &QPushButton::clicked, this, [this]() {
        m_floatPackets.clear();
        rebuildFloatTableAndCharts();
    });
    connect(m_floatBottomOffsetSpin, qOverload<double>(&QDoubleSpinBox::valueChanged),
            this, [this]() { rebuildFloatTableAndCharts(); });
    connect(m_floatTopOffsetSpin, qOverload<double>(&QDoubleSpinBox::valueChanged),
            this, [this]() { rebuildFloatTableAndCharts(); });

    setupDepthChart();
    setupPressureChart();
    setupFloatDataTable();
}

void MainWindow::setupPressureChart()
{
    m_floatPressureSeries = new QLineSeries();
    m_floatPressureSeries->setName("Pressure");
    QPen pen(QColor("#f05a5a"));
    pen.setWidth(4);
    m_floatPressureSeries->setPen(pen);

    auto chart = new QChart();
    chart->addSeries(m_floatPressureSeries);
    chart->setTitle("Float Pressure Over Time");
    chart->setTitleFont(QFont("Aileron", 14, QFont::Bold));
    chart->setTheme(QChart::ChartThemeBlueCerulean);
    chart->legend()->setVisible(false);
    auto *axisX = new QValueAxis(chart);
    axisX->setTitleText("Time (seconds)");
    axisX->setTitleFont(QFont("Aileron", 11, QFont::Bold));
    axisX->setLabelsFont(QFont("Aileron", 10));
    axisX->setRange(0, 10);
    auto *axisY = new QValueAxis(chart);
    axisY->setTitleText("Pressure (kPa)");
    axisY->setTitleFont(QFont("Aileron", 11, QFont::Bold));
    axisY->setLabelsFont(QFont("Aileron", 10));
    axisY->setRange(0, 30);
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    m_floatPressureSeries->attachAxis(axisX);
    m_floatPressureSeries->attachAxis(axisY);
    ui->pressureChart->setChart(chart);
    ui->pressureChart->setRenderHint(QPainter::Antialiasing);
}

void MainWindow::setupDepthChart()
{
    m_floatDepthSeries = new QLineSeries();
    m_floatDepthSeries->setName("Depth");
    QPen pen(QColor("#00ccff"));
    pen.setWidth(4);
    m_floatDepthSeries->setPen(pen);

    auto chart = new QChart();
    chart->addSeries(m_floatDepthSeries);
    chart->setTitle("Float Depth Over Time");
    chart->setTitleFont(QFont("Aileron", 15, QFont::Bold));
    chart->setTheme(QChart::ChartThemeBlueCerulean);
    chart->legend()->setVisible(false);
    auto *axisX = new QValueAxis(chart);
    axisX->setTitleText("Time (seconds)");
    axisX->setTitleFont(QFont("Aileron", 11, QFont::Bold));
    axisX->setLabelsFont(QFont("Aileron", 10));
    axisX->setRange(0, 10);
    auto *axisY = new QValueAxis(chart);
    axisY->setTitleText("Depth (meters)");
    axisY->setTitleFont(QFont("Aileron", 11, QFont::Bold));
    axisY->setLabelsFont(QFont("Aileron", 10));
    axisY->setRange(0, 3.2);
    axisY->setReverse(true);
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    m_floatDepthSeries->attachAxis(axisX);
    m_floatDepthSeries->attachAxis(axisY);
    ui->depthChart->setChart(chart);
    ui->depthChart->setRenderHint(QPainter::Antialiasing);
}

void MainWindow::setupFloatDataTable()
{
    m_floatPacketTable->setColumnCount(7);
    m_floatPacketTable->setHorizontalHeaderLabels({"#", "Company", "Time (s)", "Depth (m)", "Pressure (kPa)", "Phase", "Raw packet"});
    m_floatPacketTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    m_floatPacketTable->horizontalHeader()->setStretchLastSection(true);
    m_floatPacketTable->verticalHeader()->setVisible(false);
    m_floatPacketTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_floatPacketTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    rebuildFloatTableAndCharts();
}

void MainWindow::appendFloatPacketText(const QString &text)
{
    const QStringList lines = text.split(QRegularExpression("[\r\n]+"), Qt::SkipEmptyParts);
    for (const QString &line : lines) {
        FloatPacket packet;
        if (parseFloatPacket(line.trimmed(), &packet)) {
            packet.afterDescent = packet.depthMeters > 0.05;
            auto existing = std::find_if(m_floatPackets.begin(), m_floatPackets.end(), [&packet](const FloatPacket &p) {
                return p.company == packet.company && qAbs(p.timeSeconds - packet.timeSeconds) < 0.001;
            });
            if (existing != m_floatPackets.end())
                *existing = packet;
            else
                m_floatPackets.push_back(packet);
        }
    }
    std::sort(m_floatPackets.begin(), m_floatPackets.end(), [](const FloatPacket &a, const FloatPacket &b) {
        return a.timeSeconds < b.timeSeconds;
    });
    rebuildFloatTableAndCharts();
}

bool MainWindow::parseFloatPacket(const QString &line, FloatPacket *packet) const
{
    if (line.isEmpty() || !packet)
        return false;

    FloatPacket parsed;
    parsed.raw = line;
    const QStringList tokens = line.split(QRegularExpression("[,\\s]+"), Qt::SkipEmptyParts);
    if (!tokens.isEmpty())
        parsed.company = tokens.first();

    bool gotTime = false;
    for (int i = 0; i < tokens.size(); ++i) {
        const QString &token = tokens[i];
        if (i + 1 < tokens.size() && isFloatMeasurementUnit(tokens[i + 1]))
            continue;
        const double seconds = parseFloatTimeSeconds(token);
        if (seconds >= 0.0) {
            parsed.timeSeconds = seconds;
            gotTime = true;
            break;
        }
    }

    QRegularExpression depthRe("(-?\\d+(?:\\.\\d+)?)\\s*(meters?|metres?|m|cm)\\b",
                               QRegularExpression::CaseInsensitiveOption);
    auto depthMatch = depthRe.match(line);
    bool gotDepth = depthMatch.hasMatch();
    if (gotDepth) {
        parsed.depthMeters = depthMatch.captured(1).toDouble();
        const QString unit = depthMatch.captured(2).toLower();
        if (unit == "cm")
            parsed.depthMeters /= 100.0;
    }

    QRegularExpression pressureRe("(-?\\d+(?:\\.\\d+)?)\\s*(kpa|pa)\\b",
                                  QRegularExpression::CaseInsensitiveOption);
    auto pressureMatch = pressureRe.match(line);
    if (pressureMatch.hasMatch()) {
        parsed.pressureKpa = pressureMatch.captured(1).toDouble();
        if (pressureMatch.captured(2).compare("pa", Qt::CaseInsensitive) == 0)
            parsed.pressureKpa /= 1000.0;
        parsed.hasPressure = true;
    }

    if (!gotDepth || !gotTime) {
        QVector<double> numbers;
        QRegularExpression numberRe("(?<![A-Za-z0-9_.])-?\\d+(?:\\.\\d+)?(?![A-Za-z0-9_.])");
        auto it = numberRe.globalMatch(line);
        while (it.hasNext())
            numbers.push_back(it.next().captured(0).toDouble());
        if (!gotTime && !numbers.isEmpty()) {
            parsed.timeSeconds = numbers.first();
            gotTime = true;
        }
        if (!gotDepth && numbers.size() >= 2) {
            parsed.depthMeters = numbers.last();
            gotDepth = true;
        }
    }

    if (!gotTime || !gotDepth)
        return false;

    *packet = parsed;
    return true;
}

double MainWindow::parseFloatTimeSeconds(const QString &token)
{
    if (token.contains(':')) {
        const QStringList parts = token.split(':');
        bool ok = false;
        double seconds = 0.0;
        if (parts.size() == 3) {
            seconds = parts[0].toDouble(&ok) * 3600.0;
            bool ok2 = false, ok3 = false;
            seconds += parts[1].toDouble(&ok2) * 60.0;
            seconds += parts[2].toDouble(&ok3);
            return ok && ok2 && ok3 ? seconds : -1.0;
        }
        if (parts.size() == 2) {
            seconds = parts[0].toDouble(&ok) * 60.0;
            bool ok2 = false;
            seconds += parts[1].toDouble(&ok2);
            return ok && ok2 ? seconds : -1.0;
        }
        return -1.0;
    }

    bool ok = false;
    const double value = token.toDouble(&ok);
    return ok ? value : -1.0;
}

void MainWindow::rebuildFloatTableAndCharts()
{
    if (m_floatPacketTable) {
        const double deepMin = kDepthHoldMinMeters - (m_floatBottomOffsetSpin ? m_floatBottomOffsetSpin->value() : 0.0) / 100.0;
        const double deepMax = kDepthHoldMaxMeters - (m_floatBottomOffsetSpin ? m_floatBottomOffsetSpin->value() : 0.0) / 100.0;
        const double shallowMin = kShallowHoldMinMeters + (m_floatTopOffsetSpin ? m_floatTopOffsetSpin->value() : 0.0) / 100.0;
        const double shallowMax = kShallowHoldMaxMeters + (m_floatTopOffsetSpin ? m_floatTopOffsetSpin->value() : 0.0) / 100.0;
        m_floatPacketTable->setRowCount(m_floatPackets.size());
        for (int row = 0; row < m_floatPackets.size(); ++row) {
            const FloatPacket &p = m_floatPackets[row];
            const QString phase = !p.afterDescent ? "pre-descent" :
                                      (p.depthMeters >= deepMin && p.depthMeters <= deepMax) ? "2.5 m hold" :
                                      (p.depthMeters >= shallowMin && p.depthMeters <= shallowMax) ? "40 cm hold" :
                                      "profile";
            const QStringList values = {
                QString::number(row + 1),
                p.company,
                QString::number(p.timeSeconds, 'f', 1),
                QString::number(p.depthMeters, 'f', 2),
                p.hasPressure ? QString::number(p.pressureKpa, 'f', 2) : QString(),
                phase,
                p.raw
            };
            for (int col = 0; col < values.size(); ++col)
                m_floatPacketTable->setItem(row, col, new QTableWidgetItem(values[col]));
        }
    }

    if (m_floatDepthSeries)
        m_floatDepthSeries->clear();
    if (m_floatPressureSeries)
        m_floatPressureSeries->clear();

    double maxTime = 10.0;
    double maxDepth = 3.2;
    double maxPressure = 30.0;
    for (const FloatPacket &p : m_floatPackets) {
        if (m_floatDepthSeries)
            m_floatDepthSeries->append(p.timeSeconds, p.depthMeters);
        if (p.hasPressure && m_floatPressureSeries)
            m_floatPressureSeries->append(p.timeSeconds, p.pressureKpa);
        maxTime = qMax(maxTime, p.timeSeconds);
        maxDepth = qMax(maxDepth, p.depthMeters + 0.25);
        if (p.hasPressure)
            maxPressure = qMax(maxPressure, p.pressureKpa + 5.0);
    }

    if (ui->depthChart->chart() && !ui->depthChart->chart()->axes(Qt::Horizontal).isEmpty())
        static_cast<QValueAxis *>(ui->depthChart->chart()->axes(Qt::Horizontal).first())->setRange(0, maxTime);
    if (ui->depthChart->chart() && !ui->depthChart->chart()->axes(Qt::Vertical).isEmpty())
        static_cast<QValueAxis *>(ui->depthChart->chart()->axes(Qt::Vertical).first())->setRange(0, maxDepth);
    if (ui->pressureChart->chart() && !ui->pressureChart->chart()->axes(Qt::Horizontal).isEmpty())
        static_cast<QValueAxis *>(ui->pressureChart->chart()->axes(Qt::Horizontal).first())->setRange(0, maxTime);
    if (ui->pressureChart->chart() && !ui->pressureChart->chart()->axes(Qt::Vertical).isEmpty())
        static_cast<QValueAxis *>(ui->pressureChart->chart()->axes(Qt::Vertical).first())->setRange(0, maxPressure);

}

int MainWindow::bestFloatProfileScore(int profileNumber, QStringList *evidence) const
{
    if (evidence)
        evidence->clear();
    if (m_floatPackets.size() < 2) {
        if (evidence)
            *evidence << "  No profile data parsed yet.";
        return 0;
    }

    const double deepMin = kDepthHoldMinMeters - m_floatBottomOffsetSpin->value() / 100.0;
    const double deepMax = kDepthHoldMaxMeters - m_floatBottomOffsetSpin->value() / 100.0;
    const double shallowMin = kShallowHoldMinMeters + m_floatTopOffsetSpin->value() / 100.0;
    const double shallowMax = kShallowHoldMaxMeters + m_floatTopOffsetSpin->value() / 100.0;

    int start = 0;
    int foundProfiles = 0;
    while (start < m_floatPackets.size()) {
        int deepIndex = -1;
        for (int i = start; i < m_floatPackets.size(); ++i) {
            if (m_floatPackets[i].depthMeters >= deepMin) {
                deepIndex = i;
                break;
            }
        }
        if (deepIndex < 0)
            break;

        int shallowIndex = -1;
        for (int i = deepIndex + 1; i < m_floatPackets.size(); ++i) {
            if (m_floatPackets[i].depthMeters <= shallowMax) {
                shallowIndex = i;
                break;
            }
        }
        if (shallowIndex < 0)
            break;

        ++foundProfiles;
        int end = m_floatPackets.size() - 1;
        for (int i = shallowIndex + 1; i < m_floatPackets.size(); ++i) {
            if (m_floatPackets[i].depthMeters >= deepMin) {
                end = i - 1;
                break;
            }
        }

        if (foundProfiles == profileNumber) {
            int score = 10;
            if (evidence)
                *evidence << QString("  Completed descent/ascent between %1s and %2s: +10")
                                  .arg(m_floatPackets[deepIndex].timeSeconds, 0, 'f', 1)
                                  .arg(m_floatPackets[shallowIndex].timeSeconds, 0, 'f', 1);

            const bool deepHold = hasConsecutiveHold(deepMin, deepMax, deepIndex, end);
            const bool shallowHold = hasConsecutiveHold(shallowMin, shallowMax, shallowIndex, end);
            if (deepHold) {
                score += 5;
                if (evidence)
                    *evidence << "  2.5 m hold has 7 sequential packets over 30 seconds: +5";
            } else if (evidence) {
                *evidence << "  2.5 m hold evidence missing or not continuous.";
            }
            if (shallowHold) {
                score += 5;
                if (evidence)
                    *evidence << "  40 cm hold has 7 sequential packets over 30 seconds: +5";
            } else if (evidence) {
                *evidence << "  40 cm hold evidence missing or not continuous.";
            }

            bool breached = false;
            for (int i = deepIndex; i <= end && i < m_floatPackets.size(); ++i) {
                if (m_floatPackets[i].depthMeters < shallowMin) {
                    breached = true;
                    break;
                }
            }
            if (breached) {
                score = qMax(0, score - 5);
                if (evidence)
                    *evidence << "  Possible surface/ice contact from shallow packet: -5";
            }
            return score;
        }

        start = qMax(shallowIndex + 1, end + 1);
    }

    if (evidence)
        *evidence << QString("  Profile %1 not detected yet.").arg(profileNumber);
    return 0;
}

bool MainWindow::hasConsecutiveHold(double minDepth, double maxDepth, int startIndex, int endIndex) const
{
    for (int i = qMax(0, startIndex); i <= endIndex && i < m_floatPackets.size(); ++i) {
        if (m_floatPackets[i].depthMeters < minDepth || m_floatPackets[i].depthMeters > maxDepth)
            continue;
        int count = 1;
        const double startTime = m_floatPackets[i].timeSeconds;
        for (int j = i + 1; j <= endIndex && j < m_floatPackets.size(); ++j) {
            if (m_floatPackets[j].depthMeters < minDepth || m_floatPackets[j].depthMeters > maxDepth)
                break;
            ++count;
            if (count >= 7 && m_floatPackets[j].timeSeconds - startTime >= 30.0)
                return true;
        }
    }
    return false;
}

// ─────────────────────────────────────────────────────────────────────────────
// Home (back) buttons
// ─────────────────────────────────────────────────────────────────────────────

void MainWindow::on_homePageButton_clicked()
{
    // Camera page → main menu: disconnect stream, release webcam, reset mode
    m_cameraReceiver->disconnectFromHost();
    if (m_webcamActive)
        ui->webcamTestButton->setChecked(false); // triggers stopWebcam()
    m_currentMode = "hi";
    updateModeButton();
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_homePageButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::on_homePageButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::on_homePageButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::on_homePageButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::on_homePageButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

// Bottom-left settings button → ROV Setup page
void MainWindow::on_pushButton_clicked() { ui->stackedWidget->setCurrentIndex(6); }

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (m_rovSetup)
        m_rovSetup->shutdownAll();
    QMainWindow::closeEvent(event);
}

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

    //+
    // YOLOv8 crab detection — inference runs on a worker thread (never here on
    // the GUI thread). This frame is overlaid with the most recent results,
    // which may be a few frames old; for crab counting that's fine, and the
    // video stays at full framerate.
    if (m_detectionEnabled && m_crabDetector.isLoaded()) {
        // Dispatch an inference for ~every 3rd frame, but only when the previous
        // one has finished — drop frames rather than queue them.
        ++m_detDispatchCounter;
        if (!m_detRunning && (m_detDispatchCounter % 3 == 0)) {
            m_detRunning = true;
            const QImage snapshot = image.copy();
            m_detWatcher.setFuture(QtConcurrent::run(
                [this, snapshot]() { return m_crabDetector.detect(snapshot); }));
        }
    } else {
        m_lastDetections.clear();
    }

    QImage displayImage = image;   // shared; deep-copied only if we draw overlays
    if (m_detectionEnabled && !m_lastDetections.isEmpty()) {
        displayImage = image.copy();
        QPainter painter(&displayImage);
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        painter.setFont(font);

        for (const auto &det : m_lastDetections)
        {
            float threshold = 0.70f;

            if (det.species == "European-Green-Crabs")
                threshold = 0.87f;
            else if (det.species == "Atlantic-Rock-Crabs")
                threshold = 0.72f;

            if (det.confidence < threshold)
                continue;

            // Color per species
            if (det.species == "European-Green-Crabs")
                painter.setPen(QPen(Qt::green, 2));
            else if (det.species == "Atlantic-Rock-Crabs")
                painter.setPen(QPen(Qt::red, 2));
            else if (det.species == "Jonah-Crabs")
                painter.setPen(QPen(Qt::yellow, 2));

            painter.drawRect(det.box);

            // Identify species + confidence
            QString label = QString("%1  %2%")
                                .arg(det.species)
                                .arg(static_cast<int>(det.confidence * 100));

            // Text background
            QFontMetrics fm(font);
            QRect textRect = fm.boundingRect(label);
            textRect.moveTopLeft({ det.box.x(), det.box.y() - textRect.height() - 4 });
            painter.fillRect(textRect.adjusted(-3, -2, 3, 2), QColor(0, 0, 0, 160));
            painter.drawText(textRect.bottomLeft(), label);
        }
    }
    //+

    QPixmap pm = QPixmap::fromImage(displayImage).scaled(ui->graphicsView->viewport()->size(),
                                                  Qt::KeepAspectRatio,
                                                  Qt::SmoothTransformation);
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

    // Push the GUI's current mode to the Pi so the two never disagree. Without
    // this the server boots at its own DEFAULT_MODE and we'd silently stream a
    // different resolution than the mode button claims (e.g. full 16 MP @ 10fps).
    m_cameraReceiver->setMode(m_currentMode);
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
        ui->captureFramesButton->setStyleSheet("background-color: rgb(210,80,80);"
                                               "color: white;"
                                               "border-width: 3px;"
                                               "border-style: ridge;"
                                               "border-color: rgb(255,60,60);");
    } else {
        ui->captureFramesButton->setText("Capture Frames");
        ui->captureFramesButton->setStyleSheet("background-color: rgb(44,181,222);"
                                               "color: white;"
                                               "border-width: 3px;"
                                               "border-style: ridge;"
                                               "border-color: rgb(152,199,65);");
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// Local webcam test feed
//
// Opens the laptop's built-in/USB webcam on demand for testing the camera
// display + crab-detection pipeline without an ROV attached. Frames are fed into
// onCameraFrame(), the same path the network stream uses, so detection overlays
// work identically. The webcam and the Pi network stream are mutually exclusive.
// ─────────────────────────────────────────────────────────────────────────────

void MainWindow::on_webcamTestButton_toggled(bool checked)
{
    if (checked)
        startWebcam();
    else
        stopWebcam();
}

void MainWindow::startWebcam()
{
    if (m_webcamActive)
        return;

    // Mutual exclusion: drop the ROV network stream while the webcam is live.
    if (m_cameraReceiver->isConnected())
        m_cameraReceiver->disconnectFromHost();

    const auto cameras = QMediaDevices::videoInputs();
    if (cameras.isEmpty()) {
        qDebug() << "Webcam test: no camera found";
        ui->latencyLabel->setText("Webcam: no camera found");
        // Bounce the button back out (without re-triggering this handler).
        QSignalBlocker block(ui->webcamTestButton);
        ui->webcamTestButton->setChecked(false);
        return;
    }

    if (!m_webcam) {
        m_webcam = new QCamera(cameras.first(), this);
        m_videoSink = new QVideoSink(this);
        m_captureSession.setCamera(m_webcam);
        m_captureSession.setVideoSink(m_videoSink);
    }

    m_webcamFrameConn = connect(
        m_videoSink, &QVideoSink::videoFrameChanged, this,
        [this](const QVideoFrame &frame) {
            if (!frame.isValid())
                return;
            QVideoFrame copy(frame);
            if (!copy.map(QVideoFrame::ReadOnly))
                return;
            QImage image = copy.toImage();
            copy.unmap();
            if (!image.isNull())
                onCameraFrame(image);
        });

    auto startCapture = [this]() {
        m_webcam->start();
        m_webcamActive = true;
        ui->camName->setText("Camera:  Webcam (test)");
        ui->latencyLabel->setText("Webcam: live");
        qDebug() << "Webcam test: started";
    };

    // Request camera permission where the platform requires it (macOS), then
    // start. On platforms without the permission concept this is Granted already.
    const auto status = qApp->checkPermission(QCameraPermission{});
    if (status == Qt::PermissionStatus::Undetermined) {
        qApp->requestPermission(QCameraPermission{}, this,
            [this, startCapture](const QPermission &permission) {
                if (permission.status() == Qt::PermissionStatus::Granted) {
                    startCapture();
                } else {
                    qDebug() << "Webcam test: camera permission denied";
                    ui->latencyLabel->setText("Webcam: permission denied");
                    QSignalBlocker block(ui->webcamTestButton);
                    ui->webcamTestButton->setChecked(false);
                }
            });
    } else if (status == Qt::PermissionStatus::Granted) {
        startCapture();
    } else {
        qDebug() << "Webcam test: camera permission denied";
        ui->latencyLabel->setText("Webcam: permission denied");
        QSignalBlocker block(ui->webcamTestButton);
        ui->webcamTestButton->setChecked(false);
    }
}

void MainWindow::stopWebcam()
{
    if (!m_webcamActive && !m_webcam)
        return;

    disconnect(m_webcamFrameConn);
    if (m_webcam)
        m_webcam->stop();
    m_webcamActive = false;

    if (m_pixmapItem)
        m_pixmapItem->setPixmap(QPixmap()); // clear stale frame
    m_lastDetections.clear();

    ui->latencyLabel->setText("Webcam: off");
    qDebug() << "Webcam test: stopped";
}

// ─────────────────────────────────────────────────────────────────────────────
// Clock
// ─────────────────────────────────────────────────────────────────────────────

void MainWindow::updateClock()
{
    ui->timeLabel->setText(QDateTime::currentDateTime().toString("hh:mm:ss"));
}

// ─────────────────────────────────────────────────────────────────────────────
// ALS telemetry
// ─────────────────────────────────────────────────────────────────────────────

void MainWindow::onAlsDataReady(bool als, double pitch, double yaw)
{
    if (als) {
        const QString text = QString("ALS: ON  P:%1  Y:%2").arg(pitch, 0, 'f', 2).arg(yaw, 0, 'f', 2);
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

    double sum = snowInput + acadianInput + westernInput + urchinInput + rockInput + jonahInput
                 + sunstarInput + greenInput + borealInput + brittleInput;

    if (sum == 0)
        return;

    ui->snowCrabPercent->display((snowInput / sum) * 100);
    ui->acadianCrabPercent->display((acadianInput / sum) * 100);
    ui->hairyCrabPercent->display((westernInput / sum) * 100);
    ui->urchinPercent->display((urchinInput / sum) * 100);
    ui->rockCrabPercent->display((rockInput / sum) * 100);
    ui->jonahCrabPercent->display((jonahInput / sum) * 100);
    ui->sunstarPercent->display((sunstarInput / sum) * 100);
    ui->greenCrabPercent->display((greenInput / sum) * 100);
    ui->borealPercent->display((borealInput / sum) * 100);
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
    // Cycle: hi (3 MP) → hq (photogrammetry) → hi
    if (m_currentMode == "hi")
        m_currentMode = "hq";
    else
        m_currentMode = "hi";
    m_cameraReceiver->setMode(m_currentMode);
    updateModeButton();
}

void MainWindow::updateModeButton()
{
    const QString styleTmpl =
        "background-color: %1;"
        "color: white;"
        "border-width: 3px;"
        "border-style: ridge;"
        "border-color: %2;"
        "border-radius: 6px;"
        "font-size: 13px;"
        "font-weight: bold;";

    if (m_currentMode == "hi") {
        ui->modeButton->setText("Hi-Res  2048x1536 @ 30fps");
        ui->modeButton->setToolTip(
            "Currently: Hi-Res (3 MP cameras)\nClick to switch to HQ photogrammetry");
        ui->modeButton->setStyleSheet(styleTmpl.arg("rgb(120,180,90)", "rgb(200,230,120)"));
    } else {
        ui->modeButton->setText("HQ  4656x3496 @ 10fps");
        ui->modeButton->setToolTip(
            "Currently: HQ photogrammetry\nClick to switch to Hi-Res 2048x1536");
        ui->modeButton->setStyleSheet(styleTmpl.arg("rgb(210,160,20)", "rgb(255,220,80)"));
    }
}

/**
 * Highlights the active camera button with a bright border and dims the rest.
 * The style keeps the same base colours as the rest of the UI.
 */
void MainWindow::setActiveCamButton(const QString &name)
{
    static const QString activeStyle = "background-color: rgb(44,181,222);"
                                       "border-width: 4px;"
                                       "border-style: ridge;"
                                       "border-color: rgb(255, 255, 255);" // white border = active
                                       "color: rgb(255,255,255);"
                                       "font-weight: bold;";

    static const QString inactiveStyle = "background-color: rgb(44,181,222);"
                                         "border-width: 4px;"
                                         "border-style: ridge;"
                                         "border-color: rgb(152, 199, 65);" // green border = inactive
                                         "selection-color: rgb(255, 255, 255);";

    ui->frontCamButton->setStyleSheet(name == "front" ? activeStyle : inactiveStyle);
    ui->leftCamButton->setStyleSheet(name == "left" ? activeStyle : inactiveStyle);
    ui->rightCamButton->setStyleSheet(name == "right" ? activeStyle : inactiveStyle);
    ui->botCamButton->setStyleSheet(name == "bot" ? activeStyle : inactiveStyle);
    ui->backCamButton->setStyleSheet(name == "back" ? activeStyle : inactiveStyle);
}
void MainWindow::updateIcebergTracking(double iceX,
                                       double iceY,
                                       double headingDeg,
                                       double maxKeelDepth,
                                       QVector<QPointF> perimeterPoints)
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

    if (m_manualKeelSpin && maxKeelDepth > 0.0)
        m_manualKeelSpin->setValue(maxKeelDepth);
    if (m_icebergHeadingSpin)
        m_icebergHeadingSpin->setValue(std::fmod(headingDeg + 360.0, 360.0));
    updateIcebergAnalysis();
}

void MainWindow::on_btnRecordDepth_clicked()
{
    double currentLiveDepth = m_cameraReceiver->getLiveDepth();

    if (m_manualKeelSpin)
        m_manualKeelSpin->setValue(currentLiveDepth);
    updateIcebergAnalysis();
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

    connect(m_runner, &ColmapRunner::stepStarted, this, &MainWindow::onStepStarted);
    connect(m_runner, &ColmapRunner::progressOutput, this, &MainWindow::onProgressOutput);
    connect(m_runner, &ColmapRunner::stepFinished, this, &MainWindow::onStepFinished);
    connect(m_runner, &ColmapRunner::pipelineFinished, this, &MainWindow::onPipelineFinished);
    connect(m_runner, &ColmapRunner::errorOccurred, this, &MainWindow::onError);

    connect(ui->viewer, &ModelViewer::scalePointsPicked, this, &MainWindow::onScalePointsPicked);

    connect(ui->viewer, &ModelViewer::scaleApplied, [this](float w, float h, float d) {
        ui->statusLabel->setText(QString("Scale set — W:%1 m  H:%2 m  D:%3 m")
                                     .arg(w, 0, 'f', 3)
                                     .arg(h, 0, 'f', 3)
                                     .arg(d, 0, 'f', 3));
        ui->scaleButton->setChecked(false);
    });

    connect(ui->viewer,
            &ModelViewer::measurementReady,
            [this](float total, float dx, float dy, float dz) {
                ui->statusLabel->setText(QString("A→B: %1 m    ΔX:%2  ΔY:%3  ΔZ:%4")
                                             .arg(total, 0, 'f', 3)
                                             .arg(dx, 0, 'f', 3)
                                             .arg(dy, 0, 'f', 3)
                                             .arg(dz, 0, 'f', 3));
                ui->measureButton->setChecked(false);
            });

    ui->scaleButton->setToolTip("Click two points of known distance to set real-world scale");
    ui->measureButton->setToolTip("Click two points to measure the distance between them");
#if defined(Q_OS_WIN)
    ui->denseCheckBox->setToolTip(
        "Enables CUDA for COLMAP dense stereo on Windows.\nFeature extraction/matching and "
        "patch_match_stereo use the GPU when CUDA is available.\nSparse mapper and stereo_fusion "
        "remain CPU-bound.");
#else
    ui->denseCheckBox->setToolTip(
        "Runs CPU-based dense reconstruction via OpenMVS DensifyPointCloud.\nSlower than CUDA but "
        "works on any hardware.");
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

    for (const QString &dir :
         {QString("C:/Program Files/COLMAP"), QString("C:/Program Files (x86)/COLMAP"), base}) {
        QString p = dir + "/colmap.exe";
        if (QFileInfo::exists(p))
            return p;
    }
#elif defined(Q_OS_MACOS)
    QString macPath = base + "/tools/macos/bin/colmap";
    if (QFileInfo::exists(macPath) && QSysInfo::currentCpuArchitecture() == "arm64")
        return macPath;
#else
    QString linuxPath = base + "/tools/linux/bin/colmap";
    if (QFileInfo::exists(linuxPath))
        return linuxPath;
#endif

    QString onPath = QStandardPaths::findExecutable("colmap");
    if (!onPath.isEmpty() && isRealColmap(onPath))
        return onPath;

    QString chosen = QFileDialog::getOpenFileName(this,
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
    QStringList files
        = QFileDialog::getOpenFileNames(this,
                                        "Import Images",
                                        QString(),
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
    QString videoPath = QFileDialog::getOpenFileName(this,
                                                     "Import Video",
                                                     QString(),
                                                     "Video (*.mp4 *.avi *.mov *.mkv *.webm)");

    if (videoPath.isEmpty())
        return;

    ui->statusLabel->setText("Extracting frames from video...");
    setRunning(true);

    QProcess *ffmpeg = new QProcess(this);
    QString outputPattern = m_imagePath + "/frame_%04d.jpg";
    QString filter = "select=not(mod(n\\,10))";

    ffmpeg->start("ffmpeg",
                  {"-i", videoPath, "-vf", filter, "-vsync", "vfr", "-q:v", "2", outputPattern});

    connect(ffmpeg,
            QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            [this, ffmpeg](int exitCode, QProcess::ExitStatus) {
                ffmpeg->deleteLater();
                setRunning(false);

                if (exitCode == 0) {
                    refreshThumbnails();
                    int count = QDir(m_imagePath)
                                    .entryList({"*.jpg", "*.jpeg", "*.png", "*.tiff"}, QDir::Files)
                                    .count();
                    ui->statusLabel->setText(
                        QString("Extracted frames — %1 images ready").arg(count));
                } else {
                    ui->statusLabel->setText("Frame extraction failed. Is ffmpeg installed?");
                    ui->logOutput->append("[ERROR] ffmpeg exited with code "
                                          + QString::number(exitCode));
                }
            });

    if (!ffmpeg->waitForStarted(3000)) {
        ffmpeg->deleteLater();
        setRunning(false);
        ui->statusLabel->setText("Could not start ffmpeg. Make sure it's installed and on PATH.");
    }
}

void MainWindow::on_clearButton_clicked()
{
    QDir imgDir(m_imagePath);
    QStringList images = imgDir.entryList({"*.jpg", "*.jpeg", "*.png", "*.tiff", "*.tif", "*.bmp"},
                                          QDir::Files);

    if (images.isEmpty())
        return;

    auto answer
        = QMessageBox::question(this,
                                "Clear Images",
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
    for (const QString &f :
         wsDir.entryList({"depth*.dmap", "scene*.mvs", "dense*.mvs", "*.ply"}, QDir::Files))
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
    QStringList images = imgDir.entryList({"*.jpg", "*.jpeg", "*.png", "*.tiff", "*.tif", "*.bmp"},
                                          QDir::Files,
                                          QDir::Name);

    for (const QString &filename : images) {
        QPixmap pix(imgDir.filePath(filename));
        if (pix.isNull())
            continue;

        auto *item = new QListWidgetItem(QIcon(pix.scaled(120,
                                                          90,
                                                          Qt::KeepAspectRatio,
                                                          Qt::SmoothTransformation)),
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
    int count = imgDir.entryList({"*.jpg", "*.jpeg", "*.png", "*.tiff"}, QDir::Files).count();
    if (count < 3) {
        ui->statusLabel->setText("Need at least 3 images to reconstruct");
        return;
    }

#if !defined(Q_OS_WIN)
    if (ui->denseCheckBox->isChecked()) {
        const QString toolsBin = QCoreApplication::applicationDirPath() + "/tools/linux/bin/";
        auto hasTool = [&](const QString &name) {
            return !QStandardPaths::findExecutable(name).isEmpty()
                || QFileInfo::exists(toolsBin + name);
        };
        QStringList missing;
        if (!hasTool("InterfaceCOLMAP"))
            missing << "InterfaceCOLMAP";
        if (!hasTool("DensifyPointCloud"))
            missing << "DensifyPointCloud";
        if (!missing.isEmpty()) {
            QMessageBox box(this);
            box.setIcon(QMessageBox::Warning);
            box.setWindowTitle("OpenMVS tools missing");
            box.setText("Dense reconstruction needs OpenMVS binaries on PATH but "
                        "these were not found:\n\n  • "
                        + missing.join("\n  • ")
                        + "\n\nInstall OpenMVS, or run sparse reconstruction only?");
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
    ui->logOutput->verticalScrollBar()->setValue(ui->logOutput->verticalScrollBar()->maximum());
}

void MainWindow::onStepFinished(const QString &step, bool success)
{
    ui->progressBar->setValue(ui->progressBar->value() + 1);
    ui->logOutput->append(success ? QString::fromUtf8("✓ ") + step + " complete."
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

void MainWindow::on_resetCameraButton_clicked()
{
    ui->viewer->resetCamera();
}

void MainWindow::on_loadPlyButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,
                                                "Open PLY File",
                                                QString(),
                                                "PLY Files (*.ply)");
    if (path.isEmpty())
        return;
    ui->viewer->loadPLY(path);
    ui->statusLabel->setText("Loaded: " + QFileInfo(path).fileName());
}

void MainWindow::on_scaleButton_toggled(bool on)
{
    if (on) {
        ui->measureButton->setChecked(false);
        ui->viewer->enterScaleMode();
    } else
        ui->viewer->exitPickMode();
}

void MainWindow::on_measureButton_toggled(bool on)
{
    if (on) {
        ui->scaleButton->setChecked(false);
        ui->viewer->enterMeasureMode();
    } else
        ui->viewer->exitPickMode();
}

void MainWindow::onScalePointsPicked(float /*measuredModelDist*/)
{
    bool ok;
    double val
        = QInputDialog::getDouble(this,
                                  "Set Scale",
                                  "Real-world distance between the two selected points (metres):",
                                  0.1,
                                  0.001,
                                  10000.0,
                                  4,
                                  &ok);
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
            ui->statusLabel->setText("Dense reconstruction complete — use mouse to orbit/pan/zoom");
            ui->logOutput->append(QString::fromUtf8("✓ ") + "Dense model loaded into viewer.");
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

    connect(converter,
            QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            [this, converter, plyPath](int exitCode, QProcess::ExitStatus) {
                converter->deleteLater();

                if (exitCode == 0 && QFile::exists(plyPath)) {
                    ui->logOutput->append("\n=== Loading 3D Model ===");
                    ui->viewer->loadPLY(plyPath);
                    ui->statusLabel->setText(
                        "Reconstruction complete — use mouse to orbit/pan/zoom");
                    ui->logOutput->append(QString::fromUtf8("✓ ") + "Model loaded into viewer.");
                } else {
                    ui->statusLabel->setText("Model conversion failed");
                    ui->logOutput->append("[ERROR] model_converter failed with exit code "
                                          + QString::number(exitCode));
                    ui->logOutput->append(QString::fromUtf8(converter->readAllStandardError()));
                }
            });

    QString colmapPath = detectColmapPath();
    converter->start(colmapPath,
                     {"model_converter",
                      "--input_path",
                      sparsePath,
                      "--output_path",
                      plyPath,
                      "--output_type",
                      "PLY"});

    if (!converter->waitForStarted(5000)) {
        converter->deleteLater();
        ui->statusLabel->setText("Failed to start model converter");
    }
}
// Instantly updates the live LCD whenever a UDP packet arrives
void MainWindow::updateLiveDepthDisplay(double depth)
{
    m_currentDepth = depth;
    if (m_liveDepthLcd)
        m_liveDepthLcd->display(depth);
}

void MainWindow::updateIcebergAnalysis()
{
    if (!m_platformThreatTable || !m_manualKeelSpin || !m_icebergLatSpin
        || !m_icebergLonSpin || !m_icebergHeadingSpin)
        return;

    const double icebergLat = m_icebergLatSpin->value();
    const double icebergLon = m_icebergLonSpin->value();
    const double headingRad = qDegreesToRadians(m_icebergHeadingSpin->value());
    const double keelDepth = m_manualKeelSpin->value();
    const double trackX = qSin(headingRad);
    const double trackY = qCos(headingRad);

    auto closestApproachNm = [&](const PlatformInfo &platform) {
        const double meanLatRad = qDegreesToRadians((icebergLat + platform.latitude) / 2.0);
        const double dx = (platform.longitude - icebergLon) * 60.0 * qCos(meanLatRad);
        const double dy = (platform.latitude - icebergLat) * 60.0;
        const double alongTrack = dx * trackX + dy * trackY;
        if (alongTrack < 0.0)
            return std::hypot(dx, dy);
        const double crossTrack = dx * trackY - dy * trackX;
        return qAbs(crossTrack);
    };

    auto surfaceThreat = [&](double distanceNm, double platformDepth) {
        if (keelDepth >= platformDepth * 1.10)
            return QStringLiteral("GREEN");
        if (distanceNm < 5.0)
            return QStringLiteral("RED");
        if (distanceNm <= 10.0)
            return QStringLiteral("YELLOW");
        return QStringLiteral("GREEN");
    };

    auto subseaThreat = [&](double distanceNm, double platformDepth) {
        if (distanceNm > 25.0)
            return QStringLiteral("GREEN");
        const double ratio = platformDepth > 0.0 ? keelDepth / platformDepth : 0.0;
        if (ratio >= 1.10)
            return QStringLiteral("GREEN");
        if (ratio >= 0.90)
            return QStringLiteral("RED");
        if (ratio >= 0.70)
            return QStringLiteral("YELLOW");
        return QStringLiteral("GREEN");
    };

    auto setItem = [&](int row, int column, const QString &text, const QString &threat = QString()) {
        auto *item = new QTableWidgetItem(text);
        item->setTextAlignment(Qt::AlignCenter);
        if (threat == "RED") {
            item->setForeground(Qt::white);
            item->setBackground(QColor(QStringLiteral("#b3261e")));
        } else if (threat == "YELLOW") {
            item->setForeground(QColor(QStringLiteral("#1d1b16")));
            item->setBackground(QColor(QStringLiteral("#f4c542")));
        } else if (threat == "GREEN") {
            item->setForeground(Qt::white);
            item->setBackground(QColor(QStringLiteral("#2e7d32")));
        }
        m_platformThreatTable->setItem(row, column, item);
    };

    QStringList summary;
    QStringList surveyed;
    for (QLineEdit *edit : m_surveyNumberEdits)
        surveyed << (edit && !edit->text().trimmed().isEmpty() ? edit->text().trimmed() : QStringLiteral("_"));

    summary << QStringLiteral("Survey numbers shown: %1").arg(surveyed.join(QStringLiteral(", ")));
    summary << QStringLiteral("Measured keel depth: %1 m").arg(keelDepth, 0, 'f', 2);
    summary << QStringLiteral("Iceberg position: %1, %2 | heading %3 deg")
                   .arg(icebergLat, 0, 'f', 4)
                   .arg(icebergLon, 0, 'f', 4)
                   .arg(m_icebergHeadingSpin->value(), 0, 'f', 1);
    summary << QStringLiteral("");

    if (m_tacticalScene) {
        m_tacticalScene->clear();
        m_icebergMarker = m_tacticalScene->addEllipse(-5, -5, 10, 10, QPen(Qt::cyan, 2), QBrush(Qt::cyan));
        m_headingVector = m_tacticalScene->addLine(0, 0, trackX * 120.0, -trackY * 120.0, QPen(Qt::red, 3));
        m_icebergPerimeter = m_tacticalScene->addPolygon(QPolygonF(), QPen(Qt::cyan, 1, Qt::DashLine));
    }

    for (int i = 0; i < 4; ++i) {
        const PlatformInfo &platform = kPlatforms[i];
        const double distanceNm = closestApproachNm(platform);
        const QString surface = surfaceThreat(distanceNm, platform.depthMeters);
        const QString subsea = subseaThreat(distanceNm, platform.depthMeters);

        setItem(i, 0, QString::fromLatin1(platform.name));
        setItem(i, 1, QString::number(platform.latitude, 'f', 4));
        setItem(i, 2, QString::number(platform.longitude, 'f', 4));
        setItem(i, 3, QString::number(platform.depthMeters, 'f', 0));
        setItem(i, 4, QString::number(distanceNm, 'f', 1));
        setItem(i, 5, surface, surface);
        setItem(i, 6, subsea, subsea);

        summary << QStringLiteral("%1: surface %2, subsea %3, closest approach %4 NM")
                       .arg(QString::fromLatin1(platform.name), surface, subsea)
                       .arg(distanceNm, 0, 'f', 1);

        if (m_tacticalScene) {
            const double meanLatRad = qDegreesToRadians((icebergLat + platform.latitude) / 2.0);
            const double x = (platform.longitude - icebergLon) * 60.0 * qCos(meanLatRad);
            const double y = (platform.latitude - icebergLat) * 60.0;
            const QColor color = surface == "RED" ? QColor("#b3261e")
                                 : surface == "YELLOW" ? QColor("#f4c542")
                                                        : QColor("#2e7d32");
            m_tacticalScene->addEllipse(x - 4.0, -y - 4.0, 8.0, 8.0, QPen(color), QBrush(color));
            m_tacticalScene->addText(QString::fromLatin1(platform.name))->setPos(x + 6.0, -y - 10.0);
        }
    }

    if (m_tacticalView && m_tacticalScene)
        m_tacticalView->fitInView(m_tacticalScene->itemsBoundingRect().adjusted(-20, -20, 20, 20),
                                  Qt::KeepAspectRatio);
    if (m_judgeSummary)
        m_judgeSummary->setPlainText(summary.join(QStringLiteral("\n")));
}

// Instantly moves the blue dot on the map when telemetry supplies live coordinates.
void MainWindow::updateIcebergPosition(double x, double y)
{
    if (m_icebergMarker != nullptr) {
        m_icebergMarker->setPos(x, y);
    }
}
