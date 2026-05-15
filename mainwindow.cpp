#include "mainwindow.h"
#include <QDateTime>
#include <QFontDatabase>
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <QGraphicsVideoItem>
#include <QImage>
#include <QKeyEvent>
#include <QLCDNumber>
#include <QLabel>
#include <QMediaPlayer>
#include <QMessageBox>
#include <QPixmap>
#include <QSpinBox>
#include <QStackedLayout>
#include <QString>
#include <QTabBar>
#include <QTime>
#include <QVBoxLayout>
#include <QVideoWidget>
#include <QWidget>

#include <QDebug>
#include <QDir>

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , scene(new QGraphicsScene(this))
    , pixmapItem(new QGraphicsPixmapItem())
    , timer(new QTimer(this))
{
    ui->setupUi(this);
    resize(1200, 800);
    setMinimumSize(900, 600);

    //image setup
    QPixmap pixmap(":/images/images/rov_logo_complete.png");
    //ui->crush_label->setPixmap(pixmap);
    if (pixmap.isNull()) {
        ui->crush_label->setText("Error: Logo not found!");
    } else {
        int maxWidth = 250;
        int maxHeight = 250;
        QPixmap scaledPixmap = pixmap.scaled(maxWidth,
                                             maxHeight,
                                             Qt::KeepAspectRatio,
                                             Qt::SmoothTransformation);
        ui->crush_label->setPixmap(scaledPixmap);
        ui->crush_label->setAlignment(Qt::AlignCenter);
    }

    //font correction
    int fontId = QFontDatabase::addApplicationFont(":/font/fonts/aileron.black.otf");

    // 2. Check if it worked
    if (fontId == -1) {
        qDebug() << "Warning: Custom font failed to load from resources!";
    } else {
        // 3. Get the official "Family Name" so you know exactly what to call it in your CSS
        QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
        qDebug() << "Success! The font family name is:" << fontFamily;
    }

    //camera
    scene->addItem(pixmapItem);
    ui->graphicsView->setScene(scene);

    connect(ui->frontCamButton, &QPushButton::clicked, this, &MainWindow::startFrontCamera);
    connect(ui->homePageButton, &QToolButton::clicked, this, &MainWindow::stopCamera);

    connect(timer, &QTimer::timeout, this, &MainWindow::updateFrame);

    orb = cv::ORB::create();
    matcher = cv::BFMatcher::create(cv::NORM_HAMMING);

    qDebug() << "CURRENT DIR:" << QDir::currentPath();
    qDebug() << "APP DIR:" << QCoreApplication::applicationDirPath();
    qDebug() << QFile::exists("crabs/crab1.png");

    imgCrab1 = cv::imread("crabs/crab1.png", cv::IMREAD_GRAYSCALE);
    imgCrab2 = cv::imread("crabs/crab2.png", cv::IMREAD_GRAYSCALE);
    imgCrab3 = cv::imread("crabs/crab3.png", cv::IMREAD_GRAYSCALE);

    orb->detectAndCompute(imgCrab1, cv::noArray(), kpCrab1, desCrab1);
    orb->detectAndCompute(imgCrab2, cv::noArray(), kpCrab2, desCrab2);
    orb->detectAndCompute(imgCrab3, cv::noArray(), kpCrab3, desCrab3);
}

MainWindow::~MainWindow()
{
    stopCamera();
    delete ui;
}

/// User can press escape at any screen to go back to the main menu

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    ///See if user pressed esc
    if (event->key() == Qt::Key_Escape) {
        if (ui->stackedWidget->currentIndex() != 0) {
            ui->stackedWidget->setCurrentIndex(0);
        }
    } else {
        QMainWindow::keyPressEvent(event);
    }
}
/// Main menu button logic

void MainWindow::on_cameraFeedPushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
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

void MainWindow::on_homePageButton_clicked()
{
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

void MainWindow::on_closeProgramButton_clicked()
{
    close();
}

/// eDNA Percentage Calculator Function

void MainWindow::on_pushButtonCalcPercent_clicked()
{
    /// Assigns the number of times an animal has been seen to an object

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
    double sumOfInputs = snowInput + acadianInput + westernInput + urchinInput + rockInput
                         + jonahInput + sunstarInput + greenInput + borealInput + brittleInput;

    /// Assigns the percentage frequency to an object

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

    /// Displays that percent in the box

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

    /// IT WORKS LETS GOOOOOO
}

void MainWindow::startFrontCamera()
{
    // Open front camera
    if (!cap.isOpened())
        cap.open(0);

    if (cap.isOpened())
        timer->start(30); // 30 fps
}

void MainWindow::stopCamera()
{
    if (timer->isActive())
        timer->stop();
    if (cap.isOpened())
        cap.release();

    pixmapItem->setPixmap(QPixmap());
}

void MainWindow::updateFrame()
{
    cv::Mat frame;
    if (!cap.read(frame)) return;

    cv::Mat gray;
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

    ui->graphicsView->fitInView(pixmapItem, Qt::KeepAspectRatio);

    std::vector<cv::KeyPoint> kpFrame;
    cv::Mat desFrame;

    orb->detectAndCompute(gray, cv::noArray(), kpFrame, desFrame);


    if (desFrame.empty() || desCrab1.empty() || desCrab2.empty() || desCrab3.empty())
    {
        cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
        QImage qimg(frame.data, frame.cols, frame.rows, frame.step,
                    QImage::Format_RGB888);

        pixmapItem->setPixmap(QPixmap::fromImage(qimg));
        ui->graphicsView->fitInView(pixmapItem, Qt::KeepAspectRatio);
        return;
    }

    std::vector<cv::DMatch> matches1, matches2, matches3;

    matcher->match(desFrame, desCrab1, matches1);
    matcher->match(desFrame, desCrab2, matches2);
    matcher->match(desFrame, desCrab3, matches3);

    auto goodMatches = [](const std::vector<cv::DMatch>& matches)
    {
        int good = 0;
        for (const auto& m : matches)
        {
            if (m.distance < 40)
                good++;
        }
        return good;
    };

    int score1 = goodMatches(matches1);
    int score2 = goodMatches(matches2);
    int score3 = goodMatches(matches3);

    qDebug() << "Scores:" << score1 << score2 << score3;

    std::string label = "Unknown";

    int best = std::max({score1, score2, score3});

    if (best >= 15)
    {
        if (best == score1) label = "European Green Crab";
        else if (best == score2) label = "Rock Crab";
        else label = "Jonah Crab";
    }

    cv::putText(frame,
                label,
                cv::Point(30, 50),
                cv::FONT_HERSHEY_SIMPLEX,
                1.2,
                cv::Scalar(0, 255, 0),
                2);

    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);

    QImage qimg(frame.data,
                frame.cols,
                frame.rows,
                frame.step,
                QImage::Format_RGB888);

    pixmapItem->setPixmap(QPixmap::fromImage(qimg));

    ui->graphicsView->fitInView(pixmapItem, Qt::KeepAspectRatio);
}
