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

class QPainter;

class ModelViewer : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit ModelViewer(QWidget *parent = nullptr);
    ~ModelViewer();
    void loadPLY(const QString &path);
    void clear();
    void resetCamera();

    // Scale tool: enterScaleMode() → user clicks two points → scalePointsPicked() →
    // caller shows dialog → applyScale(real metres)
    void enterScaleMode();
    void enterMeasureMode();
    void exitPickMode();
    void applyScale(float realWorldMeters);
    float scaleFactor() const { return m_scaleFactor; }

signals:
    // Emitted when the second scale reference point is picked.
    // measuredModelDist is the distance in model (arbitrary) units.
    void scalePointsPicked(float measuredModelDist);
    // Emitted after applyScale() with the real-world AABB extents.
    void scaleApplied(float widthM, float heightM, float depthM);
    // Emitted after a freehand measurement is completed.
    void measurementReady(float totalM, float dxM, float dyM, float dzM);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    enum class PickMode { None, ScaleFirst, ScaleSecond, MeasureFirst, MeasureSecond };

    struct PointCloudData {
        QVector<float> vertexData; // interleaved xyz rgb, centred at origin
        int vertexCount = 0;
        QVector3D center;
        float maxExtent = 1.0f;
        float extentX = 0, extentY = 0, extentZ = 0;
    };

    PointCloudData parsePLY(const QString &path);
    void uploadToGPU(const PointCloudData &data);
    void buildAABBLines();
    void drawHUD(QPainter &painter);
    QVector3D pickNearestPoint(QPoint mousePos);
    QPoint projectToScreen(const QVector3D &pt) const;
    QMatrix4x4 buildMVP() const;

    // GL — point cloud
    QOpenGLShaderProgram *m_shader = nullptr;
    QOpenGLBuffer         m_vbo;
    QOpenGLVertexArrayObject m_vao;

    // GL — AABB wireframe
    QOpenGLBuffer            m_lineVbo;
    QOpenGLVertexArrayObject m_lineVao;
    int m_lineVertexCount = 0;

    int  m_vertexCount = 0;
    bool m_dataLoaded  = false;

    // Camera
    QQuaternion m_rotation;
    float       m_distance  = 5.0f;
    QVector3D   m_panOffset {0, 0, 0};
    float       m_pointSize = 3.0f;
    QPoint      m_lastMousePos;
    QMatrix4x4  m_projection;

    // Pick state
    PickMode  m_pickMode        = PickMode::None;
    QVector3D m_pickedA, m_pickedB;
    float     m_measuredPickDist = 0;

    // Scale
    float m_scaleFactor = 1.0f;
    bool  m_hasScale    = false;
    float m_extentX = 0, m_extentY = 0, m_extentZ = 0;

    // Measurement result
    bool      m_hasMeasure    = false;
    float     m_measureTotal  = 0;
    QVector3D m_measureDelta;

    // CPU vertex copy for screen-space picking
    QVector<float> m_cpuVerts;
};
