/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QStackedWidget *stackedWidget;
    QWidget *mainMenu;
    QGridLayout *gridLayout_3;
    QPushButton *closeProgramButton;
    QPushButton *icebergPushButton;
    QLabel *label_9;
    QPushButton *pushButton;
    QPushButton *modelingPushButton;
    QPushButton *cameraFeedPushButton;
    QPushButton *floatPushButton;
    QPushButton *ednaPushButton;
    QWidget *cameraPage;
    QGridLayout *gridLayout_2;
    QFrame *droneMap;
    QGridLayout *gridLayout;
    QPushButton *botCamButton;
    QPushButton *frontCamButton;
    QPushButton *backCamButton;
    QPushButton *leftCamButton;
    QPushButton *rightCamButton;
    QLabel *camName;
    QFrame *frame_6;
    QHBoxLayout *horizontalLayout_3;
    QLabel *latencyLabel;
    QLabel *timeLabel;
    QGraphicsView *graphicsView;
    QFrame *frame_5;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBox;
    QPushButton *scanCrabButton;
    QLCDNumber *lcdNumber_5;
    QToolButton *homePageButton;
    QWidget *modelingPage;
    QToolButton *homePageButton_2;
    QWidget *icebergPage;
    QToolButton *homePageButton_3;
    QWidget *ednaPage;
    QGridLayout *gridLayout_4;
    QLabel *label_11;
    QSpinBox *spinBoxRock;
    QSpinBox *spinBoxSnow;
    QLabel *label_8;
    QSpinBox *spinBoxJonah;
    QLabel *label_4;
    QSpinBox *spinBoxSunstar;
    QLCDNumber *hairyCrabPercent;
    QLabel *label_3;
    QLabel *label;
    QLabel *label_12;
    QLCDNumber *snowCrabPercent;
    QToolButton *homePageButton_4;
    QLCDNumber *rockCrabPercent;
    QSpinBox *spinBoxBoreal;
    QLCDNumber *brittlePercent;
    QLabel *label_10;
    QLabel *label_14;
    QLabel *label_5;
    QSpinBox *spinBoxWestern;
    QLabel *label_13;
    QSpinBox *spinBoxGreen;
    QSpinBox *spinBoxAcadian;
    QSpinBox *spinBoxUrchin;
    QLabel *label_2;
    QLCDNumber *borealPercent;
    QLabel *label_6;
    QLabel *label_7;
    QLCDNumber *greenCrabPercent;
    QLCDNumber *sunstarPercent;
    QLCDNumber *acadianCrabPercent;
    QLCDNumber *jonahCrabPercent;
    QLCDNumber *urchinPercent;
    QSpinBox *spinBoxBrittle;
    QPushButton *pushButtonCalcPercent;
    QWidget *floatPage;
    QToolButton *homePageButton_5;
    QWidget *settingsPage;
    QToolButton *homePageButton_6;
    QMenuBar *menubar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(839, 662);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::WeatherStorm));
        MainWindow->setWindowIcon(icon);
        MainWindow->setAnimated(false);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy1);
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        sizePolicy1.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy1);
        stackedWidget->setStyleSheet(QString::fromUtf8("background-color: rgba(150, 183, 255, 20);"));
        stackedWidget->setFrameShape(QFrame::Shape::Box);
        stackedWidget->setLineWidth(2);
        mainMenu = new QWidget();
        mainMenu->setObjectName("mainMenu");
        gridLayout_3 = new QGridLayout(mainMenu);
        gridLayout_3->setObjectName("gridLayout_3");
        closeProgramButton = new QPushButton(mainMenu);
        closeProgramButton->setObjectName("closeProgramButton");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(closeProgramButton->sizePolicy().hasHeightForWidth());
        closeProgramButton->setSizePolicy(sizePolicy2);
        QFont font;
        font.setFamilies({QString::fromUtf8("Comic Sans MS")});
        font.setPointSize(14);
        font.setBold(true);
        font.setItalic(false);
        font.setUnderline(false);
        font.setStrikeOut(false);
        font.setKerning(true);
        closeProgramButton->setFont(font);
        closeProgramButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::ApplicationExit));
        closeProgramButton->setIcon(icon1);
        closeProgramButton->setIconSize(QSize(20, 20));

        gridLayout_3->addWidget(closeProgramButton, 2, 2, 1, 1);

        icebergPushButton = new QPushButton(mainMenu);
        icebergPushButton->setObjectName("icebergPushButton");
        icebergPushButton->setMinimumSize(QSize(220, 140));
        icebergPushButton->setBaseSize(QSize(220, 100));
        icebergPushButton->setAutoFillBackground(false);
        icebergPushButton->setStyleSheet(QString::fromUtf8("\n"
"font: 14pt \"Comic Sans MS\";"));
        QIcon icon2(QIcon::fromTheme(QIcon::ThemeIcon::SystemSearch));
        icebergPushButton->setIcon(icon2);

        gridLayout_3->addWidget(icebergPushButton, 0, 2, 1, 1);

        label_9 = new QLabel(mainMenu);
        label_9->setObjectName("label_9");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Comic Sans MS")});
        font1.setPointSize(16);
        font1.setBold(true);
        label_9->setFont(font1);

        gridLayout_3->addWidget(label_9, 2, 1, 1, 1);

        pushButton = new QPushButton(mainMenu);
        pushButton->setObjectName("pushButton");
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Comic Sans MS")});
        font2.setPointSize(14);
        font2.setBold(false);
        pushButton->setFont(font2);

        gridLayout_3->addWidget(pushButton, 2, 0, 1, 1);

        modelingPushButton = new QPushButton(mainMenu);
        modelingPushButton->setObjectName("modelingPushButton");
        modelingPushButton->setMinimumSize(QSize(220, 140));
        modelingPushButton->setBaseSize(QSize(220, 100));
        modelingPushButton->setAutoFillBackground(false);
        modelingPushButton->setStyleSheet(QString::fromUtf8("font: 14pt \"Comic Sans MS\";"));
        QIcon icon3(QIcon::fromTheme(QIcon::ThemeIcon::CameraVideo));
        modelingPushButton->setIcon(icon3);

        gridLayout_3->addWidget(modelingPushButton, 0, 1, 1, 1);

        cameraFeedPushButton = new QPushButton(mainMenu);
        cameraFeedPushButton->setObjectName("cameraFeedPushButton");
        cameraFeedPushButton->setMinimumSize(QSize(220, 140));
        cameraFeedPushButton->setBaseSize(QSize(220, 100));
        cameraFeedPushButton->setAutoFillBackground(false);
        cameraFeedPushButton->setStyleSheet(QString::fromUtf8("font: 14pt \"Comic Sans MS\";"));
        QIcon icon4(QIcon::fromTheme(QIcon::ThemeIcon::MediaRecord));
        cameraFeedPushButton->setIcon(icon4);

        gridLayout_3->addWidget(cameraFeedPushButton, 0, 0, 1, 1);

        floatPushButton = new QPushButton(mainMenu);
        floatPushButton->setObjectName("floatPushButton");
        floatPushButton->setMinimumSize(QSize(220, 140));
        floatPushButton->setBaseSize(QSize(220, 100));
        floatPushButton->setAutoFillBackground(false);
        floatPushButton->setStyleSheet(QString::fromUtf8("\n"
"font: 14pt \"Comic Sans MS\";"));
        QIcon icon5(QIcon::fromTheme(QIcon::ThemeIcon::SoftwareUpdateAvailable));
        floatPushButton->setIcon(icon5);

        gridLayout_3->addWidget(floatPushButton, 1, 2, 1, 1);

        ednaPushButton = new QPushButton(mainMenu);
        ednaPushButton->setObjectName("ednaPushButton");
        ednaPushButton->setMinimumSize(QSize(220, 140));
        ednaPushButton->setBaseSize(QSize(220, 100));
        ednaPushButton->setAutoFillBackground(false);
        ednaPushButton->setStyleSheet(QString::fromUtf8("\n"
"font: 14pt \"Comic Sans MS\";"));
        QIcon icon6(QIcon::fromTheme(QIcon::ThemeIcon::MediaFlash));
        ednaPushButton->setIcon(icon6);

        gridLayout_3->addWidget(ednaPushButton, 1, 0, 1, 1);

        stackedWidget->addWidget(mainMenu);
        cameraPage = new QWidget();
        cameraPage->setObjectName("cameraPage");
        gridLayout_2 = new QGridLayout(cameraPage);
        gridLayout_2->setObjectName("gridLayout_2");
        droneMap = new QFrame(cameraPage);
        droneMap->setObjectName("droneMap");
        droneMap->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
        droneMap->setFrameShape(QFrame::Shape::Box);
        droneMap->setLineWidth(2);
        gridLayout = new QGridLayout(droneMap);
        gridLayout->setObjectName("gridLayout");
        botCamButton = new QPushButton(droneMap);
        botCamButton->setObjectName("botCamButton");
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Comic Sans MS")});
        font3.setKerning(true);
        botCamButton->setFont(font3);
        botCamButton->setStyleSheet(QString::fromUtf8("selection-color: rgb(255, 255, 255);"));

        gridLayout->addWidget(botCamButton, 2, 1, 1, 1);

        frontCamButton = new QPushButton(droneMap);
        frontCamButton->setObjectName("frontCamButton");
        frontCamButton->setFont(font3);
        frontCamButton->setStyleSheet(QString::fromUtf8("selection-color: rgb(255, 255, 255);"));

        gridLayout->addWidget(frontCamButton, 0, 1, 1, 1);

        backCamButton = new QPushButton(droneMap);
        backCamButton->setObjectName("backCamButton");
        backCamButton->setFont(font3);
        backCamButton->setStyleSheet(QString::fromUtf8("selection-color: rgb(255, 255, 255);"));

        gridLayout->addWidget(backCamButton, 3, 1, 1, 1);

        leftCamButton = new QPushButton(droneMap);
        leftCamButton->setObjectName("leftCamButton");
        leftCamButton->setFont(font3);
        leftCamButton->setStyleSheet(QString::fromUtf8("selection-color: rgb(255, 255, 255);"));

        gridLayout->addWidget(leftCamButton, 2, 0, 1, 1);

        rightCamButton = new QPushButton(droneMap);
        rightCamButton->setObjectName("rightCamButton");
        rightCamButton->setFont(font3);
        rightCamButton->setStyleSheet(QString::fromUtf8("selection-color: rgb(255, 255, 255);"));

        gridLayout->addWidget(rightCamButton, 2, 2, 1, 1);


        gridLayout_2->addWidget(droneMap, 3, 2, 1, 1);

        camName = new QLabel(cameraPage);
        camName->setObjectName("camName");
        QFont font4;
        font4.setPointSize(20);
        camName->setFont(font4);
        camName->setFrameShape(QFrame::Shape::Box);
        camName->setLineWidth(2);

        gridLayout_2->addWidget(camName, 0, 1, 1, 1);

        frame_6 = new QFrame(cameraPage);
        frame_6->setObjectName("frame_6");
        frame_6->setFrameShape(QFrame::Shape::Box);
        frame_6->setFrameShadow(QFrame::Shadow::Plain);
        frame_6->setLineWidth(2);
        horizontalLayout_3 = new QHBoxLayout(frame_6);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        latencyLabel = new QLabel(frame_6);
        latencyLabel->setObjectName("latencyLabel");
        QFont font5;
        font5.setFamilies({QString::fromUtf8("Comic Sans MS")});
        latencyLabel->setFont(font5);
        latencyLabel->setFrameShape(QFrame::Shape::Box);
        latencyLabel->setFrameShadow(QFrame::Shadow::Plain);

        horizontalLayout_3->addWidget(latencyLabel);

        timeLabel = new QLabel(frame_6);
        timeLabel->setObjectName("timeLabel");
        timeLabel->setFont(font5);
        timeLabel->setFrameShape(QFrame::Shape::Box);

        horizontalLayout_3->addWidget(timeLabel);


        gridLayout_2->addWidget(frame_6, 0, 2, 1, 1);

        graphicsView = new QGraphicsView(cameraPage);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setFrameShape(QFrame::Shape::Box);
        graphicsView->setFrameShadow(QFrame::Shadow::Plain);
        graphicsView->setLineWidth(3);
        graphicsView->setMidLineWidth(0);

        gridLayout_2->addWidget(graphicsView, 1, 0, 1, 3);

        frame_5 = new QFrame(cameraPage);
        frame_5->setObjectName("frame_5");
        frame_5->setFrameShape(QFrame::Shape::Box);
        frame_5->setFrameShadow(QFrame::Shadow::Plain);
        frame_5->setLineWidth(2);
        horizontalLayout = new QHBoxLayout(frame_5);
        horizontalLayout->setObjectName("horizontalLayout");
        comboBox = new QComboBox(frame_5);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setFont(font5);
        comboBox->setEditable(false);

        horizontalLayout->addWidget(comboBox);

        scanCrabButton = new QPushButton(frame_5);
        scanCrabButton->setObjectName("scanCrabButton");
        scanCrabButton->setFont(font5);

        horizontalLayout->addWidget(scanCrabButton);

        lcdNumber_5 = new QLCDNumber(frame_5);
        lcdNumber_5->setObjectName("lcdNumber_5");

        horizontalLayout->addWidget(lcdNumber_5);


        gridLayout_2->addWidget(frame_5, 3, 0, 1, 2);

        homePageButton = new QToolButton(cameraPage);
        homePageButton->setObjectName("homePageButton");
        homePageButton->setMinimumSize(QSize(40, 30));
        homePageButton->setMaximumSize(QSize(40, 30));
        homePageButton->setFont(font5);
        homePageButton->setPopupMode(QToolButton::ToolButtonPopupMode::DelayedPopup);
        homePageButton->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonFollowStyle);
        homePageButton->setAutoRaise(true);
        homePageButton->setArrowType(Qt::ArrowType::LeftArrow);

        gridLayout_2->addWidget(homePageButton, 0, 0, 1, 1);

        stackedWidget->addWidget(cameraPage);
        modelingPage = new QWidget();
        modelingPage->setObjectName("modelingPage");
        homePageButton_2 = new QToolButton(modelingPage);
        homePageButton_2->setObjectName("homePageButton_2");
        homePageButton_2->setGeometry(QRect(0, 0, 40, 30));
        homePageButton_2->setMinimumSize(QSize(40, 30));
        homePageButton_2->setMaximumSize(QSize(40, 30));
        homePageButton_2->setFont(font5);
        homePageButton_2->setPopupMode(QToolButton::ToolButtonPopupMode::DelayedPopup);
        homePageButton_2->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonFollowStyle);
        homePageButton_2->setAutoRaise(true);
        homePageButton_2->setArrowType(Qt::ArrowType::LeftArrow);
        stackedWidget->addWidget(modelingPage);
        icebergPage = new QWidget();
        icebergPage->setObjectName("icebergPage");
        homePageButton_3 = new QToolButton(icebergPage);
        homePageButton_3->setObjectName("homePageButton_3");
        homePageButton_3->setGeometry(QRect(0, 0, 40, 30));
        homePageButton_3->setMinimumSize(QSize(40, 30));
        homePageButton_3->setMaximumSize(QSize(40, 30));
        homePageButton_3->setFont(font5);
        homePageButton_3->setPopupMode(QToolButton::ToolButtonPopupMode::DelayedPopup);
        homePageButton_3->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonFollowStyle);
        homePageButton_3->setAutoRaise(true);
        homePageButton_3->setArrowType(Qt::ArrowType::LeftArrow);
        stackedWidget->addWidget(icebergPage);
        ednaPage = new QWidget();
        ednaPage->setObjectName("ednaPage");
        gridLayout_4 = new QGridLayout(ednaPage);
        gridLayout_4->setObjectName("gridLayout_4");
        label_11 = new QLabel(ednaPage);
        label_11->setObjectName("label_11");
        label_11->setFont(font5);
        label_11->setFrameShape(QFrame::Shape::Box);

        gridLayout_4->addWidget(label_11, 5, 4, 1, 1);

        spinBoxRock = new QSpinBox(ednaPage);
        spinBoxRock->setObjectName("spinBoxRock");

        gridLayout_4->addWidget(spinBoxRock, 5, 2, 1, 1);

        spinBoxSnow = new QSpinBox(ednaPage);
        spinBoxSnow->setObjectName("spinBoxSnow");

        gridLayout_4->addWidget(spinBoxSnow, 1, 2, 1, 1);

        label_8 = new QLabel(ednaPage);
        label_8->setObjectName("label_8");
        label_8->setFont(font5);
        label_8->setFrameShape(QFrame::Shape::Box);

        gridLayout_4->addWidget(label_8, 3, 4, 1, 1);

        spinBoxJonah = new QSpinBox(ednaPage);
        spinBoxJonah->setObjectName("spinBoxJonah");

        gridLayout_4->addWidget(spinBoxJonah, 1, 5, 1, 1);

        label_4 = new QLabel(ednaPage);
        label_4->setObjectName("label_4");
        label_4->setFont(font5);
        label_4->setFrameShape(QFrame::Shape::Box);

        gridLayout_4->addWidget(label_4, 4, 1, 1, 1);

        spinBoxSunstar = new QSpinBox(ednaPage);
        spinBoxSunstar->setObjectName("spinBoxSunstar");

        gridLayout_4->addWidget(spinBoxSunstar, 2, 5, 1, 1);

        hairyCrabPercent = new QLCDNumber(ednaPage);
        hairyCrabPercent->setObjectName("hairyCrabPercent");
        hairyCrabPercent->setFrameShadow(QFrame::Shadow::Plain);
        hairyCrabPercent->setSmallDecimalPoint(true);
        hairyCrabPercent->setSegmentStyle(QLCDNumber::SegmentStyle::Flat);

        gridLayout_4->addWidget(hairyCrabPercent, 3, 3, 1, 1);

        label_3 = new QLabel(ednaPage);
        label_3->setObjectName("label_3");
        label_3->setFont(font5);
        label_3->setFrameShape(QFrame::Shape::Box);

        gridLayout_4->addWidget(label_3, 3, 1, 1, 1);

        label = new QLabel(ednaPage);
        label->setObjectName("label");
        label->setFont(font5);
        label->setFrameShape(QFrame::Shape::Box);

        gridLayout_4->addWidget(label, 1, 4, 1, 1);

        label_12 = new QLabel(ednaPage);
        label_12->setObjectName("label_12");
        QFont font6;
        font6.setFamilies({QString::fromUtf8("Comic Sans MS")});
        font6.setPointSize(30);
        font6.setBold(false);
        font6.setItalic(true);
        font6.setUnderline(false);
        label_12->setFont(font6);
        label_12->setFrameShape(QFrame::Shape::NoFrame);

        gridLayout_4->addWidget(label_12, 0, 1, 1, 1, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignTop);

        snowCrabPercent = new QLCDNumber(ednaPage);
        snowCrabPercent->setObjectName("snowCrabPercent");
        snowCrabPercent->setFrameShadow(QFrame::Shadow::Plain);
        snowCrabPercent->setSmallDecimalPoint(true);
        snowCrabPercent->setMode(QLCDNumber::Mode::Dec);
        snowCrabPercent->setSegmentStyle(QLCDNumber::SegmentStyle::Flat);
        snowCrabPercent->setProperty("value", QVariant(10.500000000000000));

        gridLayout_4->addWidget(snowCrabPercent, 1, 3, 1, 1);

        homePageButton_4 = new QToolButton(ednaPage);
        homePageButton_4->setObjectName("homePageButton_4");
        homePageButton_4->setMinimumSize(QSize(40, 30));
        homePageButton_4->setMaximumSize(QSize(40, 30));
        homePageButton_4->setFont(font5);
        homePageButton_4->setPopupMode(QToolButton::ToolButtonPopupMode::DelayedPopup);
        homePageButton_4->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonFollowStyle);
        homePageButton_4->setAutoRaise(true);
        homePageButton_4->setArrowType(Qt::ArrowType::LeftArrow);

        gridLayout_4->addWidget(homePageButton_4, 0, 0, 1, 1);

        rockCrabPercent = new QLCDNumber(ednaPage);
        rockCrabPercent->setObjectName("rockCrabPercent");
        rockCrabPercent->setFrameShadow(QFrame::Shadow::Plain);
        rockCrabPercent->setSmallDecimalPoint(true);
        rockCrabPercent->setSegmentStyle(QLCDNumber::SegmentStyle::Flat);

        gridLayout_4->addWidget(rockCrabPercent, 5, 3, 1, 1);

        spinBoxBoreal = new QSpinBox(ednaPage);
        spinBoxBoreal->setObjectName("spinBoxBoreal");

        gridLayout_4->addWidget(spinBoxBoreal, 4, 5, 1, 1);

        brittlePercent = new QLCDNumber(ednaPage);
        brittlePercent->setObjectName("brittlePercent");
        brittlePercent->setFrameShadow(QFrame::Shadow::Plain);
        brittlePercent->setSmallDecimalPoint(true);
        brittlePercent->setSegmentStyle(QLCDNumber::SegmentStyle::Flat);

        gridLayout_4->addWidget(brittlePercent, 5, 6, 1, 1);

        label_10 = new QLabel(ednaPage);
        label_10->setObjectName("label_10");
        label_10->setFont(font5);
        label_10->setFrameShape(QFrame::Shape::Box);

        gridLayout_4->addWidget(label_10, 4, 4, 1, 1);

        label_14 = new QLabel(ednaPage);
        label_14->setObjectName("label_14");
        QFont font7;
        font7.setFamilies({QString::fromUtf8("Comic Sans MS")});
        font7.setPointSize(30);
        label_14->setFont(font7);

        gridLayout_4->addWidget(label_14, 0, 3, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        label_5 = new QLabel(ednaPage);
        label_5->setObjectName("label_5");
        label_5->setFont(font5);
        label_5->setFrameShape(QFrame::Shape::Box);

        gridLayout_4->addWidget(label_5, 5, 1, 1, 1);

        spinBoxWestern = new QSpinBox(ednaPage);
        spinBoxWestern->setObjectName("spinBoxWestern");

        gridLayout_4->addWidget(spinBoxWestern, 3, 2, 1, 1);

        label_13 = new QLabel(ednaPage);
        label_13->setObjectName("label_13");
        label_13->setFont(font7);

        gridLayout_4->addWidget(label_13, 0, 2, 1, 1, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignTop);

        spinBoxGreen = new QSpinBox(ednaPage);
        spinBoxGreen->setObjectName("spinBoxGreen");

        gridLayout_4->addWidget(spinBoxGreen, 3, 5, 1, 1);

        spinBoxAcadian = new QSpinBox(ednaPage);
        spinBoxAcadian->setObjectName("spinBoxAcadian");

        gridLayout_4->addWidget(spinBoxAcadian, 2, 2, 1, 1);

        spinBoxUrchin = new QSpinBox(ednaPage);
        spinBoxUrchin->setObjectName("spinBoxUrchin");

        gridLayout_4->addWidget(spinBoxUrchin, 4, 2, 1, 1);

        label_2 = new QLabel(ednaPage);
        label_2->setObjectName("label_2");
        label_2->setFont(font5);
        label_2->setFrameShape(QFrame::Shape::Box);

        gridLayout_4->addWidget(label_2, 2, 1, 1, 1);

        borealPercent = new QLCDNumber(ednaPage);
        borealPercent->setObjectName("borealPercent");
        borealPercent->setFrameShadow(QFrame::Shadow::Plain);
        borealPercent->setSmallDecimalPoint(true);
        borealPercent->setSegmentStyle(QLCDNumber::SegmentStyle::Flat);

        gridLayout_4->addWidget(borealPercent, 4, 6, 1, 1);

        label_6 = new QLabel(ednaPage);
        label_6->setObjectName("label_6");
        label_6->setFont(font5);
        label_6->setFrameShape(QFrame::Shape::Box);

        gridLayout_4->addWidget(label_6, 1, 1, 1, 1);

        label_7 = new QLabel(ednaPage);
        label_7->setObjectName("label_7");
        label_7->setFont(font5);
        label_7->setFrameShape(QFrame::Shape::Box);

        gridLayout_4->addWidget(label_7, 2, 4, 1, 1);

        greenCrabPercent = new QLCDNumber(ednaPage);
        greenCrabPercent->setObjectName("greenCrabPercent");
        greenCrabPercent->setFrameShadow(QFrame::Shadow::Plain);
        greenCrabPercent->setSmallDecimalPoint(true);
        greenCrabPercent->setSegmentStyle(QLCDNumber::SegmentStyle::Flat);

        gridLayout_4->addWidget(greenCrabPercent, 3, 6, 1, 1);

        sunstarPercent = new QLCDNumber(ednaPage);
        sunstarPercent->setObjectName("sunstarPercent");
        sunstarPercent->setFrameShadow(QFrame::Shadow::Plain);
        sunstarPercent->setSmallDecimalPoint(true);
        sunstarPercent->setSegmentStyle(QLCDNumber::SegmentStyle::Flat);

        gridLayout_4->addWidget(sunstarPercent, 2, 6, 1, 1);

        acadianCrabPercent = new QLCDNumber(ednaPage);
        acadianCrabPercent->setObjectName("acadianCrabPercent");
        acadianCrabPercent->setFrameShadow(QFrame::Shadow::Plain);
        acadianCrabPercent->setSmallDecimalPoint(true);
        acadianCrabPercent->setSegmentStyle(QLCDNumber::SegmentStyle::Flat);

        gridLayout_4->addWidget(acadianCrabPercent, 2, 3, 1, 1);

        jonahCrabPercent = new QLCDNumber(ednaPage);
        jonahCrabPercent->setObjectName("jonahCrabPercent");
        jonahCrabPercent->setFrameShadow(QFrame::Shadow::Plain);
        jonahCrabPercent->setSmallDecimalPoint(true);
        jonahCrabPercent->setSegmentStyle(QLCDNumber::SegmentStyle::Flat);

        gridLayout_4->addWidget(jonahCrabPercent, 1, 6, 1, 1);

        urchinPercent = new QLCDNumber(ednaPage);
        urchinPercent->setObjectName("urchinPercent");
        urchinPercent->setFrameShadow(QFrame::Shadow::Plain);
        urchinPercent->setSmallDecimalPoint(true);
        urchinPercent->setSegmentStyle(QLCDNumber::SegmentStyle::Flat);

        gridLayout_4->addWidget(urchinPercent, 4, 3, 1, 1);

        spinBoxBrittle = new QSpinBox(ednaPage);
        spinBoxBrittle->setObjectName("spinBoxBrittle");

        gridLayout_4->addWidget(spinBoxBrittle, 5, 5, 1, 1);

        pushButtonCalcPercent = new QPushButton(ednaPage);
        pushButtonCalcPercent->setObjectName("pushButtonCalcPercent");
        QFont font8;
        font8.setFamilies({QString::fromUtf8("Comic Sans MS")});
        font8.setPointSize(20);
        pushButtonCalcPercent->setFont(font8);

        gridLayout_4->addWidget(pushButtonCalcPercent, 0, 4, 1, 1);

        stackedWidget->addWidget(ednaPage);
        floatPage = new QWidget();
        floatPage->setObjectName("floatPage");
        homePageButton_5 = new QToolButton(floatPage);
        homePageButton_5->setObjectName("homePageButton_5");
        homePageButton_5->setGeometry(QRect(0, 0, 40, 30));
        homePageButton_5->setMinimumSize(QSize(40, 30));
        homePageButton_5->setMaximumSize(QSize(40, 30));
        homePageButton_5->setFont(font5);
        homePageButton_5->setPopupMode(QToolButton::ToolButtonPopupMode::DelayedPopup);
        homePageButton_5->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonFollowStyle);
        homePageButton_5->setAutoRaise(true);
        homePageButton_5->setArrowType(Qt::ArrowType::LeftArrow);
        stackedWidget->addWidget(floatPage);
        settingsPage = new QWidget();
        settingsPage->setObjectName("settingsPage");
        homePageButton_6 = new QToolButton(settingsPage);
        homePageButton_6->setObjectName("homePageButton_6");
        homePageButton_6->setGeometry(QRect(0, 0, 40, 30));
        homePageButton_6->setMinimumSize(QSize(40, 30));
        homePageButton_6->setMaximumSize(QSize(40, 30));
        homePageButton_6->setFont(font5);
        homePageButton_6->setPopupMode(QToolButton::ToolButtonPopupMode::DelayedPopup);
        homePageButton_6->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonFollowStyle);
        homePageButton_6->setAutoRaise(true);
        homePageButton_6->setArrowType(Qt::ArrowType::LeftArrow);
        stackedWidget->addWidget(settingsPage);

        verticalLayout_2->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 839, 30));
        menubar->setDefaultUp(true);
        MainWindow->setMenuBar(menubar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolBar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(4);
        comboBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainTab", nullptr));
        closeProgramButton->setText(QCoreApplication::translate("MainWindow", "Close Program", nullptr));
        icebergPushButton->setText(QCoreApplication::translate("MainWindow", "Iceberg Data Analysis", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "MATE ROV 2026", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Settings", nullptr));
        modelingPushButton->setText(QCoreApplication::translate("MainWindow", "3D Modeling", nullptr));
        cameraFeedPushButton->setText(QCoreApplication::translate("MainWindow", "Camera Feed / Image Recon", nullptr));
        floatPushButton->setText(QCoreApplication::translate("MainWindow", "Float", nullptr));
        ednaPushButton->setText(QCoreApplication::translate("MainWindow", "eDNA Sample Analysis", nullptr));
        botCamButton->setText(QCoreApplication::translate("MainWindow", "Bottom", nullptr));
        frontCamButton->setText(QCoreApplication::translate("MainWindow", "Front", nullptr));
        backCamButton->setText(QCoreApplication::translate("MainWindow", "Back", nullptr));
        leftCamButton->setText(QCoreApplication::translate("MainWindow", "Left", nullptr));
        rightCamButton->setText(QCoreApplication::translate("MainWindow", "Right", nullptr));
        camName->setText(QCoreApplication::translate("MainWindow", "Camera :  PlaceHolder", nullptr));
        latencyLabel->setText(QCoreApplication::translate("MainWindow", "Latency: 0ms", nullptr));
        timeLabel->setText(QCoreApplication::translate("MainWindow", "Current Time", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "European Green Crab", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Native Rock Crab", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "Native Jonah Crab", nullptr));

        comboBox->setCurrentText(QCoreApplication::translate("MainWindow", "European Green Crab", nullptr));
        scanCrabButton->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        homePageButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        homePageButton_2->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        homePageButton_3->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Daisy Brittle Star", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "European Green Crab", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Sea Urchin", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Western Atlantic Hairy Hermit Crab", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Jonah Crab", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Species Name", nullptr));
        homePageButton_4->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Boreal Sea Star", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "%", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Rock Crab", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "#", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Acadian Hermit Crab", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Snow Crab", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Spiny Sunstar", nullptr));
        pushButtonCalcPercent->setText(QCoreApplication::translate("MainWindow", "Calculate Percentage", nullptr));
        homePageButton_5->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        homePageButton_6->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
