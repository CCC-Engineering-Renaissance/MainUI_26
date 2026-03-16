// ImageManager.h
#pragma once
#include <QObject>
#include <QStringList>
#include <QDir>

class ImageManager : public QObject {
    Q_OBJECT
public:
    explicit ImageManager(const QString& imageDir, QObject* parent = nullptr);

    void importImages(const QStringList& filePaths);
    void importFromDirectory(const QString& sourceDir);
    void extractFramesFromVideo(const QString& videoPath, int everyNthFrame = 10);
    QStringList imageList() const;
    int imageCount() const;

signals:
    void imagesUpdated(int count);

private:
    QDir m_imageDir;
};
