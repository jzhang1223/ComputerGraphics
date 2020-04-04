#include "BasicWidget.h"

#include <QByteArray>

//////////////////////////////////////////////////////////////////////
// Publics
BasicWidget::BasicWidget(QWidget* parent) : QOpenGLWidget(parent), vbo_(QOpenGLBuffer::VertexBuffer), ibo_(QOpenGLBuffer::IndexBuffer), logger_(this)
{
  setFocusPolicy(Qt::StrongFocus);
  // setup parse objects
  bunny.parse("../../objects/bunny_centered.obj");
  monkey.parse("../../objects/monkey_centered.obj");
  // bunny.parse("../../objects/windmill/windmill.obj");
  // monkey.parse("../../objects/capsule/capsule.obj");
  // current = bunny;
}

BasicWidget::~BasicWidget()
{
  vbo_.release();
  vbo_.destroy();
  ibo_.release();
  ibo_.destroy();
  vao_.release();
  vao_.destroy();
}

//////////////////////////////////////////////////////////////////////
// Privates
QString BasicWidget::vertexShaderString() const
{
  QString str =
    "#version 330\n"
    "layout(location = 0) in vec3 position;\n"
    // "layout(location = 1) in vec4 color;\n"

    "uniform mat4 modelMatrix;\n"
    "uniform mat4 viewMatrix;\n"
    "uniform mat4 projectionMatrix;\n"
    
    "out vec4 vertColor;\n"

    "void main()\n"
    "{\n"
    "  gl_Position = vec4(position, 1.0);\n"
    "  vertColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
    "}\n";
  return str;
}

QString BasicWidget::fragmentShaderString() const
{
  QString str =
  "#version 330\n"
    "in vec4 vertColor;\n"
  "out vec4 color;\n"
  "void main()\n"
  "{\n"
  "  color = vertColor;\n"
  "}\n";
  return str;
}

void BasicWidget::createShader()
{
  QOpenGLShader vert(QOpenGLShader::Vertex);
  vert.compileSourceCode(vertexShaderString());
  QOpenGLShader frag(QOpenGLShader::Fragment);
  frag.compileSourceCode(fragmentShaderString());
  bool ok = shaderProgram_.addShader(&vert);
  if(!ok) {
  qDebug() << shaderProgram_.log();
  }
  ok = shaderProgram_.addShader(&frag);
  if(!ok) {
  qDebug() << shaderProgram_.log();
  }
  ok = shaderProgram_.link();
  if(!ok) {
  qDebug() << shaderProgram_.log();
  }
}

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
    renderWireframe = !renderWireframe;
    // switch to rendering in wireframe mode
    update();
  } else if (keyEvent->key() == Qt::Key_1) {
    qDebug() << "1 Key Pressed";
    showBunny = true;
    setRender(bunny);
    update();
  } else if (keyEvent->key() == Qt::Key_2) {
    qDebug() << "2 Key Pressed";
    showBunny = false;
    setRender(monkey);
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

  createShader();

  // printf("Running initializeGL()");
  vbo_.create();
  ibo_.create();
  vao_.create();

  showBunny = true;
  setRender(bunny);

}

// Always set showBunny before calling setRender
void BasicWidget::setRender(OBJ image) {

  shaderProgram_.bind();

  vbo_.setUsagePattern(QOpenGLBuffer::StaticDraw);
  vbo_.bind();
  vbo_.allocate(image.out_vertices.data(), image.out_vertices.size() * sizeof(GL_FLOAT));


  ibo_.setUsagePattern(QOpenGLBuffer::StaticDraw);
  ibo_.bind();
  ibo_.allocate(image.out_indices.data(), image.out_indices.size() * sizeof(GL_UNSIGNED_INT));


  vao_.bind();
  vbo_.bind();

  shaderProgram_.enableAttributeArray(0);
  shaderProgram_.setAttributeBuffer(0, GL_FLOAT, 0, 3);

  ibo_.bind();

  vao_.release();
  shaderProgram_.release();


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

  renderWireframe ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  // TODO:  render.
  printf("Running paintGL()\n");


  shaderProgram_.bind();
  vao_.bind();
  if (showBunny) {
    glDrawElements(GL_TRIANGLES, bunny.out_indices.size(), GL_UNSIGNED_INT, 0);
  } else {
    glDrawElements(GL_TRIANGLES, monkey.out_indices.size(), GL_UNSIGNED_INT, 0);
  }
  vao_.release();
  shaderProgram_.release();

  printf(showBunny ? "true\n" : "false\n");

}