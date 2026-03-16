#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector3D>
#include <QVector>
#include <QMouseEvent>
#include <QWheelEvent>

class ModelViewer : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit ModelViewer(QWidget *parent = nullptr);
    ~ModelViewer();
    void loadPLY(const QString &path);
    void clear();
    void resetCamera();
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
private:
    struct PointCloudData {
        QVector<float> vertexData;
        int vertexCount = 0;
        QVector3D center;
        float maxExtent = 1.0f;
    };
    PointCloudData parsePLY(const QString &path);
    void uploadToGPU(const PointCloudData &data);
    QOpenGLShaderProgram *m_shader = nullptr;
    QOpenGLBuffer m_vbo;
    QOpenGLVertexArrayObject m_vao;
    int m_vertexCount = 0;
    bool m_dataLoaded = false;
    QQuaternion m_rotation;
    float m_distance = 5.0f;
    QVector3D m_panOffset{0, 0, 0};
    float m_pointSize = 3.0f;
    QPoint m_lastMousePos;
    Qt::MouseButton m_activeButton = Qt::NoButton;
    QMatrix4x4 m_projection;
};
