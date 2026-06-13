#include "modelviewer.h"
#include <QDebug>
#include <QFile>
#include <QPainter>
#include <QTextStream>
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <limits>

// ─── Shaders ────────────────────────────────────────────────────────────────

static const char *vertexShaderSource = R"(
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
uniform mat4  mvp;
uniform float pointSize;
out vec3 vColor;
void main() {
    gl_Position  = mvp * vec4(aPos, 1.0);
    gl_PointSize = pointSize;
    vColor = aColor;
}
)";

// roundPoints=true → circular point sprites; false → solid (used for lines)
static const char *fragmentShaderSource = R"(
#version 330 core
in  vec3 vColor;
out vec4 FragColor;
uniform bool roundPoints;
void main() {
    if (roundPoints) {
        vec2 coord = gl_PointCoord - vec2(0.5);
        if (dot(coord, coord) > 0.25) discard;
    }
    FragColor = vec4(vColor, 1.0);
}
)";

// ─── Construction / destruction ──────────────────────────────────────────────

ModelViewer::ModelViewer(QWidget *parent)
    : QOpenGLWidget(parent)
    , m_vbo(QOpenGLBuffer::VertexBuffer)
    , m_lineVbo(QOpenGLBuffer::VertexBuffer)
{
    m_rotation = QQuaternion::fromEulerAngles(25.0f, -45.0f, 0.0f);
    setMinimumSize(200, 200);
    setFocusPolicy(Qt::StrongFocus);
}

ModelViewer::~ModelViewer()
{
    makeCurrent();
    m_vao.destroy();
    m_vbo.destroy();
    m_lineVao.destroy();
    m_lineVbo.destroy();
    delete m_shader;
    doneCurrent();
}

// ─── GL lifecycle ────────────────────────────────────────────────────────────

void ModelViewer::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.12f, 0.12f, 0.14f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_PROGRAM_POINT_SIZE);

    m_shader = new QOpenGLShaderProgram(this);
    if (!m_shader->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource))
        qWarning() << "ModelViewer: vertex shader error:" << m_shader->log();
    if (!m_shader->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource))
        qWarning() << "ModelViewer: fragment shader error:" << m_shader->log();
    if (!m_shader->link())
        qWarning() << "ModelViewer: shader link error:" << m_shader->log();
    else
        qDebug() << "ModelViewer: shader OK. GL:"
                 << reinterpret_cast<const char *>(glGetString(GL_VERSION));
}

void ModelViewer::resizeGL(int w, int h)
{
    m_projection.setToIdentity();
    m_projection.perspective(45.0f, float(w) / float(h > 0 ? h : 1), 0.01f, 1000.0f);
}

QMatrix4x4 ModelViewer::buildMVP() const
{
    QMatrix4x4 view;
    view.translate(m_panOffset.x(), m_panOffset.y(), -m_distance);
    view.rotate(m_rotation);
    // Scale factor is a display multiplier applied to measurement values only;
    // the GL geometry stays in model-space units so picking math stays simple.
    return m_projection * view;
}

// ─── Rendering ───────────────────────────────────────────────────────────────

void ModelViewer::paintGL()
{
    // QPainter (used for the 2D overlay at the end of this function) modifies
    // GL state and does not fully restore it.  Re-establish everything we need
    // explicitly at the top of every frame so the next paint starts clean.
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
    glEnable(GL_PROGRAM_POINT_SIZE);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    QMatrix4x4 mvp = buildMVP();

    // Point cloud
    if (m_dataLoaded && m_vertexCount > 0) {
        m_shader->bind();
        m_shader->setUniformValue("mvp", mvp);
        m_shader->setUniformValue("pointSize", m_pointSize);
        m_shader->setUniformValue("roundPoints", true);
        m_vao.bind();
        glDrawArrays(GL_POINTS, 0, m_vertexCount);
        m_vao.release();
        m_shader->release();
    }

    // AABB wireframe
    if (m_dataLoaded && m_lineVertexCount > 0) {
        m_shader->bind();
        m_shader->setUniformValue("mvp", mvp);
        m_shader->setUniformValue("pointSize", 1.0f);
        m_shader->setUniformValue("roundPoints", false);
        m_lineVao.bind();
        glDrawArrays(GL_LINES, 0, m_lineVertexCount);
        m_lineVao.release();
        m_shader->release();
    }

    // 2D overlay via QPainter
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Crosshair on first picked point when waiting for second click
    bool waitingSecond = (m_pickMode == PickMode::ScaleSecond
                          || m_pickMode == PickMode::MeasureSecond);
    if (waitingSecond) {
        QPoint sa = projectToScreen(m_pickedA);
        painter.setPen(QPen(QColor(255, 200, 0), 2));
        painter.setBrush(Qt::NoBrush);
        painter.drawEllipse(sa, 7, 7);
        painter.drawLine(sa.x() - 13, sa.y(), sa.x() + 13, sa.y());
        painter.drawLine(sa.x(), sa.y() - 13, sa.x(), sa.y() + 13);
    }

    // Dashed line + endpoint dots for completed measurement
    if (m_hasMeasure) {
        QPoint sa = projectToScreen(m_pickedA);
        QPoint sb = projectToScreen(m_pickedB);
        painter.setPen(QPen(QColor(80, 220, 80), 2, Qt::DashLine));
        painter.drawLine(sa, sb);
        painter.setPen(QPen(QColor(80, 220, 80), 2));
        painter.setBrush(QColor(80, 220, 80, 80));
        painter.drawEllipse(sa, 6, 6);
        painter.drawEllipse(sb, 6, 6);
    }

    drawHUD(painter);
    painter.end();
}

void ModelViewer::drawHUD(QPainter &p)
{
    QFont font("Monospace", 10);
    p.setFont(font);
    QFontMetrics fm(font);
    int lh = fm.height() + 3;
    int asc = fm.ascent();

    // Helper: dark-background text box
    auto drawBox = [&](int x, int y, const QStringList &lines, QColor bg) {
        int bw = 0;
        for (const auto &l : lines)
            bw = qMax(bw, fm.horizontalAdvance(l));
        bw += 14;
        int bh = lines.size() * lh + 10;
        p.fillRect(x, y, bw, bh, bg);
        p.setPen(Qt::white);
        for (int i = 0; i < lines.size(); i++)
            p.drawText(x + 7, y + 5 + i * lh + asc, lines[i]);
        return bh;
    };

    // Mode instructions — top-left, blue
    QStringList modeLines;
    switch (m_pickMode) {
    case PickMode::ScaleFirst:
        modeLines << "SET SCALE" << "Click first reference point";
        break;
    case PickMode::ScaleSecond:
        modeLines << "SET SCALE" << "Click second reference point";
        break;
    case PickMode::MeasureFirst:
        modeLines << "MEASURE" << "Click first point";
        break;
    case PickMode::MeasureSecond:
        modeLines << "MEASURE" << "Click second point";
        break;
    default:
        break;
    }
    if (!modeLines.isEmpty())
        drawBox(8, 8, modeLines, QColor(30, 60, 130, 210));

    // AABB dimensions — top-right, shown whenever scale is set
    if (m_hasScale && m_dataLoaded) {
        auto fmtM = [](float v) { return QString::number(v, 'f', 3) + " m"; };
        QStringList dims;
        dims << QString("W: %1").arg(fmtM(m_extentX * m_scaleFactor));
        dims << QString("H: %1").arg(fmtM(m_extentY * m_scaleFactor));
        dims << QString("D: %1").arg(fmtM(m_extentZ * m_scaleFactor));
        int bw = 0;
        for (const auto &l : dims)
            bw = qMax(bw, fm.horizontalAdvance(l));
        bw += 14;
        drawBox(width() - bw - 8, 8, dims, QColor(0, 0, 0, 170));
    }

    // Measurement result — bottom-left, green
    if (m_hasMeasure) {
        auto fmtM = [](float v) { return QString::number(v, 'f', 3) + " m"; };
        QStringList meas;
        meas << QString("A \u2192 B:  %1").arg(fmtM(m_measureTotal));
        meas << QString("\u0394X:     %1").arg(fmtM(qAbs(m_measureDelta.x())));
        meas << QString("\u0394Y:     %1").arg(fmtM(qAbs(m_measureDelta.y())));
        meas << QString("\u0394Z:     %1").arg(fmtM(qAbs(m_measureDelta.z())));
        int bh = meas.size() * lh + 10;
        drawBox(8, height() - bh - 8, meas, QColor(20, 70, 25, 210));
    }
}

// ─── Mouse input ─────────────────────────────────────────────────────────────

void ModelViewer::mousePressEvent(QMouseEvent *event)
{
    // In pick mode, left-click picks a point instead of starting an orbit.
    if (m_pickMode != PickMode::None && event->button() == Qt::LeftButton) {
        QVector3D picked = pickNearestPoint(event->pos());

        switch (m_pickMode) {
        case PickMode::ScaleFirst:
            m_pickedA = picked;
            m_pickMode = PickMode::ScaleSecond;
            break;

        case PickMode::ScaleSecond:
            m_pickedB = picked;
            m_measuredPickDist = (m_pickedB - m_pickedA).length();
            m_pickMode = PickMode::None;
            setCursor(Qt::ArrowCursor);
            if (m_measuredPickDist > 0)
                emit scalePointsPicked(m_measuredPickDist);
            break;

        case PickMode::MeasureFirst:
            m_pickedA = picked;
            m_pickMode = PickMode::MeasureSecond;
            break;

        case PickMode::MeasureSecond: {
            m_pickedB = picked;
            m_pickMode = PickMode::None;
            setCursor(Qt::ArrowCursor);
            QVector3D delta = (m_pickedB - m_pickedA) * m_scaleFactor;
            m_measureDelta = delta;
            m_measureTotal = delta.length();
            m_hasMeasure = true;
            emit measurementReady(m_measureTotal, qAbs(delta.x()), qAbs(delta.y()), qAbs(delta.z()));
            break;
        }
        default:
            break;
        }
        update();
        return;
    }

    m_lastMousePos = event->pos();
}

void ModelViewer::mouseMoveEvent(QMouseEvent *event)
{
    // Keep lastMousePos updated even in pick mode so orbit snaps correctly on exit.
    int dx = event->pos().x() - m_lastMousePos.x();
    int dy = event->pos().y() - m_lastMousePos.y();
    m_lastMousePos = event->pos();

    if (m_pickMode != PickMode::None)
        return; // suppress orbit/pan in pick mode

    if (event->buttons() & Qt::LeftButton) {
        m_rotation = QQuaternion::fromAxisAndAngle(0, 1, 0, dx * 0.5f) * m_rotation;
        m_rotation = m_rotation * QQuaternion::fromAxisAndAngle(1, 0, 0, dy * 0.5f);
        update();
    } else if (event->buttons() & Qt::RightButton) {
        float panSpeed = m_distance * 0.002f;
        m_panOffset.setX(m_panOffset.x() + dx * panSpeed);
        m_panOffset.setY(m_panOffset.y() - dy * panSpeed);
        update();
    } else if (event->buttons() & Qt::MiddleButton) {
        m_distance *= 1.0f + dy * 0.005f;
        m_distance = qMax(0.01f, m_distance);
        update();
    }
}

void ModelViewer::wheelEvent(QWheelEvent *event)
{
    float delta = event->angleDelta().y() / 120.0f;
    m_distance *= (1.0f - delta * 0.1f);
    m_distance = qMax(0.01f, m_distance);
    update();
}

// ─── Camera / state ──────────────────────────────────────────────────────────

void ModelViewer::resetCamera()
{
    m_rotation = QQuaternion::fromEulerAngles(25.0f, -45.0f, 0.0f);
    m_distance = 5.0f;
    m_panOffset = QVector3D(0, 0, 0);
    update();
}

void ModelViewer::clear()
{
    makeCurrent();
    m_dataLoaded = false;
    m_vertexCount = 0;
    m_lineVertexCount = 0;
    m_cpuVerts.clear();
    doneCurrent();

    m_hasScale = false;
    m_hasMeasure = false;
    m_scaleFactor = 1.0f;
    m_pickMode = PickMode::None;
    setCursor(Qt::ArrowCursor);
    update();
}

// ─── Scale / measurement tools ───────────────────────────────────────────────

void ModelViewer::enterScaleMode()
{
    m_pickMode = PickMode::ScaleFirst;
    m_hasMeasure = false;
    setCursor(Qt::CrossCursor);
    update();
}

void ModelViewer::enterMeasureMode()
{
    m_pickMode = PickMode::MeasureFirst;
    m_hasMeasure = false;
    setCursor(Qt::CrossCursor);
    update();
}

void ModelViewer::exitPickMode()
{
    m_pickMode = PickMode::None;
    setCursor(Qt::ArrowCursor);
    update();
}

void ModelViewer::applyScale(float realWorldMeters)
{
    if (m_measuredPickDist <= 0)
        return;
    m_scaleFactor = realWorldMeters / m_measuredPickDist;
    m_hasScale = true;
    update();
    emit scaleApplied(m_extentX * m_scaleFactor,
                      m_extentY * m_scaleFactor,
                      m_extentZ * m_scaleFactor);
}

// ─── Picking ─────────────────────────────────────────────────────────────────

QVector3D ModelViewer::pickNearestPoint(QPoint mousePos)
{
    QMatrix4x4 mvp = buildMVP();
    float sw = width(), sh = height();
    float bestDist2 = 1e30f;
    QVector3D bestPt;

    int n = m_cpuVerts.size() / 6;
    for (int i = 0; i < n; i++) {
        QVector3D pt(m_cpuVerts[i * 6], m_cpuVerts[i * 6 + 1], m_cpuVerts[i * 6 + 2]);
        QVector4D clip = mvp * QVector4D(pt, 1.0f);
        if (clip.w() <= 0)
            continue;
        float inv = 1.0f / clip.w();
        float sx = (clip.x() * inv + 1.0f) * 0.5f * sw;
        float sy = (1.0f - clip.y() * inv) * 0.5f * sh;
        float dx = sx - mousePos.x(), dy = sy - mousePos.y();
        float d2 = dx * dx + dy * dy;
        if (d2 < bestDist2) {
            bestDist2 = d2;
            bestPt = pt;
        }
    }
    return bestPt;
}

QPoint ModelViewer::projectToScreen(const QVector3D &pt) const
{
    QMatrix4x4 mvp = buildMVP();
    QVector4D clip = mvp * QVector4D(pt, 1.0f);
    if (clip.w() <= 0)
        return QPoint(-100, -100);
    float inv = 1.0f / clip.w();
    float sx = (clip.x() * inv + 1.0f) * 0.5f * width();
    float sy = (1.0f - clip.y() * inv) * 0.5f * height();
    return QPoint(qRound(sx), qRound(sy));
}

// ─── PLY loading ─────────────────────────────────────────────────────────────

void ModelViewer::loadPLY(const QString &path)
{
    PointCloudData data = parsePLY(path);
    if (data.vertexCount == 0) {
        qWarning() << "No points:" << path;
        return;
    }
    qDebug() << "Loaded" << data.vertexCount << "points, extent:" << data.maxExtent;
    makeCurrent();
    uploadToGPU(data);
    doneCurrent();
    m_distance = data.maxExtent * 2.0f;
    m_panOffset = QVector3D(0, 0, 0);
    m_rotation = QQuaternion::fromEulerAngles(25.0f, -45.0f, 0.0f);
    m_pointSize = qBound(2.0f, data.maxExtent * 1.5f, 8.0f);
    update();
}

void ModelViewer::uploadToGPU(const PointCloudData &data)
{
    m_extentX = data.extentX;
    m_extentY = data.extentY;
    m_extentZ = data.extentZ;
    m_cpuVerts = data.vertexData; // keep for screen-space picking

    if (!m_vao.isCreated())
        m_vao.create();
    if (!m_vbo.isCreated())
        m_vbo.create();

    m_vao.bind();
    m_vbo.bind();
    m_vbo.allocate(data.vertexData.constData(), data.vertexData.size() * sizeof(float));
    int stride = 6 * sizeof(float);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *) 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void *) (3 * sizeof(float)));
    m_vbo.release();
    m_vao.release();

    m_vertexCount = data.vertexCount;
    m_dataLoaded = true;

    buildAABBLines();
}

void ModelViewer::buildAABBLines()
{
    float hx = m_extentX * 0.5f;
    float hy = m_extentY * 0.5f;
    float hz = m_extentZ * 0.5f;
    float r = 0.3f, g = 0.6f, b = 1.0f; // light blue

    QVector<float> v;
    v.reserve(24 * 6);
    auto add = [&](float x, float y, float z) { v << x << y << z << r << g << b; };

    // Bottom face
    add(-hx, -hy, -hz);
    add(+hx, -hy, -hz);
    add(+hx, -hy, -hz);
    add(+hx, -hy, +hz);
    add(+hx, -hy, +hz);
    add(-hx, -hy, +hz);
    add(-hx, -hy, +hz);
    add(-hx, -hy, -hz);
    // Top face
    add(-hx, +hy, -hz);
    add(+hx, +hy, -hz);
    add(+hx, +hy, -hz);
    add(+hx, +hy, +hz);
    add(+hx, +hy, +hz);
    add(-hx, +hy, +hz);
    add(-hx, +hy, +hz);
    add(-hx, +hy, -hz);
    // Verticals
    add(-hx, -hy, -hz);
    add(-hx, +hy, -hz);
    add(+hx, -hy, -hz);
    add(+hx, +hy, -hz);
    add(+hx, -hy, +hz);
    add(+hx, +hy, +hz);
    add(-hx, -hy, +hz);
    add(-hx, +hy, +hz);

    if (!m_lineVao.isCreated())
        m_lineVao.create();
    if (!m_lineVbo.isCreated())
        m_lineVbo.create();

    m_lineVao.bind();
    m_lineVbo.bind();
    m_lineVbo.allocate(v.constData(), v.size() * sizeof(float));
    int stride = 6 * sizeof(float);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *) 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void *) (3 * sizeof(float)));
    m_lineVbo.release();
    m_lineVao.release();

    m_lineVertexCount = 24;
}

// ─── PLY parser (unchanged logic, added per-axis extents) ────────────────────

ModelViewer::PointCloudData ModelViewer::parsePLY(const QString &path)
{
    PointCloudData result;
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
        return result;

    bool isBinary = false;
    int vertexCount = 0;
    struct PropInfo
    {
        QString name, type, listCountType, listElemType;
    };
    QVector<PropInfo> properties;
    bool inVertex = false;

    while (true) {
        QByteArray lb = file.readLine();
        QString line = QString::fromUtf8(lb).trimmed();
        if (line == "end_header")
            break;
        if (line.startsWith("format") && line.contains("binary"))
            isBinary = true;
        else if (line.startsWith("element vertex")) {
            vertexCount = line.split(' ').last().toInt();
            inVertex = true;
        } else if (line.startsWith("element") && !line.startsWith("element vertex")) {
            inVertex = false;
        } else if (line.startsWith("property") && inVertex) {
            QStringList p = line.split(' ');
            if (p.size() >= 3) {
                if (p[1] == "list" && p.size() >= 5)
                    properties.append({p.last(), "list", p[2], p[3]});
                else
                    properties.append({p.last(), p[1], {}, {}});
            }
        }
    }
    if (vertexCount == 0)
        return result;

    int xI = -1, yI = -1, zI = -1, rI = -1, gI = -1, bI = -1;
    for (int i = 0; i < properties.size(); i++) {
        const QString &n = properties[i].name;
        if (n == "x")
            xI = i;
        else if (n == "y")
            yI = i;
        else if (n == "z")
            zI = i;
        else if (n == "red")
            rI = i;
        else if (n == "green")
            gI = i;
        else if (n == "blue")
            bI = i;
    }
    bool hasColor = (rI >= 0 && gI >= 0 && bI >= 0);

    auto tSize = [](const QString &t) -> int {
        if (t == "float" || t == "float32" || t == "int" || t == "int32" || t == "uint")
            return 4;
        if (t == "double" || t == "float64")
            return 8;
        if (t == "uchar" || t == "uint8" || t == "char" || t == "int8")
            return 1;
        if (t == "short" || t == "int16" || t == "ushort" || t == "uint16")
            return 2;
        return 4;
    };

    QVector<int> offsets(properties.size());
    int bpv = 0;
    for (int i = 0; i < properties.size(); i++) {
        offsets[i] = bpv;
        bpv += tSize(properties[i].type);
    }

    QVector<float> &V = result.vertexData;
    V.reserve(vertexCount * 6);
    float minX = 1e30f, minY = 1e30f, minZ = 1e30f, maxX = -1e30f, maxY = -1e30f, maxZ = -1e30f;

    auto readF = [&](const char *ptr, int pi) -> float {
        const char *p = ptr + offsets[pi];
        const QString &t = properties[pi].type;
        if (t == "float" || t == "float32") {
            float v;
            memcpy(&v, p, 4);
            return v;
        }
        if (t == "double" || t == "float64") {
            double v;
            memcpy(&v, p, 8);
            return (float) v;
        }
        if (t == "uchar" || t == "uint8")
            return (float) (unsigned char) (*p);
        if (t == "int" || t == "int32") {
            int32_t v;
            memcpy(&v, p, 4);
            return (float) v;
        }
        return 0.f;
    };

    auto readVal = [&](const char *p, const QString &t) -> float {
        if (t == "float" || t == "float32") {
            float v;
            memcpy(&v, p, 4);
            return v;
        }
        if (t == "double" || t == "float64") {
            double v;
            memcpy(&v, p, 8);
            return (float) v;
        }
        if (t == "uchar" || t == "uint8")
            return (float) (unsigned char) (*p);
        if (t == "int" || t == "int32") {
            int32_t v;
            memcpy(&v, p, 4);
            return (float) v;
        }
        return 0.f;
    };

    bool hasListProps = false;
    for (const auto &prop : properties)
        if (prop.type == "list") {
            hasListProps = true;
            break;
        }

    if (isBinary) {
        QByteArray all = file.readAll();
        const char *ptr = all.constData(), *end = ptr + all.size();

        if (hasListProps) {
            const char *vp = ptr;
            for (int v = 0; v < vertexCount && vp < end; v++) {
                float x = 0, y = 0, z = 0, rc = 0.8f, gc = 0.8f, bc = 0.8f;
                for (int pi = 0; pi < properties.size() && vp < end; pi++) {
                    const PropInfo &prop = properties[pi];
                    if (prop.type == "list") {
                        int cnt = (int) (unsigned char) (*vp);
                        vp += tSize(prop.listCountType);
                        vp += cnt * tSize(prop.listElemType);
                    } else {
                        float val = readVal(vp, prop.type);
                        if (pi == xI)
                            x = val;
                        else if (pi == yI)
                            y = val;
                        else if (pi == zI)
                            z = val;
                        else if (pi == rI && hasColor)
                            rc = val / 255.f;
                        else if (pi == gI && hasColor)
                            gc = val / 255.f;
                        else if (pi == bI && hasColor)
                            bc = val / 255.f;
                        vp += tSize(prop.type);
                    }
                }
                if (!std::isfinite(x) || !std::isfinite(y) || !std::isfinite(z))
                    continue;
                V << x << y << z << rc << gc << bc;
                if (x < minX)
                    minX = x;
                if (y < minY)
                    minY = y;
                if (z < minZ)
                    minZ = z;
                if (x > maxX)
                    maxX = x;
                if (y > maxY)
                    maxY = y;
                if (z > maxZ)
                    maxZ = z;
            }
        } else {
            for (int v = 0; v < vertexCount; v++) {
                const char *vp = ptr + v * bpv;
                if (vp + bpv > end)
                    break;
                float x = readF(vp, xI), y = readF(vp, yI), z = readF(vp, zI);
                if (!std::isfinite(x) || !std::isfinite(y) || !std::isfinite(z))
                    continue;
                float r = hasColor ? readF(vp, rI) / 255.f : 0.8f;
                float g = hasColor ? readF(vp, gI) / 255.f : 0.8f;
                float b = hasColor ? readF(vp, bI) / 255.f : 0.8f;
                V << x << y << z << r << g << b;
                if (x < minX)
                    minX = x;
                if (y < minY)
                    minY = y;
                if (z < minZ)
                    minZ = z;
                if (x > maxX)
                    maxX = x;
                if (y > maxY)
                    maxY = y;
                if (z > maxZ)
                    maxZ = z;
            }
        }
    } else {
        QTextStream stream(&file);
        for (int v = 0; v < vertexCount; v++) {
            QString line = stream.readLine();
            if (line.isNull())
                break;
            QStringList p = line.trimmed().split(' ', Qt::SkipEmptyParts);
            float x = p[xI].toFloat(), y = p[yI].toFloat(), z = p[zI].toFloat();
            if (!std::isfinite(x) || !std::isfinite(y) || !std::isfinite(z))
                continue;
            float r = hasColor ? p[rI].toFloat() / 255.f : 0.8f;
            float g = hasColor ? p[gI].toFloat() / 255.f : 0.8f;
            float b = hasColor ? p[bI].toFloat() / 255.f : 0.8f;
            V << x << y << z << r << g << b;
            if (x < minX)
                minX = x;
            if (y < minY)
                minY = y;
            if (z < minZ)
                minZ = z;
            if (x > maxX)
                maxX = x;
            if (y > maxY)
                maxY = y;
            if (z > maxZ)
                maxZ = z;
        }
    }
    file.close();

    QVector3D center((minX + maxX) / 2, (minY + maxY) / 2, (minZ + maxZ) / 2);
    int actualCount = V.size() / 6;
    result.extentX = maxX - minX;
    result.extentY = maxY - minY;
    result.extentZ = maxZ - minZ;
    result.maxExtent = std::max({result.extentX, result.extentY, result.extentZ});
    result.center = center;
    result.vertexCount = actualCount;

    // Centre the cloud at the origin
    for (int i = 0; i < actualCount; i++) {
        V[i * 6 + 0] -= center.x();
        V[i * 6 + 1] -= center.y();
        V[i * 6 + 2] -= center.z();
    }
    return result;
}
