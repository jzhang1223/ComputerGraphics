#include "BasicWidget.h"

#include "obj.cpp"

//////////////////////////////////////////////////////////////////////
// Publics
BasicWidget::BasicWidget(QWidget* parent) : QOpenGLWidget(parent)
{
  setFocusPolicy(Qt::StrongFocus);
}

BasicWidget::~BasicWidget()
{
}

//////////////////////////////////////////////////////////////////////
// Privates

///////////////////////////////////////////////////////////////////////
// Protected
void BasicWidget::keyReleaseEvent(QKeyEvent* keyEvent)
{
  // TODO
  // Handle key events here.
  printf("%s\n", keyEvent->text());
  if (keyEvent->key() == Qt::Key_Q) {
    qDebug() << "Q Key Pressed";
    QCoreApplication::quit(); // exits with return code 0
  } else if (keyEvent->key() == Qt::Key_W) {
    qDebug() << "W Key Pressed";
    // switch to rendering in wireframe mode
    update()
  } else if (keyEvent->key() == Qt::Key_1) {
    qDebug() << "1 Key Pressed";
    // render obj = bunny
    update()
  } else if (keyEvent->key() == Qt::Key_2) {
    qDebug() << "1 Key Pressed";
    // render obj = monkey
    update();
  } else {
    qDebug() << "You Pressed an unsupported Key!";
  }
  // ENDTODO
}

void BasicWidget::initializeGL()
{
  makeCurrent();
  initializeOpenGLFunctions();

  QOpenGLContext* curContext = this->context();
  qDebug() << "[BasicWidget]::initializeGL() -- Context Information:";
  qDebug() << "  Context Valid: " << std::string(curContext->isValid() ? "true" : "false").c_str();
  qDebug() << "  GL Version Used: " << curContext->format().majorVersion() << "." << curContext->format().minorVersion();
  qDebug() << "  Vendor: " << reinterpret_cast<const char*>(glGetString(GL_VENDOR));
  qDebug() << "  Renderer: " << reinterpret_cast<const char*>(glGetString(GL_RENDERER));
  qDebug() << "  Version: " << reinterpret_cast<const char*>(glGetString(GL_VERSION));
  qDebug() << "  GLSL Version: " << reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION));

  glViewport(0, 0, width(), height());
}

void BasicWidget::resizeGL(int w, int h)
{
  glViewport(0, 0, w, h);
}

void BasicWidget::paintGL()
{
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);

  glClearColor(0.f, 0.f, 0.f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // TODO:  render.
  OBJ myOBJ("../../objects/cube.obj");
  // myOBJ.draw();
}
