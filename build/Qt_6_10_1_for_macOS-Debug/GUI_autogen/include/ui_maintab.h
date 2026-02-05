/********************************************************************************
** Form generated from reading UI file 'maintab.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINTAB_H
#define UI_MAINTAB_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainTab
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *cameraFeedPushButton;
    QPushButton *photospherePushButton;
    QPushButton *icebergPushButton;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *floatPushButton;
    QPushButton *ednaPushButton;
    QSpacerItem *horizontalSpacer_2;
    QWidget *page_3;
    QWidget *page_2;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainTab)
    {
        if (MainTab->objectName().isEmpty())
            MainTab->setObjectName("MainTab");
        MainTab->resize(839, 662);
        centralwidget = new QWidget(MainTab);
        centralwidget->setObjectName("centralwidget");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(10, 0, 821, 621));
        page = new QWidget();
        page->setObjectName("page");
        widget = new QWidget(page);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(70, 60, 692, 292));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        cameraFeedPushButton = new QPushButton(widget);
        cameraFeedPushButton->setObjectName("cameraFeedPushButton");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cameraFeedPushButton->sizePolicy().hasHeightForWidth());
        cameraFeedPushButton->setSizePolicy(sizePolicy);
        cameraFeedPushButton->setMinimumSize(QSize(220, 140));
        cameraFeedPushButton->setMaximumSize(QSize(220, 140));
        cameraFeedPushButton->setBaseSize(QSize(220, 100));
        cameraFeedPushButton->setAutoFillBackground(true);
        cameraFeedPushButton->setStyleSheet(QString::fromUtf8("font: 14pt \"Comic Sans MS\";"));
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::MediaRecord));
        cameraFeedPushButton->setIcon(icon);

        horizontalLayout->addWidget(cameraFeedPushButton);

        photospherePushButton = new QPushButton(widget);
        photospherePushButton->setObjectName("photospherePushButton");
        sizePolicy.setHeightForWidth(photospherePushButton->sizePolicy().hasHeightForWidth());
        photospherePushButton->setSizePolicy(sizePolicy);
        photospherePushButton->setMinimumSize(QSize(220, 140));
        photospherePushButton->setMaximumSize(QSize(220, 140));
        photospherePushButton->setBaseSize(QSize(220, 100));
        photospherePushButton->setAutoFillBackground(true);
        photospherePushButton->setStyleSheet(QString::fromUtf8("font: 14pt \"Comic Sans MS\";"));
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::CameraVideo));
        photospherePushButton->setIcon(icon1);

        horizontalLayout->addWidget(photospherePushButton);

        icebergPushButton = new QPushButton(widget);
        icebergPushButton->setObjectName("icebergPushButton");
        sizePolicy.setHeightForWidth(icebergPushButton->sizePolicy().hasHeightForWidth());
        icebergPushButton->setSizePolicy(sizePolicy);
        icebergPushButton->setMinimumSize(QSize(220, 140));
        icebergPushButton->setMaximumSize(QSize(220, 140));
        icebergPushButton->setBaseSize(QSize(220, 100));
        icebergPushButton->setAutoFillBackground(true);
        icebergPushButton->setStyleSheet(QString::fromUtf8("\n"
"font: 14pt \"Comic Sans MS\";"));
        QIcon icon2(QIcon::fromTheme(QIcon::ThemeIcon::SystemSearch));
        icebergPushButton->setIcon(icon2);

        horizontalLayout->addWidget(icebergPushButton);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        floatPushButton = new QPushButton(widget);
        floatPushButton->setObjectName("floatPushButton");
        sizePolicy.setHeightForWidth(floatPushButton->sizePolicy().hasHeightForWidth());
        floatPushButton->setSizePolicy(sizePolicy);
        floatPushButton->setMinimumSize(QSize(220, 140));
        floatPushButton->setMaximumSize(QSize(220, 140));
        floatPushButton->setBaseSize(QSize(220, 100));
        floatPushButton->setAutoFillBackground(true);
        floatPushButton->setStyleSheet(QString::fromUtf8("\n"
"font: 14pt \"Comic Sans MS\";"));
        QIcon icon3(QIcon::fromTheme(QIcon::ThemeIcon::SoftwareUpdateAvailable));
        floatPushButton->setIcon(icon3);

        horizontalLayout_2->addWidget(floatPushButton);

        ednaPushButton = new QPushButton(widget);
        ednaPushButton->setObjectName("ednaPushButton");
        sizePolicy.setHeightForWidth(ednaPushButton->sizePolicy().hasHeightForWidth());
        ednaPushButton->setSizePolicy(sizePolicy);
        ednaPushButton->setMinimumSize(QSize(220, 140));
        ednaPushButton->setMaximumSize(QSize(220, 140));
        ednaPushButton->setBaseSize(QSize(220, 63));
        ednaPushButton->setAutoFillBackground(true);
        ednaPushButton->setStyleSheet(QString::fromUtf8("\n"
"font: 14pt \"Comic Sans MS\";"));
        QIcon icon4(QIcon::fromTheme(QIcon::ThemeIcon::MediaFlash));
        ednaPushButton->setIcon(icon4);

        horizontalLayout_2->addWidget(ednaPushButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        stackedWidget->addWidget(page);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        stackedWidget->addWidget(page_3);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidget->addWidget(page_2);
        MainTab->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainTab);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 839, 30));
        menubar->setDefaultUp(true);
        MainTab->setMenuBar(menubar);

        retranslateUi(MainTab);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainTab);
    } // setupUi

    void retranslateUi(QMainWindow *MainTab)
    {
        MainTab->setWindowTitle(QCoreApplication::translate("MainTab", "MainTab", nullptr));
        cameraFeedPushButton->setText(QCoreApplication::translate("MainTab", "Camera Feed / Image Recon", nullptr));
        photospherePushButton->setText(QCoreApplication::translate("MainTab", "Photosphere / 3D Modeling", nullptr));
        icebergPushButton->setText(QCoreApplication::translate("MainTab", "Iceberg Data Analysis", nullptr));
        floatPushButton->setText(QCoreApplication::translate("MainTab", "Float", nullptr));
        ednaPushButton->setText(QCoreApplication::translate("MainTab", "eDNA Sample Analysis", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainTab: public Ui_MainTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINTAB_H
