#include "mainwindow.h"

#include <QApplication>
#include <QColor>
#include <QPalette>
#include <QSurfaceFormat>

int main(int argc, char *argv[])
{
    QSurfaceFormat fmt;
    fmt.setVersion(3, 3);
    fmt.setProfile(QSurfaceFormat::CoreProfile);
    fmt.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(fmt);

    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("MATE-ROV");
    QCoreApplication::setApplicationName("MainUI_26");

#ifdef Q_OS_LINUX
    a.setStyle("Fusion");

    QPalette dark;
    dark.setColor(QPalette::Window,          QColor(0x0d, 0x1b, 0x2a));
    dark.setColor(QPalette::WindowText,      Qt::white);
    dark.setColor(QPalette::Base,            QColor(0x10, 0x1e, 0x2f));
    dark.setColor(QPalette::AlternateBase,   QColor(0x16, 0x24, 0x36));
    dark.setColor(QPalette::Text,            Qt::white);
    dark.setColor(QPalette::Button,          QColor(0x16, 0x24, 0x36));
    dark.setColor(QPalette::ButtonText,      Qt::white);
    dark.setColor(QPalette::BrightText,      QColor(0x00, 0xcc, 0xff));
    dark.setColor(QPalette::Highlight,       QColor(0x2c, 0xb5, 0xde));
    dark.setColor(QPalette::HighlightedText, Qt::white);
    dark.setColor(QPalette::ToolTipBase,     QColor(0x16, 0x24, 0x36));
    dark.setColor(QPalette::ToolTipText,     Qt::white);
    dark.setColor(QPalette::Link,            QColor(0x2c, 0xb5, 0xde));
    dark.setColor(QPalette::Disabled, QPalette::ButtonText, QColor(0x80, 0x80, 0x80));
    dark.setColor(QPalette::Disabled, QPalette::Text,       QColor(0x80, 0x80, 0x80));
    a.setPalette(dark);
#endif

    MainWindow w;
    w.show();
    return a.exec();
}
