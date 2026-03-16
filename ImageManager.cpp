#include "ImageManager.h"
#include <QProcess>

void ImageManager::extractFramesFromVideo(const QString& videoPath, int everyNthFrame) {
    QProcess* ffmpeg = new QProcess(this);
    QString outputPattern = m_imageDir.filePath("frame_%04d.jpg");

    // Extract every Nth frame
    QString filter = QString("select=not(mod(n\\,%1))").arg(everyNthFrame);

    ffmpeg->start("ffmpeg", {
                                "-i", videoPath,
                                "-vf", filter,
                                "-vsync", "vfn",
                                "-q:v", "2",          // high quality JPEG
                                outputPattern
                            });

    connect(ffmpeg, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            [this, ffmpeg](int exitCode, QProcess::ExitStatus) {
                ffmpeg->deleteLater();
                if (exitCode == 0) {
                    emit imagesUpdated(imageCount());
                }
            });
}
