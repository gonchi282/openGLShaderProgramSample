#include "MyGLWidget.h"

#include <QGLShader>

MyGLWidget::MyGLWidget(QWidget *parent) :
    QGLWidget(parent),
    shaderProgram(new QGLShaderProgram(this)),
    attrCoor2d(0)
{

}

void MyGLWidget::initializeGL()
{
    qglClearColor(QColor(Qt::black));
    setAutoBufferSwap(false);

    QGLShader vertexShader(QGLShader::Vertex);
    QGLShader fragmentShader(QGLShader::Fragment);

    qDebug() << "Compiling vertexShader";
    const char *vs_source =
#ifdef GL_ES_VERSION_2_0
            "#version 100\n"  // OpenGL ES 2.0
#else
            "#version 120\n"  // OpenGL 2.1
#endif
            "attribute vec2 coord2d;                  "
            "void main(void) {                        "
            "  gl_Position = vec4(coord2d, 0.0, 1.0); "
            "}";
    if (!vertexShader.compileSourceCode(vs_source)) {
        qDebug() << vertexShader.log();
    } else {
        qDebug() << "success";
    }
    const char *fs_source =
            "#version 120           \n"
            "void main(void) {        "
            "  gl_FragColor[0] = 0.0; "
            "  gl_FragColor[1] = 0.0; "
            "  gl_FragColor[2] = 1.0; "
            "}";
    if(!fragmentShader.compileSourceCode(fs_source)) {
        qDebug() << fragmentShader.log();
    } else {
        qDebug() << "success";
    }

    shaderProgram->addShader(&vertexShader);
    shaderProgram->addShader(&fragmentShader);
    if (!shaderProgram->link()) {
        qDebug() << shaderProgram->log();
    } else {
        qDebug() << "success";
    }
    shaderProgram->bind();

    shaderProgram->attributeLocation("coord2d");

    shaderProgram->release();
}

void MyGLWidget::paintGL()
{
    qglClearColor(QColor(Qt::blue));
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shaderProgram->bind();


    shaderProgram->enableAttributeArray(attrCoor2d);
    GLfloat triangle_vertices[] = {
       0.0,  0.8,
      -0.8, -0.8,
       0.8, -0.8,
    };
    shaderProgram->setAttributeArray(attrCoor2d, triangle_vertices, 3);

    shaderProgram->release();

    glDrawArrays(GL_TRIANGLES, 0, 3);

    swapBuffers();
}

void MyGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}
