#include "modelviewer.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <limits>

static const char *vertexShaderSource = R"(
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
uniform mat4 mvp;
uniform float pointSize;
out vec3 vColor;
void main() {
    gl_Position = mvp * vec4(aPos, 1.0);
    gl_PointSize = pointSize;
    vColor = aColor;
}
)";

static const char *fragmentShaderSource = R"(
#version 330 core
in vec3 vColor;
out vec4 FragColor;
void main() {
    vec2 coord = gl_PointCoord - vec2(0.5);
    if (dot(coord, coord) > 0.25) discard;
    FragColor = vec4(vColor, 1.0);
}
)";

ModelViewer::ModelViewer(QWidget *parent)
    : QOpenGLWidget(parent), m_vbo(QOpenGLBuffer::VertexBuffer) {
  m_rotation = QQuaternion::fromEulerAngles(25.0f, -45.0f, 0.0f);
  setMinimumSize(200, 200);
  setFocusPolicy(Qt::StrongFocus);
}

ModelViewer::~ModelViewer() {
  makeCurrent();
  m_vao.destroy();
  m_vbo.destroy();
  delete m_shader;
  doneCurrent();
}

void ModelViewer::initializeGL() {
  initializeOpenGLFunctions();
  glClearColor(0.12f, 0.12f, 0.14f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_PROGRAM_POINT_SIZE);
  m_shader = new QOpenGLShaderProgram(this);
  if (!m_shader->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource))
      qWarning() << "ModelViewer: vertex shader error:" << m_shader->log();
  if (!m_shader->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource))
      qWarning() << "ModelViewer: fragment shader error:" << m_shader->log();
  if (!m_shader->link())
      qWarning() << "ModelViewer: shader link error:" << m_shader->log();
  else
      qDebug() << "ModelViewer: shader compiled and linked OK. GL version:"
               << reinterpret_cast<const char*>(glGetString(GL_VERSION));
}

void ModelViewer::resizeGL(int w, int h) {
  m_projection.setToIdentity();
  m_projection.perspective(45.0f, float(w) / float(h > 0 ? h : 1), 0.01f,
                           1000.0f);
}

void ModelViewer::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if (!m_dataLoaded || m_vertexCount == 0)
    return;
  m_shader->bind();
  QMatrix4x4 view;
  // Pan in screen-space (before rotation) so dragging always moves relative to the screen.
  view.translate(m_panOffset.x(), m_panOffset.y(), -m_distance);
  view.rotate(m_rotation);
  m_shader->setUniformValue("mvp", m_projection * view);
  m_shader->setUniformValue("pointSize", m_pointSize);
  m_vao.bind();
  glDrawArrays(GL_POINTS, 0, m_vertexCount);
  m_vao.release();
  m_shader->release();
}

void ModelViewer::mousePressEvent(QMouseEvent *event) {
  m_lastMousePos = event->pos();
  m_activeButton = event->button();
}

void ModelViewer::mouseMoveEvent(QMouseEvent *event) {
  int dx = event->pos().x() - m_lastMousePos.x();
  int dy = event->pos().y() - m_lastMousePos.y();
  m_lastMousePos = event->pos();
  if (event->buttons() & Qt::LeftButton) {
    // Orbit: horizontal drag rotates around world Y, vertical around local X.
    // Applying in this order prevents gimbal lock and allows full 360° on all axes.
    m_rotation = QQuaternion::fromAxisAndAngle(0, 1, 0, dx * 0.5f) * m_rotation;
    m_rotation = m_rotation * QQuaternion::fromAxisAndAngle(1, 0, 0, dy * 0.5f);
    update();
  } else if (event->buttons() & Qt::RightButton) {
    // Pan in screen-space: right drag moves the model laterally.
    float panSpeed = m_distance * 0.002f;
    m_panOffset.setX(m_panOffset.x() + dx * panSpeed);
    m_panOffset.setY(m_panOffset.y() - dy * panSpeed);
    update();
  } else if (event->buttons() & Qt::MiddleButton) {
    // Middle-button drag zooms (same as scroll).
    m_distance *= 1.0f + dy * 0.005f;
    m_distance = qMax(0.01f, m_distance);
    update();
  }
}

void ModelViewer::wheelEvent(QWheelEvent *event) {
  float delta = event->angleDelta().y() / 120.0f;
  m_distance *= (1.0f - delta * 0.1f);
  m_distance = qMax(0.01f, m_distance);
  update();
}

void ModelViewer::resetCamera() {
  m_rotation = QQuaternion::fromEulerAngles(25.0f, -45.0f, 0.0f);
  m_distance = 5.0f;
  m_panOffset = QVector3D(0, 0, 0);
  update();
}

void ModelViewer::clear() {
  makeCurrent();
  m_dataLoaded = false;
  m_vertexCount = 0;
  doneCurrent();
  update();
}

void ModelViewer::loadPLY(const QString &path) {
  PointCloudData data = parsePLY(path);
  if (data.vertexCount == 0) {
    qWarning() << "No points:" << path;
    return;
  }
  qDebug() << "Loaded" << data.vertexCount
           << "points, extent:" << data.maxExtent;
  makeCurrent();
  uploadToGPU(data);
  doneCurrent();
  m_distance = data.maxExtent * 2.0f;
  m_panOffset = QVector3D(0, 0, 0);
  m_rotation = QQuaternion::fromEulerAngles(25.0f, -45.0f, 0.0f);
  m_pointSize = qBound(2.0f, data.maxExtent * 1.5f, 8.0f);
  update();
}

void ModelViewer::uploadToGPU(const PointCloudData &data) {
  if (!m_vao.isCreated())
    m_vao.create();
  if (!m_vbo.isCreated())
    m_vbo.create();

  m_vao.bind();
  m_vbo.bind();

  m_vbo.allocate(data.vertexData.constData(),
                 data.vertexData.size() * sizeof(float));

  int stride = 6 * sizeof(float);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride,
                        (void *)(3 * sizeof(float)));

  m_vbo.release();
  m_vao.release();

  m_vertexCount = data.vertexCount;
  m_dataLoaded = true;
}

ModelViewer::PointCloudData ModelViewer::parsePLY(const QString &path) {
  PointCloudData result;
  QFile file(path);
  if (!file.open(QIODevice::ReadOnly))
    return result;

  bool isBinary = false;
  int vertexCount = 0;
  struct PropInfo {
    QString name;
    QString type;
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
    } else if (line.startsWith("element") &&
               !line.startsWith("element vertex")) {
      inVertex = false;
    } else if (line.startsWith("property") && inVertex) {
      QStringList p = line.split(' ');
      if (p.size() >= 3)
        properties.append({p.last(), p[1]});
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
    if (t == "float" || t == "float32" || t == "int" || t == "int32" ||
        t == "uint")
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
  float minX = 1e30f, minY = 1e30f, minZ = 1e30f, maxX = -1e30f, maxY = -1e30f,
        maxZ = -1e30f;

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
      return (float)v;
    }
    if (t == "uchar" || t == "uint8") {
      return (float)(unsigned char)(*p);
    }
    if (t == "int" || t == "int32") {
      int32_t v;
      memcpy(&v, p, 4);
      return (float)v;
    }
    return 0.0f;
  };

  if (isBinary) {
    QByteArray all = file.readAll();
    const char *ptr = all.constData();
    for (int v = 0; v < vertexCount; v++) {
      const char *vp = ptr + v * bpv;
      float x = readF(vp, xI), y = readF(vp, yI), z = readF(vp, zI);
      float r = hasColor ? readF(vp, rI) / 255.0f : 0.8f;
      float g = hasColor ? readF(vp, gI) / 255.0f : 0.8f;
      float b = hasColor ? readF(vp, bI) / 255.0f : 0.8f;
      V.append(x);
      V.append(y);
      V.append(z);
      V.append(r);
      V.append(g);
      V.append(b);
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
    QTextStream stream(&file);
    for (int v = 0; v < vertexCount; v++) {
      QString line = stream.readLine();
      if (line.isNull())
        break;
      QStringList p = line.trimmed().split(' ', Qt::SkipEmptyParts);
      float x = p[xI].toFloat(), y = p[yI].toFloat(), z = p[zI].toFloat();
      float r = hasColor ? p[rI].toFloat() / 255.0f : 0.8f;
      float g = hasColor ? p[gI].toFloat() / 255.0f : 0.8f;
      float b = hasColor ? p[bI].toFloat() / 255.0f : 0.8f;
      V.append(x);
      V.append(y);
      V.append(z);
      V.append(r);
      V.append(g);
      V.append(b);
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
  result.maxExtent = std::max({maxX - minX, maxY - minY, maxZ - minZ});
  result.center = center;
  result.vertexCount = vertexCount;

  for (int i = 0; i < vertexCount; i++) {
    V[i * 6 + 0] -= center.x();
    V[i * 6 + 1] -= center.y();
    V[i * 6 + 2] -= center.z();
  }
  return result;
}
