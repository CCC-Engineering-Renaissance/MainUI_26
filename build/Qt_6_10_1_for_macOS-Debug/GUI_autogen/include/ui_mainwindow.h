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
    QLabel *label_8;
    QFrame *frame;
    QLCDNumber *lcdNumber;
    QLabel *label_2;
    QFrame *frame_2;
    QLCDNumber *lcdNumber_2;
    QLabel *label_3;
    QLabel *label_7;
    QFrame *frame_3;
    QLCDNumber *lcdNumber_3;
    QLabel *label_5;
    QLabel *label_6;
    QFrame *frame_4;
    QLCDNumber *lcdNumber_4;
    QLabel *label_4;
    QLabel *label;
    QToolButton *homePageButton_4;
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
        label_8 = new QLabel(ednaPage);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 170, 111, 61));
        QFont font6;
        font6.setFamilies({QString::fromUtf8("Comic Sans MS")});
        font6.setPointSize(20);
        font6.setBold(true);
        label_8->setFont(font6);
        frame = new QFrame(ednaPage);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(140, 160, 120, 80));
        frame->setFrameShape(QFrame::Shape::WinPanel);
        frame->setFrameShadow(QFrame::Shadow::Plain);
        frame->setLineWidth(1);
        lcdNumber = new QLCDNumber(frame);
        lcdNumber->setObjectName("lcdNumber");
        lcdNumber->setGeometry(QRect(-80, 10, 161, 61));
        lcdNumber->setFrameShape(QFrame::Shape::NoFrame);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(80, 10, 58, 61));
        QFont font7;
        font7.setFamilies({QString::fromUtf8("Comic Sans MS")});
        font7.setPointSize(35);
        label_2->setFont(font7);
        frame_2 = new QFrame(ednaPage);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(140, 270, 120, 80));
        frame_2->setFrameShape(QFrame::Shape::WinPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Plain);
        frame_2->setLineWidth(1);
        lcdNumber_2 = new QLCDNumber(frame_2);
        lcdNumber_2->setObjectName("lcdNumber_2");
        lcdNumber_2->setGeometry(QRect(-80, 10, 161, 61));
        lcdNumber_2->setFrameShape(QFrame::Shape::NoFrame);
        label_3 = new QLabel(frame_2);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(80, 10, 58, 61));
        label_3->setFont(font7);
        label_7 = new QLabel(ednaPage);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 280, 111, 61));
        label_7->setFont(font6);
        frame_3 = new QFrame(ednaPage);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(500, 160, 120, 80));
        frame_3->setFrameShape(QFrame::Shape::WinPanel);
        frame_3->setFrameShadow(QFrame::Shadow::Plain);
        frame_3->setLineWidth(1);
        lcdNumber_3 = new QLCDNumber(frame_3);
        lcdNumber_3->setObjectName("lcdNumber_3");
        lcdNumber_3->setGeometry(QRect(-80, 10, 161, 61));
        lcdNumber_3->setFrameShape(QFrame::Shape::NoFrame);
        label_5 = new QLabel(frame_3);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(80, 10, 58, 61));
        label_5->setFont(font7);
        label_6 = new QLabel(ednaPage);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(370, 170, 111, 61));
        label_6->setFont(font6);
        frame_4 = new QFrame(ednaPage);
        frame_4->setObjectName("frame_4");
        frame_4->setGeometry(QRect(500, 270, 120, 80));
        frame_4->setFrameShape(QFrame::Shape::WinPanel);
        frame_4->setFrameShadow(QFrame::Shadow::Plain);
        frame_4->setLineWidth(1);
        lcdNumber_4 = new QLCDNumber(frame_4);
        lcdNumber_4->setObjectName("lcdNumber_4");
        lcdNumber_4->setGeometry(QRect(-80, 10, 161, 61));
        lcdNumber_4->setFrameShape(QFrame::Shape::NoFrame);
        label_4 = new QLabel(frame_4);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(80, 10, 58, 61));
        label_4->setFont(font7);
        label = new QLabel(ednaPage);
        label->setObjectName("label");
        label->setGeometry(QRect(370, 280, 111, 61));
        label->setFont(font6);
        homePageButton_4 = new QToolButton(ednaPage);
        homePageButton_4->setObjectName("homePageButton_4");
        homePageButton_4->setGeometry(QRect(0, 0, 40, 30));
        homePageButton_4->setMinimumSize(QSize(40, 30));
        homePageButton_4->setMaximumSize(QSize(40, 30));
        homePageButton_4->setFont(font5);
        homePageButton_4->setPopupMode(QToolButton::ToolButtonPopupMode::DelayedPopup);
        homePageButton_4->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonFollowStyle);
        homePageButton_4->setAutoRaise(true);
        homePageButton_4->setArrowType(Qt::ArrowType::LeftArrow);
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

        stackedWidget->setCurrentIndex(1);
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
        label_8->setText(QCoreApplication::translate("MainWindow", "Organism 1", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "%", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "%", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Organism 2", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "%", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Organism 3", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "%", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Organism 4", nullptr));
        homePageButton_4->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
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
