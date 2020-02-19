#pragma once

#include <QtGui>
#include <QtWidgets>
#include <QtOpenGL>

#include "obj.cpp"

/**
 * This is just a basic OpenGL widget that will allow a change of background color.
 */
class BasicWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
  Q_OBJECT

private:
  QString vertexShaderString() const;
  QString fragmentShaderString() const;
  void createShader();
  QOpenGLVertexArrayObject vao_;



  bool renderWireframe = true;
  bool showBunny = true;
  OBJ bunny;
  OBJ monkey;
  OBJ current;
  
protected:
  // Required interaction overrides
  void keyReleaseEvent(QKeyEvent* keyEvent) override;

  // Required overrides form QOpenGLWidget
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

  QOpenGLBuffer vbo_;
  QOpenGLBuffer ibo_;

  QOpenGLShaderProgram shaderProgram_;
  QOpenGLDebugLogger logger_;

  void setRender(OBJ image);


  
public:
  BasicWidget(QWidget* parent=nullptr);
  virtual ~BasicWidget();
  
  // Make sure we have some size that makes sense.
  QSize sizeHint() const {return QSize(800,600);}
};