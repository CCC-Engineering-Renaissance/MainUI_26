/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
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
    QGridLayout *gridLayout_13;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_22;
    QSpacerItem *horizontalSpacer;
    QPushButton *modelingPushButton;
    QPushButton *icebergPushButton;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *ednaPushButton;
    QLabel *crush_label;
    QPushButton *floatPushButton;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *cameraFeedPushButton;
    QSpacerItem *horizontalSpacer_7;
    QHBoxLayout *horizontalLayout_23;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_31;
    QPushButton *closeProgramButton;
    QSpacerItem *horizontalSpacer_30;
    QWidget *cameraPage;
    QGridLayout *gridLayout_2;
    QToolButton *homePageButton;
    QLabel *camName;
    QFrame *frame_6;
    QHBoxLayout *horizontalLayout_3;
    QLabel *latencyLabel;
    QLabel *timeLabel;
    QFrame *frame_5;
    QGridLayout *gridLayout_3;
    QLabel *label_9;
    QLCDNumber *lcdNumber_3;
    QGraphicsView *graphicsView;
    QFrame *droneMap;
    QGridLayout *gridLayout;
    QPushButton *leftCamButton;
    QPushButton *botCamButton;
    QPushButton *rightCamButton;
    QPushButton *frontCamButton;
    QPushButton *backCamButton;
    QSpacerItem *horizontalSpacer_5;
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

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->setWindowModality(Qt::WindowModality::NonModal);
        MainWindow->resize(1200, 800);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(1200, 800));
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::WeatherStorm));
        MainWindow->setWindowIcon(icon);
        MainWindow->setAnimated(false);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        centralwidget->setAutoFillBackground(false);
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy1);
        stackedWidget->setMinimumSize(QSize(900, 600));
        stackedWidget->setMaximumSize(QSize(1600, 1000));
        QFont font;
        font.setPointSize(20);
        stackedWidget->setFont(font);
        stackedWidget->setStyleSheet(QString::fromUtf8("#stackedWidget{\n"
"	border-image: url(:/images/images/bubbles_and_animals.png);\n"
"}\n"
"\n"
""));
        stackedWidget->setFrameShape(QFrame::Shape::Box);
        stackedWidget->setLineWidth(2);
        mainMenu = new QWidget();
        mainMenu->setObjectName("mainMenu");
        mainMenu->setStyleSheet(QString::fromUtf8("#mainMenu {\n"
"	\n"
"	border-image: url(:/images/images/bubbles_and_animals.png);\n"
"}"));
        gridLayout_13 = new QGridLayout(mainMenu);
        gridLayout_13->setObjectName("gridLayout_13");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setSpacing(70);
        horizontalLayout_22->setObjectName("horizontalLayout_22");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_22->addItem(horizontalSpacer);

        modelingPushButton = new QPushButton(mainMenu);
        modelingPushButton->setObjectName("modelingPushButton");
        sizePolicy1.setHeightForWidth(modelingPushButton->sizePolicy().hasHeightForWidth());
        modelingPushButton->setSizePolicy(sizePolicy1);
        modelingPushButton->setMinimumSize(QSize(250, 250));
        modelingPushButton->setMaximumSize(QSize(250, 250));
        modelingPushButton->setBaseSize(QSize(250, 250));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Aileron")});
        font1.setPointSize(25);
        modelingPushButton->setFont(font1);
        modelingPushButton->setAutoFillBackground(false);
        modelingPushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(44,181,222); /* A nice green color */\n"
"    color: rgb(255, 255, 255);             \n"
"    border-radius: 125px;       /* This curves the corners! */\n"
"    padding: 5px;              /* Gives the text some breathing room */\n"
"	border: 5px solid white;	\n"
"	border-color: rgb(152, 199, 65);\n"
"}\n"
""));
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::CameraVideo));
        modelingPushButton->setIcon(icon1);

        horizontalLayout_22->addWidget(modelingPushButton);

        icebergPushButton = new QPushButton(mainMenu);
        icebergPushButton->setObjectName("icebergPushButton");
        sizePolicy1.setHeightForWidth(icebergPushButton->sizePolicy().hasHeightForWidth());
        icebergPushButton->setSizePolicy(sizePolicy1);
        icebergPushButton->setMinimumSize(QSize(250, 250));
        icebergPushButton->setMaximumSize(QSize(250, 250));
        icebergPushButton->setBaseSize(QSize(220, 100));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Aileron")});
        font2.setPointSize(25);
        font2.setBold(false);
        font2.setItalic(false);
        icebergPushButton->setFont(font2);
        icebergPushButton->setAutoFillBackground(false);
        icebergPushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(44,181,222); /* A nice green color */\n"
"    color: rgb(255, 255, 255);             \n"
"    border-radius: 125px;       /* This curves the corners! */\n"
"    padding: 5px;              /* Gives the text some breathing room */\n"
"	border: 5px solid white;	\n"
"	border-color: rgb(152, 199, 65);\n"
"}\n"
""));
        QIcon icon2(QIcon::fromTheme(QIcon::ThemeIcon::SystemSearch));
        icebergPushButton->setIcon(icon2);

        horizontalLayout_22->addWidget(icebergPushButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_22->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_22);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(50);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);

        ednaPushButton = new QPushButton(mainMenu);
        ednaPushButton->setObjectName("ednaPushButton");
        sizePolicy1.setHeightForWidth(ednaPushButton->sizePolicy().hasHeightForWidth());
        ednaPushButton->setSizePolicy(sizePolicy1);
        ednaPushButton->setMinimumSize(QSize(250, 250));
        ednaPushButton->setMaximumSize(QSize(250, 250));
        ednaPushButton->setBaseSize(QSize(220, 100));
        ednaPushButton->setFont(font1);
        ednaPushButton->setAutoFillBackground(false);
        ednaPushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(44,181,222); /* A nice green color */\n"
"    color: rgb(255, 255, 255);             \n"
"    border-radius: 125px;       /* This curves the corners! */\n"
"    padding: 5px;              /* Gives the text some breathing room */\n"
"	border: 5px solid white;	\n"
"	border-color: rgb(152, 199, 65);\n"
"}\n"
""));
        QIcon icon3(QIcon::fromTheme(QIcon::ThemeIcon::MediaFlash));
        ednaPushButton->setIcon(icon3);

        horizontalLayout_5->addWidget(ednaPushButton);

        crush_label = new QLabel(mainMenu);
        crush_label->setObjectName("crush_label");
        sizePolicy1.setHeightForWidth(crush_label->sizePolicy().hasHeightForWidth());
        crush_label->setSizePolicy(sizePolicy1);
        crush_label->setMinimumSize(QSize(250, 250));
        crush_label->setMaximumSize(QSize(250, 250));
        crush_label->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border: none;"));

        horizontalLayout_5->addWidget(crush_label);

        floatPushButton = new QPushButton(mainMenu);
        floatPushButton->setObjectName("floatPushButton");
        sizePolicy1.setHeightForWidth(floatPushButton->sizePolicy().hasHeightForWidth());
        floatPushButton->setSizePolicy(sizePolicy1);
        floatPushButton->setMinimumSize(QSize(250, 250));
        floatPushButton->setMaximumSize(QSize(250, 250));
        floatPushButton->setBaseSize(QSize(220, 100));
        floatPushButton->setFont(font2);
        floatPushButton->setAutoFillBackground(false);
        floatPushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(44,181,222); /* A nice green color */\n"
"    color: rgb(255, 255, 255);             \n"
"    border-radius: 125px;       /* This curves the corners! */\n"
"    padding: 5px;              /* Gives the text some breathing room */\n"
"	border: 5px solid white;	\n"
"	border-color: rgb(152, 199, 65);\n"
"}\n"
""));
        QIcon icon4(QIcon::fromTheme(QIcon::ThemeIcon::SoftwareUpdateAvailable));
        floatPushButton->setIcon(icon4);

        horizontalLayout_5->addWidget(floatPushButton);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);

        cameraFeedPushButton = new QPushButton(mainMenu);
        cameraFeedPushButton->setObjectName("cameraFeedPushButton");
        sizePolicy1.setHeightForWidth(cameraFeedPushButton->sizePolicy().hasHeightForWidth());
        cameraFeedPushButton->setSizePolicy(sizePolicy1);
        cameraFeedPushButton->setMinimumSize(QSize(250, 250));
        cameraFeedPushButton->setMaximumSize(QSize(250, 250));
        cameraFeedPushButton->setSizeIncrement(QSize(0, 0));
        cameraFeedPushButton->setBaseSize(QSize(250, 250));
        cameraFeedPushButton->setFont(font1);
        cameraFeedPushButton->setAutoFillBackground(false);
        cameraFeedPushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(44,181,222); /* A nice green color */\n"
"    color: rgb(255, 255, 255);             \n"
"    border-radius: 125px;       /* This curves the corners! */\n"
"    padding: 5px;              /* Gives the text some breathing room */\n"
"	border: 5px solid white;	\n"
"	border-color: rgb(152, 199, 65);\n"
"}\n"
""));
        QIcon icon5(QIcon::fromTheme(QIcon::ThemeIcon::MediaRecord));
        cameraFeedPushButton->setIcon(icon5);

        horizontalLayout_4->addWidget(cameraFeedPushButton);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_7);


        verticalLayout->addLayout(horizontalLayout_4);


        gridLayout_13->addLayout(verticalLayout, 0, 0, 1, 1);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setObjectName("horizontalLayout_23");
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_23->addItem(horizontalSpacer_8);

        pushButton = new QPushButton(mainMenu);
        pushButton->setObjectName("pushButton");
        pushButton->setMinimumSize(QSize(100, 100));
        pushButton->setMaximumSize(QSize(100, 100));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Aileron")});
        font3.setPointSize(30);
        font3.setBold(true);
        pushButton->setFont(font3);
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(44,181,222); /* A nice green color */\n"
"    color: rgb(0, 0, 0);              /* White text */\n"
"    border-radius: 10px;       /* This curves the corners! */\n"
"    padding: 5px;              /* Gives the text some breathing room */\n"
"	border: 5px solid white;	\n"
"	border-color: rgb(152, 199, 65);\n"
"}\n"
""));
        QIcon icon6(QIcon::fromTheme(QIcon::ThemeIcon::DocumentProperties));
        pushButton->setIcon(icon6);
        pushButton->setIconSize(QSize(40, 40));

        horizontalLayout_23->addWidget(pushButton);

        horizontalSpacer_31 = new QSpacerItem(1350, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_23->addItem(horizontalSpacer_31);

        closeProgramButton = new QPushButton(mainMenu);
        closeProgramButton->setObjectName("closeProgramButton");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(closeProgramButton->sizePolicy().hasHeightForWidth());
        closeProgramButton->setSizePolicy(sizePolicy2);
        closeProgramButton->setMinimumSize(QSize(100, 100));
        closeProgramButton->setMaximumSize(QSize(100, 100));
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Aileron")});
        font4.setPointSize(30);
        font4.setBold(true);
        font4.setItalic(false);
        font4.setUnderline(false);
        font4.setStrikeOut(false);
        font4.setKerning(true);
        closeProgramButton->setFont(font4);
        closeProgramButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        closeProgramButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(44,181,222); /* A nice green color */\n"
"    color: rgb(0, 0, 0);              /* White text */\n"
"    border-radius: 10px;       /* This curves the corners! */\n"
"    padding: 5px;              /* Gives the text some breathing room */\n"
"	border: 5px solid white;	\n"
"	border-color: rgb(152, 199, 65);\n"
"}\n"
""));
        QIcon icon7(QIcon::fromTheme(QIcon::ThemeIcon::ApplicationExit));
        closeProgramButton->setIcon(icon7);
        closeProgramButton->setIconSize(QSize(50, 50));

        horizontalLayout_23->addWidget(closeProgramButton);

        horizontalSpacer_30 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_23->addItem(horizontalSpacer_30);


        gridLayout_13->addLayout(horizontalLayout_23, 1, 0, 1, 1);

        stackedWidget->addWidget(mainMenu);
        cameraPage = new QWidget();
        cameraPage->setObjectName("cameraPage");
        cameraPage->setStyleSheet(QString::fromUtf8(""));
        gridLayout_2 = new QGridLayout(cameraPage);
        gridLayout_2->setObjectName("gridLayout_2");
        homePageButton = new QToolButton(cameraPage);
        homePageButton->setObjectName("homePageButton");
        homePageButton->setMinimumSize(QSize(40, 30));
        homePageButton->setMaximumSize(QSize(40, 30));
        QFont font5;
        font5.setFamilies({QString::fromUtf8("Comic Sans MS")});
        homePageButton->setFont(font5);
        homePageButton->setPopupMode(QToolButton::ToolButtonPopupMode::DelayedPopup);
        homePageButton->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonFollowStyle);
        homePageButton->setAutoRaise(true);
        homePageButton->setArrowType(Qt::ArrowType::LeftArrow);

        gridLayout_2->addWidget(homePageButton, 0, 0, 1, 1);

        camName = new QLabel(cameraPage);
        camName->setObjectName("camName");
        QFont font6;
        font6.setFamilies({QString::fromUtf8("Aileron")});
        font6.setPointSize(20);
        font6.setBold(false);
        camName->setFont(font6);
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
        QFont font7;
        font7.setFamilies({QString::fromUtf8("Aileron")});
        latencyLabel->setFont(font7);
        latencyLabel->setFrameShape(QFrame::Shape::Box);
        latencyLabel->setFrameShadow(QFrame::Shadow::Plain);

        horizontalLayout_3->addWidget(latencyLabel);

        timeLabel = new QLabel(frame_6);
        timeLabel->setObjectName("timeLabel");
        timeLabel->setFont(font7);
        timeLabel->setFrameShape(QFrame::Shape::Box);

        horizontalLayout_3->addWidget(timeLabel);


        gridLayout_2->addWidget(frame_6, 0, 3, 1, 1);

        frame_5 = new QFrame(cameraPage);
        frame_5->setObjectName("frame_5");
        frame_5->setStyleSheet(QString::fromUtf8(""));
        frame_5->setFrameShape(QFrame::Shape::Box);
        frame_5->setFrameShadow(QFrame::Shadow::Plain);
        frame_5->setLineWidth(4);
        gridLayout_3 = new QGridLayout(frame_5);
        gridLayout_3->setObjectName("gridLayout_3");
        label_9 = new QLabel(frame_5);
        label_9->setObjectName("label_9");
        QFont font8;
        font8.setFamilies({QString::fromUtf8("Aileron")});
        font8.setPointSize(20);
        font8.setItalic(true);
        font8.setUnderline(false);
        label_9->setFont(font8);
        label_9->setFrameShape(QFrame::Shape::Box);

        gridLayout_3->addWidget(label_9, 0, 0, 1, 1, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignTop);

        lcdNumber_3 = new QLCDNumber(frame_5);
        lcdNumber_3->setObjectName("lcdNumber_3");
        lcdNumber_3->setFont(font7);
        lcdNumber_3->setStyleSheet(QString::fromUtf8(""));
        lcdNumber_3->setLineWidth(1);
        lcdNumber_3->setMidLineWidth(2);

        gridLayout_3->addWidget(lcdNumber_3, 1, 0, 1, 1);


        gridLayout_2->addWidget(frame_5, 3, 0, 1, 2);

        graphicsView = new QGraphicsView(cameraPage);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setFrameShape(QFrame::Shape::Box);
        graphicsView->setFrameShadow(QFrame::Shadow::Plain);
        graphicsView->setLineWidth(3);
        graphicsView->setMidLineWidth(0);

        gridLayout_2->addWidget(graphicsView, 1, 0, 1, 4);

        droneMap = new QFrame(cameraPage);
        droneMap->setObjectName("droneMap");
        droneMap->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
        droneMap->setFrameShape(QFrame::Shape::Box);
        droneMap->setFrameShadow(QFrame::Shadow::Plain);
        droneMap->setLineWidth(4);
        gridLayout = new QGridLayout(droneMap);
        gridLayout->setObjectName("gridLayout");
        leftCamButton = new QPushButton(droneMap);
        leftCamButton->setObjectName("leftCamButton");
        QFont font9;
        font9.setFamilies({QString::fromUtf8("Aileron")});
        font9.setPointSize(15);
        leftCamButton->setFont(font9);
        leftCamButton->setStyleSheet(QString::fromUtf8("	background-color: rgb(44,181,222); /* A nice green color */\n"
"	border-width: 4px;\n"
"	border-style: ridge;\n"
"	border-color: rgb(152, 199, 65);\n"
"	selection-color: rgb(255, 255, 255);"));

        gridLayout->addWidget(leftCamButton, 2, 0, 1, 1);

        botCamButton = new QPushButton(droneMap);
        botCamButton->setObjectName("botCamButton");
        botCamButton->setFont(font9);
        botCamButton->setStyleSheet(QString::fromUtf8("	background-color: rgb(44,181,222); /* A nice green color */\n"
"	border-width: 4px;\n"
"	border-style: ridge;\n"
"	border-color: rgb(152, 199, 65);\n"
"	selection-color: rgb(255, 255, 255);"));

        gridLayout->addWidget(botCamButton, 2, 1, 1, 1);

        rightCamButton = new QPushButton(droneMap);
        rightCamButton->setObjectName("rightCamButton");
        rightCamButton->setFont(font9);
        rightCamButton->setStyleSheet(QString::fromUtf8("	background-color: rgb(44,181,222); /* A nice green color */\n"
"	border-width: 4px;\n"
"	border-style: ridge;\n"
"	border-color: rgb(152, 199, 65);\n"
"	selection-color: rgb(255, 255, 255);"));

        gridLayout->addWidget(rightCamButton, 2, 2, 1, 1);

        frontCamButton = new QPushButton(droneMap);
        frontCamButton->setObjectName("frontCamButton");
        frontCamButton->setFont(font9);
        frontCamButton->setStyleSheet(QString::fromUtf8("	background-color: rgb(44,181,222); /* A nice green color */\n"
"	border-width: 4px;\n"
"	border-style: ridge;\n"
"	border-color: rgb(152, 199, 65);\n"
"	selection-color: rgb(255, 255, 255);"));

        gridLayout->addWidget(frontCamButton, 0, 1, 1, 1);

        backCamButton = new QPushButton(droneMap);
        backCamButton->setObjectName("backCamButton");
        backCamButton->setFont(font9);
        backCamButton->setStyleSheet(QString::fromUtf8("	background-color: rgb(44,181,222); /* A nice green color */\n"
"	border-width: 4px;\n"
"	border-style: ridge;\n"
"	border-color: rgb(152, 199, 65);\n"
"	selection-color: rgb(255, 255, 255);"));

        gridLayout->addWidget(backCamButton, 3, 1, 1, 1);


        gridLayout_2->addWidget(droneMap, 3, 3, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_5, 3, 2, 1, 1);

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
        ednaPage->setStyleSheet(QString::fromUtf8("#ednaPage{\n"
"	border-image: url(:/images/images/bubbles_and_animals.png);\n"
"}"));
        gridLayout_4 = new QGridLayout(ednaPage);
        gridLayout_4->setObjectName("gridLayout_4");
        label_11 = new QLabel(ednaPage);
        label_11->setObjectName("label_11");
        QFont font10;
        font10.setFamilies({QString::fromUtf8("Comic Sans MS")});
        font10.setPointSize(20);
        label_11->setFont(font10);
        label_11->setFrameShape(QFrame::Shape::Box);

        gridLayout_4->addWidget(label_11, 5, 4, 1, 1);

        spinBoxRock = new QSpinBox(ednaPage);
        spinBoxRock->setObjectName("spinBoxRock");
        spinBoxRock->setFont(font);

        gridLayout_4->addWidget(spinBoxRock, 5, 2, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        spinBoxSnow = new QSpinBox(ednaPage);
        spinBoxSnow->setObjectName("spinBoxSnow");
        spinBoxSnow->setFont(font);

        gridLayout_4->addWidget(spinBoxSnow, 1, 2, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        label_8 = new QLabel(ednaPage);
        label_8->setObjectName("label_8");
        label_8->setFont(font10);
        label_8->setFrameShape(QFrame::Shape::Box);

        gridLayout_4->addWidget(label_8, 3, 4, 1, 1);

        spinBoxJonah = new QSpinBox(ednaPage);
        spinBoxJonah->setObjectName("spinBoxJonah");
        spinBoxJonah->setFont(font);

        gridLayout_4->addWidget(spinBoxJonah, 1, 5, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        label_4 = new QLabel(ednaPage);
        label_4->setObjectName("label_4");
        label_4->setFont(font10);
        label_4->setFrameShape(QFrame::Shape::Box);

        gridLayout_4->addWidget(label_4, 4, 1, 1, 1);

        spinBoxSunstar = new QSpinBox(ednaPage);
        spinBoxSunstar->setObjectName("spinBoxSunstar");
        spinBoxSunstar->setFont(font);

        gridLayout_4->addWidget(spinBoxSunstar, 2, 5, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        hairyCrabPercent = new QLCDNumber(ednaPage);
        hairyCrabPercent->setObjectName("hairyCrabPercent");
        hairyCrabPercent->setFont(font);
        hairyCrabPercent->setFrameShadow(QFrame::Shadow::Plain);
        hairyCrabPercent->setSmallDecimalPoint(true);
        hairyCrabPercent->setSegmentStyle(QLCDNumber::SegmentStyle::Flat);

        gridLayout_4->addWidget(hairyCrabPercent, 3, 3, 1, 1);

        label_3 = new QLabel(ednaPage);
        label_3->setObjectName("label_3");
        label_3->setFont(font10);
        label_3->setFrameShape(QFrame::Shape::Box);

        gridLayout_4->addWidget(label_3, 3, 1, 1, 1);

        label = new QLabel(ednaPage);
        label->setObjectName("label");
        label->setFont(font10);
        label->setFrameShape(QFrame::Shape::Box);

        gridLayout_4->addWidget(label, 1, 4, 1, 1);

        label_12 = new QLabel(ednaPage);
        label_12->setObjectName("label_12");
        label_12->setFrameShape(QFrame::Shape::NoFrame);

        gridLayout_4->addWidget(label_12, 0, 1, 1, 1, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignTop);

        snowCrabPercent = new QLCDNumber(ednaPage);
        snowCrabPercent->setObjectName("snowCrabPercent");
        snowCrabPercent->setFont(font);
        snowCrabPercent->setFrameShadow(QFrame::Shadow::Plain);
        snowCrabPercent->setSmallDecimalPoint(true);
        snowCrabPercent->setMode(QLCDNumber::Mode::Dec);
        snowCrabPercent->setSegmentStyle(QLCDNumber::SegmentStyle::Flat);

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
        rockCrabPercent->setFont(font);
        rockCrabPercent->setFrameShadow(QFrame::Shadow::Plain);
        rockCrabPercent->setSmallDecimalPoint(true);
        rockCrabPercent->setSegmentStyle(QLCDNumber::SegmentStyle::Flat);

        gridLayout_4->addWidget(rockCrabPercent, 5, 3, 1, 1);

        spinBoxBoreal = new QSpinBox(ednaPage);
        spinBoxBoreal->setObjectName("spinBoxBoreal");
        spinBoxBoreal->setFont(font);

        gridLayout_4->addWidget(spinBoxBoreal, 4, 5, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        brittlePercent = new QLCDNumber(ednaPage);
        brittlePercent->setObjectName("brittlePercent");
        brittlePercent->setFont(font);
        brittlePercent->setFrameShadow(QFrame::Shadow::Plain);
        brittlePercent->setSmallDecimalPoint(true);
        brittlePercent->setSegmentStyle(QLCDNumber::SegmentStyle::Flat);

        gridLayout_4->addWidget(brittlePercent, 5, 6, 1, 1);

        label_10 = new QLabel(ednaPage);
        label_10->setObjectName("label_10");
        label_10->setFont(font10);
        label_10->setFrameShape(QFrame::Shape::Box);

        gridLayout_4->addWidget(label_10, 4, 4, 1, 1);

        label_14 = new QLabel(ednaPage);
        label_14->setObjectName("label_14");
        QFont font11;
        font11.setFamilies({QString::fromUtf8("Comic Sans MS")});
        font11.setPointSize(30);
        label_14->setFont(font11);

        gridLayout_4->addWidget(label_14, 0, 3, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        label_5 = new QLabel(ednaPage);
        label_5->setObjectName("label_5");
        label_5->setFont(font10);
        label_5->setFrameShape(QFrame::Shape::Box);

        gridLayout_4->addWidget(label_5, 5, 1, 1, 1);

        spinBoxWestern = new QSpinBox(ednaPage);
        spinBoxWestern->setObjectName("spinBoxWestern");
        spinBoxWestern->setFont(font);

        gridLayout_4->addWidget(spinBoxWestern, 3, 2, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        label_13 = new QLabel(ednaPage);
        label_13->setObjectName("label_13");
        label_13->setFont(font11);

        gridLayout_4->addWidget(label_13, 0, 2, 1, 1, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignTop);

        spinBoxGreen = new QSpinBox(ednaPage);
        spinBoxGreen->setObjectName("spinBoxGreen");
        spinBoxGreen->setFont(font);

        gridLayout_4->addWidget(spinBoxGreen, 3, 5, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        spinBoxAcadian = new QSpinBox(ednaPage);
        spinBoxAcadian->setObjectName("spinBoxAcadian");
        spinBoxAcadian->setFont(font);

        gridLayout_4->addWidget(spinBoxAcadian, 2, 2, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        spinBoxUrchin = new QSpinBox(ednaPage);
        spinBoxUrchin->setObjectName("spinBoxUrchin");
        spinBoxUrchin->setFont(font);

        gridLayout_4->addWidget(spinBoxUrchin, 4, 2, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        label_2 = new QLabel(ednaPage);
        label_2->setObjectName("label_2");
        label_2->setFont(font10);
        label_2->setFrameShape(QFrame::Shape::Box);

        gridLayout_4->addWidget(label_2, 2, 1, 1, 1);

        borealPercent = new QLCDNumber(ednaPage);
        borealPercent->setObjectName("borealPercent");
        borealPercent->setFont(font);
        borealPercent->setFrameShadow(QFrame::Shadow::Plain);
        borealPercent->setSmallDecimalPoint(true);
        borealPercent->setSegmentStyle(QLCDNumber::SegmentStyle::Flat);

        gridLayout_4->addWidget(borealPercent, 4, 6, 1, 1);

        label_6 = new QLabel(ednaPage);
        label_6->setObjectName("label_6");
        label_6->setFont(font10);
        label_6->setFrameShape(QFrame::Shape::Box);

        gridLayout_4->addWidget(label_6, 1, 1, 1, 1);

        label_7 = new QLabel(ednaPage);
        label_7->setObjectName("label_7");
        label_7->setFont(font10);
        label_7->setFrameShape(QFrame::Shape::Box);

        gridLayout_4->addWidget(label_7, 2, 4, 1, 1);

        greenCrabPercent = new QLCDNumber(ednaPage);
        greenCrabPercent->setObjectName("greenCrabPercent");
        greenCrabPercent->setFont(font);
        greenCrabPercent->setFrameShadow(QFrame::Shadow::Plain);
        greenCrabPercent->setSmallDecimalPoint(true);
        greenCrabPercent->setSegmentStyle(QLCDNumber::SegmentStyle::Flat);

        gridLayout_4->addWidget(greenCrabPercent, 3, 6, 1, 1);

        sunstarPercent = new QLCDNumber(ednaPage);
        sunstarPercent->setObjectName("sunstarPercent");
        sunstarPercent->setFont(font);
        sunstarPercent->setFrameShadow(QFrame::Shadow::Plain);
        sunstarPercent->setSmallDecimalPoint(true);
        sunstarPercent->setSegmentStyle(QLCDNumber::SegmentStyle::Flat);

        gridLayout_4->addWidget(sunstarPercent, 2, 6, 1, 1);

        acadianCrabPercent = new QLCDNumber(ednaPage);
        acadianCrabPercent->setObjectName("acadianCrabPercent");
        acadianCrabPercent->setFont(font);
        acadianCrabPercent->setFrameShadow(QFrame::Shadow::Plain);
        acadianCrabPercent->setSmallDecimalPoint(true);
        acadianCrabPercent->setSegmentStyle(QLCDNumber::SegmentStyle::Flat);

        gridLayout_4->addWidget(acadianCrabPercent, 2, 3, 1, 1);

        jonahCrabPercent = new QLCDNumber(ednaPage);
        jonahCrabPercent->setObjectName("jonahCrabPercent");
        jonahCrabPercent->setFont(font);
        jonahCrabPercent->setFrameShadow(QFrame::Shadow::Plain);
        jonahCrabPercent->setSmallDecimalPoint(true);
        jonahCrabPercent->setSegmentStyle(QLCDNumber::SegmentStyle::Flat);

        gridLayout_4->addWidget(jonahCrabPercent, 1, 6, 1, 1);

        urchinPercent = new QLCDNumber(ednaPage);
        urchinPercent->setObjectName("urchinPercent");
        urchinPercent->setFont(font);
        urchinPercent->setFrameShadow(QFrame::Shadow::Plain);
        urchinPercent->setSmallDecimalPoint(true);
        urchinPercent->setSegmentStyle(QLCDNumber::SegmentStyle::Flat);

        gridLayout_4->addWidget(urchinPercent, 4, 3, 1, 1);

        spinBoxBrittle = new QSpinBox(ednaPage);
        spinBoxBrittle->setObjectName("spinBoxBrittle");
        spinBoxBrittle->setFont(font);

        gridLayout_4->addWidget(spinBoxBrittle, 5, 5, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        pushButtonCalcPercent = new QPushButton(ednaPage);
        pushButtonCalcPercent->setObjectName("pushButtonCalcPercent");
        pushButtonCalcPercent->setFont(font10);

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

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainTab", nullptr));
        modelingPushButton->setText(QCoreApplication::translate("MainWindow", "3D Modeling", nullptr));
        icebergPushButton->setText(QCoreApplication::translate("MainWindow", "Iceberg Data", nullptr));
        ednaPushButton->setText(QCoreApplication::translate("MainWindow", "eDNA", nullptr));
        crush_label->setText(QString());
        floatPushButton->setText(QCoreApplication::translate("MainWindow", "Float", nullptr));
        cameraFeedPushButton->setText(QCoreApplication::translate("MainWindow", "Video Feed", nullptr));
        pushButton->setText(QString());
        closeProgramButton->setText(QString());
        homePageButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        camName->setText(QCoreApplication::translate("MainWindow", "Camera :  PlaceHolder", nullptr));
        latencyLabel->setText(QCoreApplication::translate("MainWindow", "Latency: 0ms", nullptr));
        timeLabel->setText(QCoreApplication::translate("MainWindow", "Current Time", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "European Green Crab Count", nullptr));
        leftCamButton->setText(QCoreApplication::translate("MainWindow", "Left", nullptr));
        botCamButton->setText(QCoreApplication::translate("MainWindow", "Bottom", nullptr));
        rightCamButton->setText(QCoreApplication::translate("MainWindow", "Right", nullptr));
        frontCamButton->setText(QCoreApplication::translate("MainWindow", "Front", nullptr));
        backCamButton->setText(QCoreApplication::translate("MainWindow", "Back", nullptr));
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
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
