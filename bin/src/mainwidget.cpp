 #include "mainwidget.h"

 #include "geometryengine.h"

 #include <QBasicTimer>
 #include <QMouseEvent>
 #include <QDebug>
 #include <mprogram.h>
 #include <utils.h>

 #include <math.h>

 MainWidget::MainWidget(QWidget *parent) :
     QGLWidget(parent),
     timer(new QBasicTimer),
     geometries(new GeometryEngine)
 {
 }

 MainWidget::~MainWidget()
 {
     delete timer; timer = 0;
     delete geometries; geometries = 0;
 }

 void MainWidget::mousePressEvent(QMouseEvent *e)
 {
     // Saving mouse press position
     mousePressPosition = QVector2D(e->pos());
 }

 void MainWidget::mouseReleaseEvent(QMouseEvent *e)
 {
     // Mouse release position - mouse press position
     QVector2D diff = QVector2D(e->pos()) - mousePressPosition;

     // Rotation axis is perpendicular to the mouse position difference
     // vector
     QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

     // Accelerate angular speed relative to the length of the mouse sweep
     qreal acc = diff.length() / 100.0;

     // Calculate new rotation axis as weighted sum
     rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

     // Increase angular speed
     angularSpeed += acc;
 }

 void MainWidget::timerEvent(QTimerEvent *e)
 {
     Q_UNUSED(e);

     // Decrease angular speed (friction)
     angularSpeed *= 0.99;

     // Stop rotation when speed goes below threshold
     if (angularSpeed < 0.01)
         angularSpeed = 0.0;
     else {
         // Update rotation
         rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;

         // Update scene
         updateGL();
     }
 }

 void MainWidget::initializeGL()
 {
     initializeGLFunctions();

     qglClearColor(Qt::gray);

     qDebug() << "Initializing shaders...";
     initShaders();

     // Enable depth buffer
     glEnable(GL_DEPTH_TEST);

     // Enable back face culling
     glEnable(GL_CULL_FACE);

     qDebug() << "Initializing geometries...";
     geometries->init();

     // using QBasicTimer because its faster that QTimer
//     timer->start(12, this);
 }

 void MainWidget::initShaders() {
     std::string vertexCode = Utils::readFile("../bin/resources/Shaders/basic.vert");
     std::string fragmentCode = Utils::readFile("../bin/resources/Shaders/basic.frag");

     MVertexShader vShader(vertexCode);
     MFragmentShader fShader(fragmentCode);

     program = new MProgram(vShader, fShader);
 }

 void MainWidget::initTextures() {}

 void MainWidget::resizeGL(int w, int h)
 {
     // Set OpenGL viewport to cover whole widget
     glViewport(0, 0, w, h);

     // Calculate aspect ratio
     qreal aspect = (qreal)w / ((qreal)h?h:1);

     // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
     const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;

     // Reset projection
     projection.setToIdentity();

     // Set perspective projection
     projection.perspective(fov, aspect, zNear, zFar);
 }

 void MainWidget::paintGL()
 {
     // Clear color and depth buffer
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

     // Calculate model view transformation
     QMatrix4x4 matrix;
     matrix.translate(0.0, 0.0, -5.0);

     // Draw cube geometry
     geometries->drawCubeGeometry(program);
 }
