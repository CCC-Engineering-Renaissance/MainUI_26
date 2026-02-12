#ifndef COLMAPUTILS_H
#define COLMAPUTILS_H

#include <QString>
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QDebug>

// Declare the function as inline or static so it doesn't cause linking errors
inline QString getColmapPath() {
    QDir dir(QCoreApplication::applicationDirPath());

#ifdef Q_OS_MAC
    dir.cdUp();
    dir.cd("Resources");
    dir.cd("colmap");
    QString binary = dir.filePath("colmap");
#elif defined(Q_OS_WIN)
    dir.cd("tools"); // Ensure you created this folder structure
    dir.cd("colmap");
    QString binary = dir.filePath("colmap.exe");
#else
    dir.cd("tools");
    dir.cd("colmap");
    QString binary = dir.filePath("colmap");
#endif

    if (!QFile::exists(binary)) {
        qWarning() << "COLMAP binary not found at:" << binary;
        return QString(); // Return empty string on failure
    }

    return binary;
}

#endif // COLMAPUTILS_H
