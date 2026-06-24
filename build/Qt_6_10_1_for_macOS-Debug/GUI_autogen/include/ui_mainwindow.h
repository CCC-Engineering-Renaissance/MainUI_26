/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCharts/QChartView>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "modelviewer.h"

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
    QFrame *frame_6;
    QHBoxLayout *horizontalLayout_3;
    QLabel *captureCountLabel;
    QLabel *latencyLabel;
    QLabel *timeLabel;
    QLabel *alsStatusLabel;
    QFrame *frame_5;
    QGridLayout *gridLayout_3;
    QLabel *label_9;
    QLCDNumber *lcdNumber_3;
    QGraphicsView *graphicsView;
    QLabel *camName;
    QFrame *droneMap;
    QGridLayout *gridLayout;
    QPushButton *leftCamButton;
    QPushButton *botCamButton;
    QPushButton *rightCamButton;
    QPushButton *frontCamButton;
    QPushButton *backCamButton;
    QFrame *frame;
    QGridLayout *gridLayout_5;
    QLCDNumber *lcdNumber;
    QLabel *label_15;
    QPushButton *pushButton_2;
    QPushButton *captureFramesButton;
    QToolButton *homePageButton;
    QPushButton *modeButton;
    QWidget *modelingPage;
    QVBoxLayout *modelingPageLayout;
    QHBoxLayout *modelingTopRow;
    QToolButton *homePageButton_2;
    QLabel *statusLabel;
    QHBoxLayout *buttonLayout;
    QPushButton *importImagesButton;
    QPushButton *importVideoButton;
    QPushButton *clearButton;
    QCheckBox *denseCheckBox;
    QSpacerItem *photogrammetryHorizontalSpacer;
    QPushButton *scaleButton;
    QPushButton *measureButton;
    QPushButton *loadPlyButton;
    QPushButton *resetCameraButton;
    QPushButton *runButton;
    QPushButton *cancelButton;
    QProgressBar *progressBar;
    QSplitter *mainSplitter;
    QListWidget *imageList;
    QSplitter *rightSplitter;
    ModelViewer *viewer;
    QTextEdit *logOutput;
    QWidget *icebergPage;
    QGridLayout *gridLayout_6;
    QToolButton *homePageButton_3;
    QLabel *labelIcebergTitle;
    QVBoxLayout *icebergLeftColumn;
    QGroupBox *groupPerimeterSurvey;
    QGridLayout *gridPerimeterSurvey;
    QLabel *labelSurveyPrompt;
    QLabel *labelSurvey1;
    QLineEdit *lineSurveyNumber1;
    QLabel *labelSurvey2;
    QLineEdit *lineSurveyNumber2;
    QLabel *labelSurvey3;
    QLineEdit *lineSurveyNumber3;
    QLabel *labelSurvey4;
    QLineEdit *lineSurveyNumber4;
    QLabel *labelSurvey5;
    QLineEdit *lineSurveyNumber5;
    QGroupBox *groupKeelMeasurement;
    QGridLayout *gridKeelMeasurement;
    QLabel *labelLiveDepth;
    QLCDNumber *lcdLiveDepth;
    QPushButton *btnRecordDepth;
    QLabel *labelFinalKeel;
    QDoubleSpinBox *spinFinalKeelDepth;
    QGroupBox *groupIcebergInfo;
    QFormLayout *formIcebergInfo;
    QLabel *labelIcebergLatitude;
    QDoubleSpinBox *spinIcebergLatitude;
    QLabel *labelIcebergLongitude;
    QDoubleSpinBox *spinIcebergLongitude;
    QLabel *labelIcebergHeading;
    QDoubleSpinBox *spinIcebergHeading;
    QGroupBox *groupTrackMap;
    QVBoxLayout *verticalLayoutTrackMap;
    QGraphicsView *tacticalview;
    QTableWidget *tablePlatformThreats;
    QGroupBox *groupJudgeSummary;
    QVBoxLayout *verticalLayoutJudgeSummary;
    QPlainTextEdit *txtJudgeSummary;
    QWidget *ednaPage;
    QGridLayout *gridLayout_4;
    QSpinBox *spinBoxRock;
    QLCDNumber *borealPercent;
    QSpinBox *spinBoxUrchin;
    QLabel *label_10;
    QLCDNumber *rockCrabPercent;
    QSpinBox *spinBoxSnow;
    QLCDNumber *jonahCrabPercent;
    QLCDNumber *sunstarPercent;
    QSpinBox *spinBoxBrittle;
    QLabel *label;
    QSpinBox *spinBoxWestern;
    QSpinBox *spinBoxAcadian;
    QLabel *label_8;
    QLabel *label_5;
    QLCDNumber *snowCrabPercent;
    QLCDNumber *brittlePercent;
    QLabel *label_14;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *label_11;
    QLCDNumber *acadianCrabPercent;
    QLabel *label_6;
    QLabel *label_7;
    QLCDNumber *urchinPercent;
    QLCDNumber *hairyCrabPercent;
    QLCDNumber *greenCrabPercent;
    QSpinBox *spinBoxBoreal;
    QSpinBox *spinBoxSunstar;
    QPushButton *pushButtonCalcPercent;
    QLabel *label_13;
    QLabel *label_4;
    QSpinBox *spinBoxGreen;
    QToolButton *homePageButton_4;
    QSpinBox *spinBoxJonah;
    QLabel *label_12;
    QWidget *floatPage;
    QVBoxLayout *floatPageLayout;
    QHBoxLayout *floatHeaderLayout;
    QToolButton *homePageButton_5;
    QLabel *floatTitleLabel;
    QSpacerItem *floatHeaderSpacer;
    QLabel *floatInstructionLabel;
    QHBoxLayout *floatControlsLayout;
    QSpinBox *floatPortSpin;
    QPushButton *btnFloatStartReceiver;
    QPushButton *btnFloatStopReceiver;
    QPushButton *btnFloatImportPackets;
    QPushButton *btnFloatAddPackets;
    QPushButton *btnFloatLoadSample;
    QPushButton *btnFloatClear;
    QLabel *floatRxStatusLabel;
    QHBoxLayout *floatOffsetLayout;
    QLabel *floatBottomOffsetLabel;
    QDoubleSpinBox *spinFloatBottomOffset;
    QLabel *floatTopOffsetLabel;
    QDoubleSpinBox *spinFloatTopOffset;
    QSpacerItem *floatOffsetSpacer;
    QSplitter *floatMainSplitter;
    QWidget *floatPacketPanel;
    QVBoxLayout *floatPacketPanelLayout;
    QLabel *floatPacketInputLabel;
    QTextEdit *txtFloatPacketInput;
    QLabel *floatPacketTableLabel;
    QTableWidget *floatPacketTable;
    QWidget *floatGraphPanel;
    QVBoxLayout *floatGraphPanelLayout;
    QLabel *floatGraphLabel;
    QChartView *depthChart;
    QChartView *pressureChart;
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
        frame_6 = new QFrame(cameraPage);
        frame_6->setObjectName("frame_6");
        frame_6->setFrameShape(QFrame::Shape::Box);
        frame_6->setFrameShadow(QFrame::Shadow::Plain);
        frame_6->setLineWidth(2);
        horizontalLayout_3 = new QHBoxLayout(frame_6);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        captureCountLabel = new QLabel(frame_6);
        captureCountLabel->setObjectName("captureCountLabel");
        QFont font5;
        font5.setFamilies({QString::fromUtf8("Aileron")});
        captureCountLabel->setFont(font5);
        captureCountLabel->setFrameShape(QFrame::Shape::Box);

        horizontalLayout_3->addWidget(captureCountLabel);

        latencyLabel = new QLabel(frame_6);
        latencyLabel->setObjectName("latencyLabel");
        latencyLabel->setFont(font5);
        latencyLabel->setFrameShape(QFrame::Shape::Box);
        latencyLabel->setFrameShadow(QFrame::Shadow::Plain);

        horizontalLayout_3->addWidget(latencyLabel);

        timeLabel = new QLabel(frame_6);
        timeLabel->setObjectName("timeLabel");
        timeLabel->setFont(font5);
        timeLabel->setFrameShape(QFrame::Shape::Box);

        horizontalLayout_3->addWidget(timeLabel);

        alsStatusLabel = new QLabel(frame_6);
        alsStatusLabel->setObjectName("alsStatusLabel");
        QFont font6;
        font6.setFamilies({QString::fromUtf8("Aileron")});
        font6.setBold(true);
        alsStatusLabel->setFont(font6);
        alsStatusLabel->setStyleSheet(QString::fromUtf8("color: #ff4444;"));
        alsStatusLabel->setFrameShape(QFrame::Shape::Box);

        horizontalLayout_3->addWidget(alsStatusLabel);


        gridLayout_2->addWidget(frame_6, 0, 4, 1, 1);

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
        QFont font7;
        font7.setFamilies({QString::fromUtf8("Aileron")});
        font7.setPointSize(20);
        font7.setItalic(true);
        font7.setUnderline(false);
        label_9->setFont(font7);
        label_9->setFrameShape(QFrame::Shape::Box);

        gridLayout_3->addWidget(label_9, 0, 0, 1, 1, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignTop);

        lcdNumber_3 = new QLCDNumber(frame_5);
        lcdNumber_3->setObjectName("lcdNumber_3");
        lcdNumber_3->setFont(font5);
        lcdNumber_3->setStyleSheet(QString::fromUtf8(""));
        lcdNumber_3->setLineWidth(1);
        lcdNumber_3->setMidLineWidth(2);

        gridLayout_3->addWidget(lcdNumber_3, 1, 0, 1, 1);


        gridLayout_2->addWidget(frame_5, 3, 2, 1, 1);

        graphicsView = new QGraphicsView(cameraPage);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setFrameShape(QFrame::Shape::Box);
        graphicsView->setFrameShadow(QFrame::Shadow::Plain);
        graphicsView->setLineWidth(3);
        graphicsView->setMidLineWidth(0);

        gridLayout_2->addWidget(graphicsView, 1, 0, 1, 5);

        camName = new QLabel(cameraPage);
        camName->setObjectName("camName");
        QFont font8;
        font8.setFamilies({QString::fromUtf8("Aileron")});
        font8.setPointSize(20);
        font8.setBold(false);
        camName->setFont(font8);
        camName->setFrameShape(QFrame::Shape::Box);
        camName->setLineWidth(2);

        gridLayout_2->addWidget(camName, 0, 2, 1, 1);

        droneMap = new QFrame(cameraPage);
        droneMap->setObjectName("droneMap");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(droneMap->sizePolicy().hasHeightForWidth());
        droneMap->setSizePolicy(sizePolicy3);
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


        gridLayout_2->addWidget(droneMap, 3, 4, 1, 1);

        frame = new QFrame(cameraPage);
        frame->setObjectName("frame");
        sizePolicy3.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy3);
        QFont font10;
        font10.setFamilies({QString::fromUtf8("Aileron")});
        font10.setPointSize(16);
        frame->setFont(font10);
        frame->setFrameShape(QFrame::Shape::Box);
        frame->setFrameShadow(QFrame::Shadow::Plain);
        frame->setLineWidth(4);
        gridLayout_5 = new QGridLayout(frame);
        gridLayout_5->setObjectName("gridLayout_5");
        lcdNumber = new QLCDNumber(frame);
        lcdNumber->setObjectName("lcdNumber");
        QFont font11;
        font11.setFamilies({QString::fromUtf8("Aileron")});
        font11.setPointSize(17);
        lcdNumber->setFont(font11);

        gridLayout_5->addWidget(lcdNumber, 2, 0, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        label_15 = new QLabel(frame);
        label_15->setObjectName("label_15");
        QFont font12;
        font12.setFamilies({QString::fromUtf8("Aileron")});
        font12.setPointSize(17);
        font12.setItalic(true);
        label_15->setFont(font12);
        label_15->setFrameShape(QFrame::Shape::Box);

        gridLayout_5->addWidget(label_15, 0, 0, 1, 1, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignTop);

        pushButton_2 = new QPushButton(frame);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setFont(font10);
        pushButton_2->setStyleSheet(QString::fromUtf8("	background-color: rgb(44,181,222); /* A nice green color */\n"
"	border-width: 4px;\n"
"	border-style: ridge;\n"
"	border-color: rgb(152, 199, 65);\n"
"	selection-color: rgb(255, 255, 255);"));

        gridLayout_5->addWidget(pushButton_2, 3, 0, 1, 1);


        gridLayout_2->addWidget(frame, 3, 0, 1, 1);

        captureFramesButton = new QPushButton(cameraPage);
        captureFramesButton->setObjectName("captureFramesButton");
        QFont font13;
        font13.setFamilies({QString::fromUtf8("Aileron")});
        font13.setPointSize(12);
        captureFramesButton->setFont(font13);
        captureFramesButton->setStyleSheet(QString::fromUtf8("background-color: rgb(44,181,222);\n"
"color: white;\n"
"border-width: 3px;\n"
"border-style: ridge;\n"
"border-color: rgb(152,199,65);"));

        gridLayout_2->addWidget(captureFramesButton, 0, 1, 1, 1);

        homePageButton = new QToolButton(cameraPage);
        homePageButton->setObjectName("homePageButton");
        sizePolicy1.setHeightForWidth(homePageButton->sizePolicy().hasHeightForWidth());
        homePageButton->setSizePolicy(sizePolicy1);
        homePageButton->setMinimumSize(QSize(40, 30));
        homePageButton->setMaximumSize(QSize(40, 30));
        QFont font14;
        font14.setPointSize(13);
        font14.setBold(false);
        homePageButton->setFont(font14);
        homePageButton->setIconSize(QSize(16, 16));
        homePageButton->setAutoRaise(true);
        homePageButton->setArrowType(Qt::ArrowType::LeftArrow);

        gridLayout_2->addWidget(homePageButton, 0, 0, 1, 1);

        modeButton = new QPushButton(cameraPage);
        modeButton->setObjectName("modeButton");
        modeButton->setMinimumSize(QSize(160, 36));
        modeButton->setMaximumSize(QSize(160, 36));
        modeButton->setStyleSheet(QString::fromUtf8("background-color: rgb(44,181,222);\n"
"color: white;\n"
"border-width: 3px;\n"
"border-style: ridge;\n"
"border-color: rgb(152,199,65);\n"
"border-radius: 6px;\n"
"font-size: 13px;\n"
"font-weight: bold;"));

        gridLayout_2->addWidget(modeButton, 0, 3, 1, 1);

        stackedWidget->addWidget(cameraPage);
        modelingPage = new QWidget();
        modelingPage->setObjectName("modelingPage");
        modelingPageLayout = new QVBoxLayout(modelingPage);
        modelingPageLayout->setObjectName("modelingPageLayout");
        modelingTopRow = new QHBoxLayout();
        modelingTopRow->setObjectName("modelingTopRow");
        homePageButton_2 = new QToolButton(modelingPage);
        homePageButton_2->setObjectName("homePageButton_2");
        homePageButton_2->setMinimumSize(QSize(40, 30));
        homePageButton_2->setMaximumSize(QSize(40, 30));
        QFont font15;
        font15.setFamilies({QString::fromUtf8("Comic Sans MS")});
        homePageButton_2->setFont(font15);
        homePageButton_2->setPopupMode(QToolButton::ToolButtonPopupMode::DelayedPopup);
        homePageButton_2->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonFollowStyle);
        homePageButton_2->setAutoRaise(true);
        homePageButton_2->setArrowType(Qt::ArrowType::LeftArrow);

        modelingTopRow->addWidget(homePageButton_2);

        statusLabel = new QLabel(modelingPage);
        statusLabel->setObjectName("statusLabel");

        modelingTopRow->addWidget(statusLabel);


        modelingPageLayout->addLayout(modelingTopRow);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName("buttonLayout");
        importImagesButton = new QPushButton(modelingPage);
        importImagesButton->setObjectName("importImagesButton");

        buttonLayout->addWidget(importImagesButton);

        importVideoButton = new QPushButton(modelingPage);
        importVideoButton->setObjectName("importVideoButton");

        buttonLayout->addWidget(importVideoButton);

        clearButton = new QPushButton(modelingPage);
        clearButton->setObjectName("clearButton");

        buttonLayout->addWidget(clearButton);

        denseCheckBox = new QCheckBox(modelingPage);
        denseCheckBox->setObjectName("denseCheckBox");

        buttonLayout->addWidget(denseCheckBox);

        photogrammetryHorizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        buttonLayout->addItem(photogrammetryHorizontalSpacer);

        scaleButton = new QPushButton(modelingPage);
        scaleButton->setObjectName("scaleButton");
        scaleButton->setCheckable(true);

        buttonLayout->addWidget(scaleButton);

        measureButton = new QPushButton(modelingPage);
        measureButton->setObjectName("measureButton");
        measureButton->setCheckable(true);

        buttonLayout->addWidget(measureButton);

        loadPlyButton = new QPushButton(modelingPage);
        loadPlyButton->setObjectName("loadPlyButton");

        buttonLayout->addWidget(loadPlyButton);

        resetCameraButton = new QPushButton(modelingPage);
        resetCameraButton->setObjectName("resetCameraButton");

        buttonLayout->addWidget(resetCameraButton);

        runButton = new QPushButton(modelingPage);
        runButton->setObjectName("runButton");
        runButton->setEnabled(false);

        buttonLayout->addWidget(runButton);

        cancelButton = new QPushButton(modelingPage);
        cancelButton->setObjectName("cancelButton");
        cancelButton->setEnabled(false);

        buttonLayout->addWidget(cancelButton);


        modelingPageLayout->addLayout(buttonLayout);

        progressBar = new QProgressBar(modelingPage);
        progressBar->setObjectName("progressBar");
        progressBar->setMinimum(0);
        progressBar->setMaximum(3);
        progressBar->setValue(0);

        modelingPageLayout->addWidget(progressBar);

        mainSplitter = new QSplitter(modelingPage);
        mainSplitter->setObjectName("mainSplitter");
        mainSplitter->setOrientation(Qt::Orientation::Horizontal);
        imageList = new QListWidget(mainSplitter);
        imageList->setObjectName("imageList");
        imageList->setMinimumSize(QSize(180, 0));
        imageList->setMaximumSize(QSize(300, 16777215));
        imageList->setIconSize(QSize(120, 90));
        imageList->setResizeMode(QListView::ResizeMode::Adjust);
        imageList->setSpacing(4);
        imageList->setViewMode(QListView::ViewMode::IconMode);
        mainSplitter->addWidget(imageList);
        rightSplitter = new QSplitter(mainSplitter);
        rightSplitter->setObjectName("rightSplitter");
        rightSplitter->setOrientation(Qt::Orientation::Vertical);
        viewer = new ModelViewer(rightSplitter);
        viewer->setObjectName("viewer");
        viewer->setMinimumSize(QSize(0, 300));
        rightSplitter->addWidget(viewer);
        logOutput = new QTextEdit(rightSplitter);
        logOutput->setObjectName("logOutput");
        logOutput->setMaximumSize(QSize(16777215, 200));
        QFont font16;
        font16.setFamilies({QString::fromUtf8("Courier")});
        logOutput->setFont(font16);
        logOutput->setReadOnly(true);
        rightSplitter->addWidget(logOutput);
        mainSplitter->addWidget(rightSplitter);

        modelingPageLayout->addWidget(mainSplitter);

        stackedWidget->addWidget(modelingPage);
        icebergPage = new QWidget();
        icebergPage->setObjectName("icebergPage");
        gridLayout_6 = new QGridLayout(icebergPage);
        gridLayout_6->setObjectName("gridLayout_6");
        gridLayout_6->setHorizontalSpacing(14);
        gridLayout_6->setVerticalSpacing(10);
        gridLayout_6->setContentsMargins(14, 12, 14, 12);
        homePageButton_3 = new QToolButton(icebergPage);
        homePageButton_3->setObjectName("homePageButton_3");
        homePageButton_3->setMinimumSize(QSize(44, 34));
        homePageButton_3->setAutoRaise(true);
        homePageButton_3->setArrowType(Qt::ArrowType::LeftArrow);

        gridLayout_6->addWidget(homePageButton_3, 0, 0, 1, 1, Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);

        labelIcebergTitle = new QLabel(icebergPage);
        labelIcebergTitle->setObjectName("labelIcebergTitle");
        QFont font17;
        font17.setFamilies({QString::fromUtf8("Aileron")});
        font17.setPointSize(26);
        font17.setBold(true);
        labelIcebergTitle->setFont(font17);

        gridLayout_6->addWidget(labelIcebergTitle, 0, 1, 1, 2);

        icebergLeftColumn = new QVBoxLayout();
        icebergLeftColumn->setObjectName("icebergLeftColumn");
        groupPerimeterSurvey = new QGroupBox(icebergPage);
        groupPerimeterSurvey->setObjectName("groupPerimeterSurvey");
        gridPerimeterSurvey = new QGridLayout(groupPerimeterSurvey);
        gridPerimeterSurvey->setObjectName("gridPerimeterSurvey");
        labelSurveyPrompt = new QLabel(groupPerimeterSurvey);
        labelSurveyPrompt->setObjectName("labelSurveyPrompt");

        gridPerimeterSurvey->addWidget(labelSurveyPrompt, 0, 0, 1, 2);

        labelSurvey1 = new QLabel(groupPerimeterSurvey);
        labelSurvey1->setObjectName("labelSurvey1");

        gridPerimeterSurvey->addWidget(labelSurvey1, 1, 0, 1, 1);

        lineSurveyNumber1 = new QLineEdit(groupPerimeterSurvey);
        lineSurveyNumber1->setObjectName("lineSurveyNumber1");
        lineSurveyNumber1->setMaxLength(1);
        lineSurveyNumber1->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridPerimeterSurvey->addWidget(lineSurveyNumber1, 1, 1, 1, 1);

        labelSurvey2 = new QLabel(groupPerimeterSurvey);
        labelSurvey2->setObjectName("labelSurvey2");

        gridPerimeterSurvey->addWidget(labelSurvey2, 2, 0, 1, 1);

        lineSurveyNumber2 = new QLineEdit(groupPerimeterSurvey);
        lineSurveyNumber2->setObjectName("lineSurveyNumber2");
        lineSurveyNumber2->setMaxLength(1);
        lineSurveyNumber2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridPerimeterSurvey->addWidget(lineSurveyNumber2, 2, 1, 1, 1);

        labelSurvey3 = new QLabel(groupPerimeterSurvey);
        labelSurvey3->setObjectName("labelSurvey3");

        gridPerimeterSurvey->addWidget(labelSurvey3, 3, 0, 1, 1);

        lineSurveyNumber3 = new QLineEdit(groupPerimeterSurvey);
        lineSurveyNumber3->setObjectName("lineSurveyNumber3");
        lineSurveyNumber3->setMaxLength(1);
        lineSurveyNumber3->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridPerimeterSurvey->addWidget(lineSurveyNumber3, 3, 1, 1, 1);

        labelSurvey4 = new QLabel(groupPerimeterSurvey);
        labelSurvey4->setObjectName("labelSurvey4");

        gridPerimeterSurvey->addWidget(labelSurvey4, 4, 0, 1, 1);

        lineSurveyNumber4 = new QLineEdit(groupPerimeterSurvey);
        lineSurveyNumber4->setObjectName("lineSurveyNumber4");
        lineSurveyNumber4->setMaxLength(1);
        lineSurveyNumber4->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridPerimeterSurvey->addWidget(lineSurveyNumber4, 4, 1, 1, 1);

        labelSurvey5 = new QLabel(groupPerimeterSurvey);
        labelSurvey5->setObjectName("labelSurvey5");

        gridPerimeterSurvey->addWidget(labelSurvey5, 5, 0, 1, 1);

        lineSurveyNumber5 = new QLineEdit(groupPerimeterSurvey);
        lineSurveyNumber5->setObjectName("lineSurveyNumber5");
        lineSurveyNumber5->setMaxLength(1);
        lineSurveyNumber5->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridPerimeterSurvey->addWidget(lineSurveyNumber5, 5, 1, 1, 1);


        icebergLeftColumn->addWidget(groupPerimeterSurvey);

        groupKeelMeasurement = new QGroupBox(icebergPage);
        groupKeelMeasurement->setObjectName("groupKeelMeasurement");
        gridKeelMeasurement = new QGridLayout(groupKeelMeasurement);
        gridKeelMeasurement->setObjectName("gridKeelMeasurement");
        gridKeelMeasurement->setHorizontalSpacing(10);
        gridKeelMeasurement->setVerticalSpacing(8);
        labelLiveDepth = new QLabel(groupKeelMeasurement);
        labelLiveDepth->setObjectName("labelLiveDepth");

        gridKeelMeasurement->addWidget(labelLiveDepth, 0, 0, 1, 1);

        lcdLiveDepth = new QLCDNumber(groupKeelMeasurement);
        lcdLiveDepth->setObjectName("lcdLiveDepth");
        lcdLiveDepth->setDigitCount(6);
        lcdLiveDepth->setMinimumSize(QSize(150, 42));
        lcdLiveDepth->setSegmentStyle(QLCDNumber::SegmentStyle::Filled);

        gridKeelMeasurement->addWidget(lcdLiveDepth, 0, 1, 1, 1);

        btnRecordDepth = new QPushButton(groupKeelMeasurement);
        btnRecordDepth->setObjectName("btnRecordDepth");

        gridKeelMeasurement->addWidget(btnRecordDepth, 1, 0, 1, 2);

        labelFinalKeel = new QLabel(groupKeelMeasurement);
        labelFinalKeel->setObjectName("labelFinalKeel");

        gridKeelMeasurement->addWidget(labelFinalKeel, 2, 0, 1, 1);

        spinFinalKeelDepth = new QDoubleSpinBox(groupKeelMeasurement);
        spinFinalKeelDepth->setObjectName("spinFinalKeelDepth");
        spinFinalKeelDepth->setDecimals(2);
        spinFinalKeelDepth->setMaximum(200.000000000000000);
        spinFinalKeelDepth->setSingleStep(0.010000000000000);

        gridKeelMeasurement->addWidget(spinFinalKeelDepth, 2, 1, 1, 1);


        icebergLeftColumn->addWidget(groupKeelMeasurement);

        groupIcebergInfo = new QGroupBox(icebergPage);
        groupIcebergInfo->setObjectName("groupIcebergInfo");
        formIcebergInfo = new QFormLayout(groupIcebergInfo);
        formIcebergInfo->setObjectName("formIcebergInfo");
        labelIcebergLatitude = new QLabel(groupIcebergInfo);
        labelIcebergLatitude->setObjectName("labelIcebergLatitude");

        formIcebergInfo->setWidget(0, QFormLayout::ItemRole::LabelRole, labelIcebergLatitude);

        spinIcebergLatitude = new QDoubleSpinBox(groupIcebergInfo);
        spinIcebergLatitude->setObjectName("spinIcebergLatitude");
        spinIcebergLatitude->setDecimals(4);
        spinIcebergLatitude->setMinimum(-90.000000000000000);
        spinIcebergLatitude->setMaximum(90.000000000000000);
        spinIcebergLatitude->setSingleStep(0.000100000000000);
        spinIcebergLatitude->setValue(46.399999999999999);

        formIcebergInfo->setWidget(0, QFormLayout::ItemRole::FieldRole, spinIcebergLatitude);

        labelIcebergLongitude = new QLabel(groupIcebergInfo);
        labelIcebergLongitude->setObjectName("labelIcebergLongitude");

        formIcebergInfo->setWidget(1, QFormLayout::ItemRole::LabelRole, labelIcebergLongitude);

        spinIcebergLongitude = new QDoubleSpinBox(groupIcebergInfo);
        spinIcebergLongitude->setObjectName("spinIcebergLongitude");
        spinIcebergLongitude->setDecimals(4);
        spinIcebergLongitude->setMinimum(-180.000000000000000);
        spinIcebergLongitude->setMaximum(180.000000000000000);
        spinIcebergLongitude->setSingleStep(0.000100000000000);
        spinIcebergLongitude->setValue(-48.399999999999999);

        formIcebergInfo->setWidget(1, QFormLayout::ItemRole::FieldRole, spinIcebergLongitude);

        labelIcebergHeading = new QLabel(groupIcebergInfo);
        labelIcebergHeading->setObjectName("labelIcebergHeading");

        formIcebergInfo->setWidget(2, QFormLayout::ItemRole::LabelRole, labelIcebergHeading);

        spinIcebergHeading = new QDoubleSpinBox(groupIcebergInfo);
        spinIcebergHeading->setObjectName("spinIcebergHeading");
        spinIcebergHeading->setDecimals(1);
        spinIcebergHeading->setMaximum(359.899999999999977);

        formIcebergInfo->setWidget(2, QFormLayout::ItemRole::FieldRole, spinIcebergHeading);


        icebergLeftColumn->addWidget(groupIcebergInfo);


        gridLayout_6->addLayout(icebergLeftColumn, 1, 0, 2, 1);

        groupTrackMap = new QGroupBox(icebergPage);
        groupTrackMap->setObjectName("groupTrackMap");
        verticalLayoutTrackMap = new QVBoxLayout(groupTrackMap);
        verticalLayoutTrackMap->setObjectName("verticalLayoutTrackMap");
        tacticalview = new QGraphicsView(groupTrackMap);
        tacticalview->setObjectName("tacticalview");
        tacticalview->setMinimumSize(QSize(280, 260));

        verticalLayoutTrackMap->addWidget(tacticalview);


        gridLayout_6->addWidget(groupTrackMap, 1, 1, 1, 1);

        tablePlatformThreats = new QTableWidget(icebergPage);
        if (tablePlatformThreats->columnCount() < 7)
            tablePlatformThreats->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tablePlatformThreats->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tablePlatformThreats->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tablePlatformThreats->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tablePlatformThreats->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tablePlatformThreats->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tablePlatformThreats->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tablePlatformThreats->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        if (tablePlatformThreats->rowCount() < 4)
            tablePlatformThreats->setRowCount(4);
        tablePlatformThreats->setObjectName("tablePlatformThreats");
        tablePlatformThreats->setMinimumSize(QSize(560, 300));
        tablePlatformThreats->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        tablePlatformThreats->setSelectionMode(QAbstractItemView::SelectionMode::NoSelection);

        gridLayout_6->addWidget(tablePlatformThreats, 1, 2, 1, 1);

        groupJudgeSummary = new QGroupBox(icebergPage);
        groupJudgeSummary->setObjectName("groupJudgeSummary");
        verticalLayoutJudgeSummary = new QVBoxLayout(groupJudgeSummary);
        verticalLayoutJudgeSummary->setObjectName("verticalLayoutJudgeSummary");
        txtJudgeSummary = new QPlainTextEdit(groupJudgeSummary);
        txtJudgeSummary->setObjectName("txtJudgeSummary");
        txtJudgeSummary->setMinimumSize(QSize(0, 130));
        txtJudgeSummary->setReadOnly(false);

        verticalLayoutJudgeSummary->addWidget(txtJudgeSummary);


        gridLayout_6->addWidget(groupJudgeSummary, 2, 1, 1, 2);

        stackedWidget->addWidget(icebergPage);
        ednaPage = new QWidget();
        ednaPage->setObjectName("ednaPage");
        ednaPage->setStyleSheet(QString::fromUtf8("#ednaPage{\n"
"	border-image: url(:/images/images/bubbles_and_animals.png);\n"
"}"));
        gridLayout_4 = new QGridLayout(ednaPage);
        gridLayout_4->setObjectName("gridLayout_4");
        spinBoxRock = new QSpinBox(ednaPage);
        spinBoxRock->setObjectName("spinBoxRock");
        QFont font18;
        font18.setFamilies({QString::fromUtf8("Aileron")});
        font18.setPointSize(30);
        spinBoxRock->setFont(font18);

        gridLayout_4->addWidget(spinBoxRock, 5, 2, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        borealPercent = new QLCDNumber(ednaPage);
        borealPercent->setObjectName("borealPercent");
        QFont font19;
        font19.setFamilies({QString::fromUtf8("Aileron")});
        font19.setPointSize(20);
        borealPercent->setFont(font19);
        borealPercent->setFrameShadow(QFrame::Shadow::Plain);
        borealPercent->setSmallDecimalPoint(true);
        borealPercent->setSegmentStyle(QLCDNumber::SegmentStyle::Flat);

        gridLayout_4->addWidget(borealPercent, 4, 6, 1, 1);

        spinBoxUrchin = new QSpinBox(ednaPage);
        spinBoxUrchin->setObjectName("spinBoxUrchin");
        spinBoxUrchin->setFont(font18);

        gridLayout_4->addWidget(spinBoxUrchin, 4, 2, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        label_10 = new QLabel(ednaPage);
        label_10->setObjectName("label_10");
        label_10->setFont(font19);
        label_10->setFrameShape(QFrame::Shape::Box);

        gridLayout_4->addWidget(label_10, 4, 4, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        rockCrabPercent = new QLCDNumber(ednaPage);
        rockCrabPercent->setObjectName("rockCrabPercent");
        rockCrabPercent->setFont(font19);
        rockCrabPercent->setFrameShadow(QFrame::Shadow::Plain);
        rockCrabPercent->setSmallDecimalPoint(true);
        rockCrabPercent->setSegmentStyle(QLCDNumber::SegmentStyle::Flat);

        gridLayout_4->addWidget(rockCrabPercent, 5, 3, 1, 1);

        spinBoxSnow = new QSpinBox(ednaPage);
        spinBoxSnow->setObjectName("spinBoxSnow");
        spinBoxSnow->setFont(font18);

        gridLayout_4->addWidget(spinBoxSnow, 1, 2, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        jonahCrabPercent = new QLCDNumber(ednaPage);
        jonahCrabPercent->setObjectName("jonahCrabPercent");
        jonahCrabPercent->setFont(font19);
        jonahCrabPercent->setFrameShadow(QFrame::Shadow::Plain);
        jonahCrabPercent->setSmallDecimalPoint(true);
        jonahCrabPercent->setSegmentStyle(QLCDNumber::SegmentStyle::Flat);

        gridLayout_4->addWidget(jonahCrabPercent, 1, 6, 1, 1);

        sunstarPercent = new QLCDNumber(ednaPage);
        sunstarPercent->setObjectName("sunstarPercent");
        sunstarPercent->setFont(font19);
        sunstarPercent->setFrameShadow(QFrame::Shadow::Plain);
        sunstarPercent->setSmallDecimalPoint(true);
        sunstarPercent->setSegmentStyle(QLCDNumber::SegmentStyle::Flat);

        gridLayout_4->addWidget(sunstarPercent, 2, 6, 1, 1);

        spinBoxBrittle = new QSpinBox(ednaPage);
        spinBoxBrittle->setObjectName("spinBoxBrittle");
        spinBoxBrittle->setFont(font18);

        gridLayout_4->addWidget(spinBoxBrittle, 5, 5, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        label = new QLabel(ednaPage);
        label->setObjectName("label");
        label->setFont(font19);
        label->setFrameShape(QFrame::Shape::Box);

        gridLayout_4->addWidget(label, 1, 4, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        spinBoxWestern = new QSpinBox(ednaPage);
        spinBoxWestern->setObjectName("spinBoxWestern");
        spinBoxWestern->setFont(font18);

        gridLayout_4->addWidget(spinBoxWestern, 3, 2, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        spinBoxAcadian = new QSpinBox(ednaPage);
        spinBoxAcadian->setObjectName("spinBoxAcadian");
        spinBoxAcadian->setFont(font18);

        gridLayout_4->addWidget(spinBoxAcadian, 2, 2, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        label_8 = new QLabel(ednaPage);
        label_8->setObjectName("label_8");
        label_8->setFont(font19);
        label_8->setFrameShape(QFrame::Shape::Box);

        gridLayout_4->addWidget(label_8, 3, 4, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        label_5 = new QLabel(ednaPage);
        label_5->setObjectName("label_5");
        label_5->setFont(font19);
        label_5->setFrameShape(QFrame::Shape::Box);

        gridLayout_4->addWidget(label_5, 5, 1, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        snowCrabPercent = new QLCDNumber(ednaPage);
        snowCrabPercent->setObjectName("snowCrabPercent");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(snowCrabPercent->sizePolicy().hasHeightForWidth());
        snowCrabPercent->setSizePolicy(sizePolicy4);
        QFont font20;
        font20.setFamilies({QString::fromUtf8("Aileron")});
        font20.setPointSize(26);
        snowCrabPercent->setFont(font20);
        snowCrabPercent->setFrameShadow(QFrame::Shadow::Plain);
        snowCrabPercent->setSmallDecimalPoint(true);
        snowCrabPercent->setMode(QLCDNumber::Mode::Dec);
        snowCrabPercent->setSegmentStyle(QLCDNumber::SegmentStyle::Flat);

        gridLayout_4->addWidget(snowCrabPercent, 1, 3, 1, 1);

        brittlePercent = new QLCDNumber(ednaPage);
        brittlePercent->setObjectName("brittlePercent");
        brittlePercent->setFont(font19);
        brittlePercent->setFrameShadow(QFrame::Shadow::Plain);
        brittlePercent->setSmallDecimalPoint(true);
        brittlePercent->setSegmentStyle(QLCDNumber::SegmentStyle::Flat);

        gridLayout_4->addWidget(brittlePercent, 5, 6, 1, 1);

        label_14 = new QLabel(ednaPage);
        label_14->setObjectName("label_14");
        QFont font21;
        font21.setFamilies({QString::fromUtf8("Aileron")});
        font21.setPointSize(30);
        font21.setItalic(true);
        label_14->setFont(font21);

        gridLayout_4->addWidget(label_14, 0, 3, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        label_3 = new QLabel(ednaPage);
        label_3->setObjectName("label_3");
        label_3->setFont(font19);
        label_3->setFrameShape(QFrame::Shape::Box);

        gridLayout_4->addWidget(label_3, 3, 1, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        label_2 = new QLabel(ednaPage);
        label_2->setObjectName("label_2");
        label_2->setFont(font19);
        label_2->setFrameShape(QFrame::Shape::Box);

        gridLayout_4->addWidget(label_2, 2, 1, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        label_11 = new QLabel(ednaPage);
        label_11->setObjectName("label_11");
        label_11->setFont(font19);
        label_11->setFrameShape(QFrame::Shape::Box);

        gridLayout_4->addWidget(label_11, 5, 4, 1, 1, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignVCenter);

        acadianCrabPercent = new QLCDNumber(ednaPage);
        acadianCrabPercent->setObjectName("acadianCrabPercent");
        acadianCrabPercent->setFont(font19);
        acadianCrabPercent->setFrameShadow(QFrame::Shadow::Plain);
        acadianCrabPercent->setSmallDecimalPoint(true);
        acadianCrabPercent->setSegmentStyle(QLCDNumber::SegmentStyle::Flat);

        gridLayout_4->addWidget(acadianCrabPercent, 2, 3, 1, 1);

        label_6 = new QLabel(ednaPage);
        label_6->setObjectName("label_6");
        label_6->setFont(font19);
        label_6->setFrameShape(QFrame::Shape::Box);

        gridLayout_4->addWidget(label_6, 1, 1, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        label_7 = new QLabel(ednaPage);
        label_7->setObjectName("label_7");
        label_7->setFont(font19);
        label_7->setFrameShape(QFrame::Shape::Box);

        gridLayout_4->addWidget(label_7, 2, 4, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        urchinPercent = new QLCDNumber(ednaPage);
        urchinPercent->setObjectName("urchinPercent");
        urchinPercent->setFont(font19);
        urchinPercent->setFrameShadow(QFrame::Shadow::Plain);
        urchinPercent->setSmallDecimalPoint(true);
        urchinPercent->setSegmentStyle(QLCDNumber::SegmentStyle::Flat);

        gridLayout_4->addWidget(urchinPercent, 4, 3, 1, 1);

        hairyCrabPercent = new QLCDNumber(ednaPage);
        hairyCrabPercent->setObjectName("hairyCrabPercent");
        hairyCrabPercent->setFont(font19);
        hairyCrabPercent->setFrameShadow(QFrame::Shadow::Plain);
        hairyCrabPercent->setSmallDecimalPoint(true);
        hairyCrabPercent->setSegmentStyle(QLCDNumber::SegmentStyle::Flat);

        gridLayout_4->addWidget(hairyCrabPercent, 3, 3, 1, 1);

        greenCrabPercent = new QLCDNumber(ednaPage);
        greenCrabPercent->setObjectName("greenCrabPercent");
        greenCrabPercent->setFont(font19);
        greenCrabPercent->setFrameShadow(QFrame::Shadow::Plain);
        greenCrabPercent->setSmallDecimalPoint(true);
        greenCrabPercent->setSegmentStyle(QLCDNumber::SegmentStyle::Flat);

        gridLayout_4->addWidget(greenCrabPercent, 3, 6, 1, 1);

        spinBoxBoreal = new QSpinBox(ednaPage);
        spinBoxBoreal->setObjectName("spinBoxBoreal");
        spinBoxBoreal->setFont(font18);

        gridLayout_4->addWidget(spinBoxBoreal, 4, 5, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        spinBoxSunstar = new QSpinBox(ednaPage);
        spinBoxSunstar->setObjectName("spinBoxSunstar");
        spinBoxSunstar->setFont(font18);

        gridLayout_4->addWidget(spinBoxSunstar, 2, 5, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        pushButtonCalcPercent = new QPushButton(ednaPage);
        pushButtonCalcPercent->setObjectName("pushButtonCalcPercent");
        QFont font22;
        font22.setFamilies({QString::fromUtf8("Aileron")});
        font22.setPointSize(20);
        font22.setItalic(false);
        pushButtonCalcPercent->setFont(font22);
        pushButtonCalcPercent->setStyleSheet(QString::fromUtf8("	background-color: rgb(44,181,222); /* A nice green color */\n"
"	border-width: 4px;\n"
"	border-style: ridge;\n"
"	border-color: rgb(152, 199, 65);\n"
"	selection-color: rgb(255, 255, 255);"));

        gridLayout_4->addWidget(pushButtonCalcPercent, 0, 4, 1, 1);

        label_13 = new QLabel(ednaPage);
        label_13->setObjectName("label_13");
        label_13->setFont(font21);

        gridLayout_4->addWidget(label_13, 0, 2, 1, 1, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignTop);

        label_4 = new QLabel(ednaPage);
        label_4->setObjectName("label_4");
        label_4->setFont(font19);
        label_4->setFrameShape(QFrame::Shape::Box);

        gridLayout_4->addWidget(label_4, 4, 1, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        spinBoxGreen = new QSpinBox(ednaPage);
        spinBoxGreen->setObjectName("spinBoxGreen");
        spinBoxGreen->setFont(font18);

        gridLayout_4->addWidget(spinBoxGreen, 3, 5, 1, 1, Qt::AlignmentFlag::AlignHCenter);

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

        spinBoxJonah = new QSpinBox(ednaPage);
        spinBoxJonah->setObjectName("spinBoxJonah");
        spinBoxJonah->setFont(font18);

        gridLayout_4->addWidget(spinBoxJonah, 1, 5, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        label_12 = new QLabel(ednaPage);
        label_12->setObjectName("label_12");
        QFont font23;
        font23.setFamilies({QString::fromUtf8("Aileron")});
        font23.setPointSize(33);
        font23.setItalic(true);
        label_12->setFont(font23);
        label_12->setFrameShape(QFrame::Shape::NoFrame);
        label_12->setTextFormat(Qt::TextFormat::AutoText);

        gridLayout_4->addWidget(label_12, 0, 1, 1, 1, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignTop);

        stackedWidget->addWidget(ednaPage);
        floatPage = new QWidget();
        floatPage->setObjectName("floatPage");
        floatPageLayout = new QVBoxLayout(floatPage);
        floatPageLayout->setObjectName("floatPageLayout");
        floatPageLayout->setContentsMargins(12, 10, 12, 12);
        floatHeaderLayout = new QHBoxLayout();
        floatHeaderLayout->setObjectName("floatHeaderLayout");
        homePageButton_5 = new QToolButton(floatPage);
        homePageButton_5->setObjectName("homePageButton_5");
        homePageButton_5->setMinimumSize(QSize(40, 30));
        homePageButton_5->setMaximumSize(QSize(40, 30));
        homePageButton_5->setFont(font15);
        homePageButton_5->setPopupMode(QToolButton::ToolButtonPopupMode::DelayedPopup);
        homePageButton_5->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonFollowStyle);
        homePageButton_5->setAutoRaise(true);
        homePageButton_5->setArrowType(Qt::ArrowType::LeftArrow);

        floatHeaderLayout->addWidget(homePageButton_5);

        floatTitleLabel = new QLabel(floatPage);
        floatTitleLabel->setObjectName("floatTitleLabel");
        QFont font24;
        font24.setFamilies({QString::fromUtf8("Aileron")});
        font24.setPointSize(24);
        font24.setBold(true);
        floatTitleLabel->setFont(font24);

        floatHeaderLayout->addWidget(floatTitleLabel);

        floatHeaderSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        floatHeaderLayout->addItem(floatHeaderSpacer);


        floatPageLayout->addLayout(floatHeaderLayout);

        floatInstructionLabel = new QLabel(floatPage);
        floatInstructionLabel->setObjectName("floatInstructionLabel");
        floatInstructionLabel->setWordWrap(true);

        floatPageLayout->addWidget(floatInstructionLabel);

        floatControlsLayout = new QHBoxLayout();
        floatControlsLayout->setObjectName("floatControlsLayout");
        floatPortSpin = new QSpinBox(floatPage);
        floatPortSpin->setObjectName("floatPortSpin");
        floatPortSpin->setMinimum(1024);
        floatPortSpin->setMaximum(65535);
        floatPortSpin->setValue(5007);

        floatControlsLayout->addWidget(floatPortSpin);

        btnFloatStartReceiver = new QPushButton(floatPage);
        btnFloatStartReceiver->setObjectName("btnFloatStartReceiver");

        floatControlsLayout->addWidget(btnFloatStartReceiver);

        btnFloatStopReceiver = new QPushButton(floatPage);
        btnFloatStopReceiver->setObjectName("btnFloatStopReceiver");

        floatControlsLayout->addWidget(btnFloatStopReceiver);

        btnFloatImportPackets = new QPushButton(floatPage);
        btnFloatImportPackets->setObjectName("btnFloatImportPackets");

        floatControlsLayout->addWidget(btnFloatImportPackets);

        btnFloatAddPackets = new QPushButton(floatPage);
        btnFloatAddPackets->setObjectName("btnFloatAddPackets");

        floatControlsLayout->addWidget(btnFloatAddPackets);

        btnFloatLoadSample = new QPushButton(floatPage);
        btnFloatLoadSample->setObjectName("btnFloatLoadSample");

        floatControlsLayout->addWidget(btnFloatLoadSample);

        btnFloatClear = new QPushButton(floatPage);
        btnFloatClear->setObjectName("btnFloatClear");

        floatControlsLayout->addWidget(btnFloatClear);

        floatRxStatusLabel = new QLabel(floatPage);
        floatRxStatusLabel->setObjectName("floatRxStatusLabel");
        floatRxStatusLabel->setMinimumSize(QSize(150, 0));

        floatControlsLayout->addWidget(floatRxStatusLabel);


        floatPageLayout->addLayout(floatControlsLayout);

        floatOffsetLayout = new QHBoxLayout();
        floatOffsetLayout->setObjectName("floatOffsetLayout");
        floatBottomOffsetLabel = new QLabel(floatPage);
        floatBottomOffsetLabel->setObjectName("floatBottomOffsetLabel");

        floatOffsetLayout->addWidget(floatBottomOffsetLabel);

        spinFloatBottomOffset = new QDoubleSpinBox(floatPage);
        spinFloatBottomOffset->setObjectName("spinFloatBottomOffset");
        spinFloatBottomOffset->setMaximum(100.000000000000000);

        floatOffsetLayout->addWidget(spinFloatBottomOffset);

        floatTopOffsetLabel = new QLabel(floatPage);
        floatTopOffsetLabel->setObjectName("floatTopOffsetLabel");

        floatOffsetLayout->addWidget(floatTopOffsetLabel);

        spinFloatTopOffset = new QDoubleSpinBox(floatPage);
        spinFloatTopOffset->setObjectName("spinFloatTopOffset");
        spinFloatTopOffset->setMaximum(100.000000000000000);

        floatOffsetLayout->addWidget(spinFloatTopOffset);

        floatOffsetSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        floatOffsetLayout->addItem(floatOffsetSpacer);


        floatPageLayout->addLayout(floatOffsetLayout);

        floatMainSplitter = new QSplitter(floatPage);
        floatMainSplitter->setObjectName("floatMainSplitter");
        floatMainSplitter->setOrientation(Qt::Orientation::Horizontal);
        floatPacketPanel = new QWidget(floatMainSplitter);
        floatPacketPanel->setObjectName("floatPacketPanel");
        floatPacketPanelLayout = new QVBoxLayout(floatPacketPanel);
        floatPacketPanelLayout->setObjectName("floatPacketPanelLayout");
        floatPacketPanelLayout->setContentsMargins(0, 0, 0, 0);
        floatPacketInputLabel = new QLabel(floatPacketPanel);
        floatPacketInputLabel->setObjectName("floatPacketInputLabel");

        floatPacketPanelLayout->addWidget(floatPacketInputLabel);

        txtFloatPacketInput = new QTextEdit(floatPacketPanel);
        txtFloatPacketInput->setObjectName("txtFloatPacketInput");
        txtFloatPacketInput->setMinimumSize(QSize(0, 90));

        floatPacketPanelLayout->addWidget(txtFloatPacketInput);

        floatPacketTableLabel = new QLabel(floatPacketPanel);
        floatPacketTableLabel->setObjectName("floatPacketTableLabel");

        floatPacketPanelLayout->addWidget(floatPacketTableLabel);

        floatPacketTable = new QTableWidget(floatPacketPanel);
        floatPacketTable->setObjectName("floatPacketTable");
        floatPacketTable->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        floatPacketPanelLayout->addWidget(floatPacketTable);

        floatMainSplitter->addWidget(floatPacketPanel);
        floatGraphPanel = new QWidget(floatMainSplitter);
        floatGraphPanel->setObjectName("floatGraphPanel");
        floatGraphPanelLayout = new QVBoxLayout(floatGraphPanel);
        floatGraphPanelLayout->setObjectName("floatGraphPanelLayout");
        floatGraphPanelLayout->setContentsMargins(0, 0, 0, 0);
        floatGraphLabel = new QLabel(floatGraphPanel);
        floatGraphLabel->setObjectName("floatGraphLabel");

        floatGraphPanelLayout->addWidget(floatGraphLabel);

        depthChart = new QChartView(floatGraphPanel);
        depthChart->setObjectName("depthChart");
        depthChart->setMinimumSize(QSize(0, 330));

        floatGraphPanelLayout->addWidget(depthChart);

        pressureChart = new QChartView(floatGraphPanel);
        pressureChart->setObjectName("pressureChart");
        pressureChart->setMinimumSize(QSize(0, 260));
        pressureChart->setFocusPolicy(Qt::FocusPolicy::TabFocus);
        pressureChart->setInteractive(false);
        pressureChart->setRenderHints(QPainter::RenderHint::Antialiasing);

        floatGraphPanelLayout->addWidget(pressureChart);

        floatMainSplitter->addWidget(floatGraphPanel);

        floatPageLayout->addWidget(floatMainSplitter);

        stackedWidget->addWidget(floatPage);
        settingsPage = new QWidget();
        settingsPage->setObjectName("settingsPage");
        homePageButton_6 = new QToolButton(settingsPage);
        homePageButton_6->setObjectName("homePageButton_6");
        homePageButton_6->setGeometry(QRect(0, 0, 40, 30));
        homePageButton_6->setMinimumSize(QSize(40, 30));
        homePageButton_6->setMaximumSize(QSize(40, 30));
        homePageButton_6->setFont(font15);
        homePageButton_6->setPopupMode(QToolButton::ToolButtonPopupMode::DelayedPopup);
        homePageButton_6->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonFollowStyle);
        homePageButton_6->setAutoRaise(true);
        homePageButton_6->setArrowType(Qt::ArrowType::LeftArrow);
        stackedWidget->addWidget(settingsPage);

        verticalLayout_2->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(5);


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
        captureCountLabel->setText(QCoreApplication::translate("MainWindow", "0 frames", nullptr));
        latencyLabel->setText(QCoreApplication::translate("MainWindow", "Latency: 0ms", nullptr));
        timeLabel->setText(QCoreApplication::translate("MainWindow", "Current Time", nullptr));
        alsStatusLabel->setText(QCoreApplication::translate("MainWindow", "ALS: OFF", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "European Green Crab Count", nullptr));
        camName->setText(QCoreApplication::translate("MainWindow", "Camera :  PlaceHolder", nullptr));
        leftCamButton->setText(QCoreApplication::translate("MainWindow", "Left", nullptr));
        botCamButton->setText(QCoreApplication::translate("MainWindow", "Bottom", nullptr));
        rightCamButton->setText(QCoreApplication::translate("MainWindow", "Right", nullptr));
        frontCamButton->setText(QCoreApplication::translate("MainWindow", "Front", nullptr));
        backCamButton->setText(QCoreApplication::translate("MainWindow", "Back", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "Current Keel Depth", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Store Value", nullptr));
        captureFramesButton->setText(QCoreApplication::translate("MainWindow", "Capture Frames", nullptr));
        modeButton->setText(QCoreApplication::translate("MainWindow", "Live  2048x1536 @ 30fps", nullptr));
        homePageButton_2->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        statusLabel->setText(QCoreApplication::translate("MainWindow", "Ready \342\200\224 import images to begin", nullptr));
        importImagesButton->setText(QCoreApplication::translate("MainWindow", "Import Images", nullptr));
        importVideoButton->setText(QCoreApplication::translate("MainWindow", "Import Video", nullptr));
        clearButton->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        denseCheckBox->setText(QCoreApplication::translate("MainWindow", "Dense Reconstruction", nullptr));
        scaleButton->setText(QCoreApplication::translate("MainWindow", "Set Scale", nullptr));
        measureButton->setText(QCoreApplication::translate("MainWindow", "Measure", nullptr));
        loadPlyButton->setText(QCoreApplication::translate("MainWindow", "Open PLY...", nullptr));
        resetCameraButton->setText(QCoreApplication::translate("MainWindow", "Reset View", nullptr));
        runButton->setText(QCoreApplication::translate("MainWindow", "Run Photogrammetry", nullptr));
        cancelButton->setText(QCoreApplication::translate("MainWindow", "Cancel", nullptr));
        progressBar->setFormat(QCoreApplication::translate("MainWindow", "Step %v / %m", nullptr));
        homePageButton_3->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        labelIcebergTitle->setText(QCoreApplication::translate("MainWindow", "Iceberg Keel Depth Task", nullptr));
        groupPerimeterSurvey->setTitle(QCoreApplication::translate("MainWindow", "Perimeter Survey (Numbers located on the perimeters of the icebergs)", nullptr));
        labelSurveyPrompt->setText(QCoreApplication::translate("MainWindow", "Show each number clearly to the judge.", nullptr));
        labelSurvey1->setText(QCoreApplication::translate("MainWindow", "Number 1:", nullptr));
        lineSurveyNumber1->setPlaceholderText(QCoreApplication::translate("MainWindow", "0-9", nullptr));
        labelSurvey2->setText(QCoreApplication::translate("MainWindow", "Number 2:", nullptr));
        lineSurveyNumber2->setPlaceholderText(QCoreApplication::translate("MainWindow", "0-9", nullptr));
        labelSurvey3->setText(QCoreApplication::translate("MainWindow", "Number 3:", nullptr));
        lineSurveyNumber3->setPlaceholderText(QCoreApplication::translate("MainWindow", "0-9", nullptr));
        labelSurvey4->setText(QCoreApplication::translate("MainWindow", "Number 4:", nullptr));
        lineSurveyNumber4->setPlaceholderText(QCoreApplication::translate("MainWindow", "0-9", nullptr));
        labelSurvey5->setText(QCoreApplication::translate("MainWindow", "Number 5:", nullptr));
        lineSurveyNumber5->setPlaceholderText(QCoreApplication::translate("MainWindow", "0-9", nullptr));
        groupKeelMeasurement->setTitle(QCoreApplication::translate("MainWindow", "Keel Measurement", nullptr));
        labelLiveDepth->setText(QCoreApplication::translate("MainWindow", "Live sensor depth", nullptr));
        btnRecordDepth->setText(QCoreApplication::translate("MainWindow", "Record Keel Depth", nullptr));
        labelFinalKeel->setText(QCoreApplication::translate("MainWindow", "Final keel depth", nullptr));
        spinFinalKeelDepth->setSuffix(QCoreApplication::translate("MainWindow", " m", nullptr));
        groupIcebergInfo->setTitle(QCoreApplication::translate("MainWindow", "Iceberg Information Sheet (From Sheet)", nullptr));
        labelIcebergLatitude->setText(QCoreApplication::translate("MainWindow", "Latitude", nullptr));
        spinIcebergLatitude->setSuffix(QCoreApplication::translate("MainWindow", " deg", nullptr));
        labelIcebergLongitude->setText(QCoreApplication::translate("MainWindow", "Longitude", nullptr));
        spinIcebergLongitude->setSuffix(QCoreApplication::translate("MainWindow", " deg", nullptr));
        labelIcebergHeading->setText(QCoreApplication::translate("MainWindow", "Heading", nullptr));
        spinIcebergHeading->setSuffix(QCoreApplication::translate("MainWindow", " deg", nullptr));
        groupTrackMap->setTitle(QCoreApplication::translate("MainWindow", "Map of Iceberg and Oil Rigs", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tablePlatformThreats->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Platform", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tablePlatformThreats->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Lat", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tablePlatformThreats->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Lon", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tablePlatformThreats->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Water m", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tablePlatformThreats->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Closest NM", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tablePlatformThreats->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Surface", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tablePlatformThreats->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "Subsea", nullptr));
        groupJudgeSummary->setTitle(QCoreApplication::translate("MainWindow", "Judge Notes / Outline", nullptr));
        txtJudgeSummary->setPlaceholderText(QCoreApplication::translate("MainWindow", "Auto-filled from the iceberg data. Edit here before reporting to the judge.", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Boreal Sea Star", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Jonah Crab", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "European Green Crab", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Rock Crab", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "%", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Western Atlantic Hairy Hermit Crab", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Acadian Hermit Crab", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Daisy Brittle Star", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Snow Crab", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Spiny Sunstar", nullptr));
        pushButtonCalcPercent->setText(QCoreApplication::translate("MainWindow", "Calculate Percentage", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "#", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Sea Urchin", nullptr));
        homePageButton_4->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Species Name", nullptr));
        homePageButton_5->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        floatTitleLabel->setText(QCoreApplication::translate("MainWindow", "Float Page", nullptr));
        floatInstructionLabel->setText(QString());
#if QT_CONFIG(tooltip)
        floatPortSpin->setToolTip(QCoreApplication::translate("MainWindow", "UDP port used by the float radio/receiver bridge.", nullptr));
#endif // QT_CONFIG(tooltip)
        floatPortSpin->setPrefix(QCoreApplication::translate("MainWindow", "UDP ", nullptr));
        btnFloatStartReceiver->setText(QCoreApplication::translate("MainWindow", "Start Receiver", nullptr));
        btnFloatStopReceiver->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        btnFloatImportPackets->setText(QCoreApplication::translate("MainWindow", "Import Packets", nullptr));
        btnFloatAddPackets->setText(QCoreApplication::translate("MainWindow", "Add Pasted Packets", nullptr));
        btnFloatLoadSample->setText(QCoreApplication::translate("MainWindow", "Load Sample", nullptr));
        btnFloatClear->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        floatRxStatusLabel->setText(QCoreApplication::translate("MainWindow", "Receiver idle", nullptr));
        floatBottomOffsetLabel->setText(QCoreApplication::translate("MainWindow", "Depth sensor above float bottom:", nullptr));
#if QT_CONFIG(tooltip)
        spinFloatBottomOffset->setToolTip(QCoreApplication::translate("MainWindow", "Used to adjust the 2.5 m bottom-of-float scoring range.", nullptr));
#endif // QT_CONFIG(tooltip)
        spinFloatBottomOffset->setSuffix(QCoreApplication::translate("MainWindow", " cm", nullptr));
        floatTopOffsetLabel->setText(QCoreApplication::translate("MainWindow", "Depth sensor below float top:", nullptr));
#if QT_CONFIG(tooltip)
        spinFloatTopOffset->setToolTip(QCoreApplication::translate("MainWindow", "Used to adjust the 40 cm top-of-float scoring range.", nullptr));
#endif // QT_CONFIG(tooltip)
        spinFloatTopOffset->setSuffix(QCoreApplication::translate("MainWindow", " cm", nullptr));
        floatPacketInputLabel->setText(QCoreApplication::translate("MainWindow", "Packet input / import preview", nullptr));
        txtFloatPacketInput->setPlaceholderText(QCoreApplication::translate("MainWindow", "Paste packets one per line. Example: EX01 1:51:42 UTC 9.8 kpa 1.00 meters", nullptr));
        floatPacketTableLabel->setText(QCoreApplication::translate("MainWindow", "Parsed packets to show the judge", nullptr));
        floatGraphLabel->setText(QCoreApplication::translate("MainWindow", "Depth and pressure over time", nullptr));
        homePageButton_6->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
