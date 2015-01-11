#include <QMouseEvent>
#include <QDebug>

#include "openglwidget.hpp"

OpenGLWidget::OpenGLWidget(QWidget *parent, Qt::WindowFlags f):
    QOpenGLWidget(parent, f),
    xRot(0),
    yRot(0),
    zRot(0)
{
}

OpenGLWidget::~OpenGLWidget()
{

}

void OpenGLWidget::initializeGL()
{
    QSurfaceFormat format = context()->format();
    format.setSwapInterval(0);
    format.setProfile(QSurfaceFormat::CoreProfile);
    qDebug() << format;

    context()->setFormat(format);

    initializeOpenGLFunctions();

    glClearColor(0.f, 0.f, 0.f, 0.f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    static GLfloat lightPosition[4] = { 0, 0, 10, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void OpenGLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-2, +2, -2, +2, 1.0, 15.0);

    glMatrixMode(GL_MODELVIEW);
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);

    glColor3f(1., 1., 1.f);
    glBegin(GL_QUADS);
    glNormal3f(0, 0, -1);
    glVertex3f(-1, -1, 0);
    glVertex3f(-1, 1, 0);
    glVertex3f(1, 1, 0);
    glVertex3f(1, -1, 0);

    glEnd();
    glBegin(GL_TRIANGLES);
    glNormal3f(0, -1, 0.707);
    glVertex3f(-1, -1, 0);
    glVertex3f(1, -1, 0);
    glVertex3f(0, 0, 1.2);
    glEnd();
    glBegin(GL_TRIANGLES);
    glNormal3f(1, 0, 0.707);
    glVertex3f(1, -1, 0);
    glVertex3f(1, 1, 0);
    glVertex3f(0, 0, 1.2);
    glEnd();
    glBegin(GL_TRIANGLES);
    glNormal3f(0, 1, 0.707);
    glVertex3f(1, 1, 0);
    glVertex3f(-1, 1, 0);
    glVertex3f(0, 0, 1.2);
    glEnd();
    glBegin(GL_TRIANGLES);
    glNormal3f(-1, 0, 0.707);
    glVertex3f(-1, 1, 0);
    glVertex3f(-1, -1, 0);
    glVertex3f(0, 0, 1.2);
    glEnd();
}
void OpenGLWidget::mousePressEvent(QMouseEvent *event)
{
    lastMousePosition = event->pos();
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    QPoint positionDiff = lastMousePosition - event->pos();

    yRot -= positionDiff.x();
    xRot -= positionDiff.y();

    lastMousePosition = event->pos();

    update();
}
