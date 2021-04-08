#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>
#include <QGLFunctions>
#include <QGLShaderProgram>

class MyGLWidget : public QGLWidget
{
public:
    MyGLWidget(QWidget *parent = nullptr);

protected:
    virtual void initializeGL() override;
    virtual void paintGL() override;
    virtual void resizeGL(int w, int h) override;

private:
    QGLShaderProgram *shaderProgram;
    int attrCoor2d;

};

#endif // MYGLWIDGET_H
