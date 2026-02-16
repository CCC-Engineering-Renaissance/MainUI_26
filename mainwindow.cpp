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
#include <QSpinBox>
#include <QLCDNumber>
#include <QLabel>
#include <QVBoxLayout>
#include <QPixmap>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //image setup
    QLabel *imageLabel = new QLabel(this);
    QPixmap pixmap(":/images/rov_logo_complete.png");
    imageLabel->setPixmap(pixmap);
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
    double sumOfInputs = snowInput+acadianInput+westernInput+urchinInput+rockInput+
                      jonahInput+sunstarInput+greenInput+borealInput+brittleInput;

    /// Assigns the percentage frequency to an object

    double snowPercent = (snowInput/sumOfInputs) * 100;
    double acadianPercent = (acadianInput/sumOfInputs) * 100;
    double westernPercent = (westernInput/sumOfInputs) * 100;
    double seaUrchinPercent = (urchinInput/sumOfInputs) * 100;
    double rockPercent = (rockInput/sumOfInputs) * 100;
    double jonahPercent = (jonahInput/sumOfInputs) * 100;
    double spinySunstarPercent = (sunstarInput/sumOfInputs) * 100;
    double greenPercent = (greenInput/sumOfInputs) * 100;
    double borealStarPercent = (borealInput/sumOfInputs) * 100;
    double brittleStarPercent = (brittleInput/sumOfInputs) * 100;

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

