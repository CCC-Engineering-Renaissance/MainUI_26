#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTabBar>
#include <QKeyEvent>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QStackedLayout>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsVideoItem>
#include <QGraphicsProxyWidget>
#include <QDateTime>
#include <QTime>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

    /// User can press escape at any screen to go back to the main menu
void MainWindow::keyPressEvent(QKeyEvent *event){
    ///See if user pressed esc
    if(event->key() == Qt::Key_Escape){
        if(ui->stackedWidget->currentIndex() != 0){
            ui->stackedWidget->setCurrentIndex(0);
        }
    }
    else{
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


/// Time Display
void MainWindow::updateTimeLabel() {
    // Get the current time
    QTime time = QTime::currentTime();
    // Set the time to a string
    QString timeString = time.toString("hh:mm:ss");
    // Set label text to current time
    ui->timeLabel->setText(timeString);
}

// /// Timer for Time display Updates
// QTimer *timer = new QTimer();
// // Connect the timer's timeout() signal to a lambda function that updates the label
// QObject::connect(timer, &QTimer::timeout, [&label]() {
//     updateTimeLabel(timeLabel);
// });

// // Start the timer to trigger every 1000 milliseconds (1 second)
// timer->start(1000);
