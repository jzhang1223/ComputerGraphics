#include "BasicWidget.h"

//////////////////////////////////////////////////////////////////////
// Publics
BasicWidget::BasicWidget(QWidget* parent) : QOpenGLWidget(parent), vbo_(QOpenGLBuffer::VertexBuffer), ibo_(QOpenGLBuffer::IndexBuffer), logger_(this)
{
  setFocusPolicy(Qt::StrongFocus);
}

BasicWidget::~BasicWidget()
{
  vbo_.release();
  vbo_.destroy();
  // TODO: Remove the CBO
  // cbo_.release();
  // cbo_.destroy();
  // End TODO
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
    "layout(location = 1) in vec4 color;\n"

    "uniform mat4 modelMatrix;\n"
    "uniform mat4 viewMatrix;\n"
    "uniform mat4 projectionMatrix;\n"
    
    "out vec4 vertColor;\n"

    "void main()\n"
    "{\n"
    // TODO: gl_Position must be updated!
    "  gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);\n"
    // END TODO
    "  vertColor = color;\n"
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
  // Handle key events here.
  if (keyEvent->key() == Qt::Key_Left) {
    qDebug() << "Left Arrow Pressed";
    update();  // We call update after we handle a key press to trigger a redraw when we are ready
  } else if (keyEvent->key() == Qt::Key_Right) {
    qDebug() << "Right Arrow Pressed";
    update();  // We call update after we handle a key press to trigger a redraw when we are ready
  } else {
    qDebug() << "You Pressed an unsupported Key!";
  }
}
void BasicWidget::initializeGL()
{
  makeCurrent();
  initializeOpenGLFunctions();
  logger_.initialize();

  // All of our matrices should be set to identity for now.
  model_.setToIdentity();
  view_.setToIdentity();
  projection_.setToIdentity();
  
  // Setup the logger for real-time messaging
  connect(&logger_, &QOpenGLDebugLogger::messageLogged, [=](){
    const QList<QOpenGLDebugMessage> messages = logger_.loggedMessages();
    for(auto msg : messages) {
      qDebug() << msg;
    }
  });
  logger_.startLogging();
  
  QOpenGLContext* curContext = this->context();
  qDebug() << "[BasicWidget]::initializeGL() -- Context Information:";
  qDebug() << "  Context Valid: " << std::string(curContext->isValid() ? "true" : "false").c_str();
  qDebug() << "  GL Version Used: " << curContext->format().majorVersion() << "." << curContext->format().minorVersion();
  qDebug() << "  Vendor: " << reinterpret_cast<const char*>(glGetString(GL_VENDOR));
  qDebug() << "  Renderer: " << reinterpret_cast<const char*>(glGetString(GL_RENDERER));
  qDebug() << "  Version: " << reinterpret_cast<const char*>(glGetString(GL_VERSION));
  qDebug() << "  GLSL Version: " << reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION));

  // Set up our shaders.
  createShader();

  // Define our verts
  // x, y, z, r, g, b, a
  static const GLfloat verts[21] =
  {
    0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // Center vertex position
    1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // Top right vertex position
    -1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f  // Top left vertex position
  };
  // Define our vert colors
 //  static const GLfloat colors[12] =
 //  {
 // // red
 //       // green
 // // blue
 //  };
  // Define our indices
  static const GLuint idx[3] =
  {
      0, 1, 2
  };
  // Set up our buffers and our vao
  // Temporary bind of our shader.
  shaderProgram_.bind();

  // TODO:  Create a position + color buffer
  // Note - use the vbo_ member provided 
  vbo_.create();
  vbo_.setUsagePattern(QOpenGLBuffer::StaticDraw);
  vbo_.bind();
  // vertices * data points per vertex * data point size
  vbo_.allocate(verts, 3 * 7 * sizeof(GL_FLOAT));
  // END TODO
  
  // TODO:  Remove the cbo_
  // cbo_.create();
  // cbo_.setUsagePattern(QOpenGLBuffer::StaticDraw);
  // cbo_.bind();
  // cbo_.allocate(colors, 3 * 4 * sizeof(GL_FLOAT));
  // END TODO

  // TODO:  Generate our index buffer
  ibo_.create();
  ibo_.setUsagePattern(QOpenGLBuffer::StaticDraw);
  ibo_.bind();
  ibo_.allocate(idx, 7 * sizeof(GL_UNSIGNED_INT));
  // ENDTODO

  // Create a VAO to keep track of things for us.
  vao_.create();
  vao_.bind();
  vbo_.bind();
  // TODO:  Enable the attribute arrays for position and color
  // Note:  Remember that Offset and Stride are expressed in terms
  //        of bytes!
  shaderProgram_.enableAttributeArray(0);
  shaderProgram_.setAttributeBuffer(0, GL_FLOAT, 0, 3, 7 * sizeof(GL_FLOAT));
  // cbo_.bind();
  shaderProgram_.enableAttributeArray(1);
  shaderProgram_.setAttributeBuffer(1, GL_FLOAT, 3 * sizeof(GL_FLOAT), 4, 7 * sizeof(GL_FLOAT));
  // END TODO

  ibo_.bind();
  // Releae the vao THEN the vbo
  vao_.release();
  shaderProgram_.release();

  glViewport(0, 0, width(), height());
}

void BasicWidget::resizeGL(int w, int h)
{
  glViewport(0, 0, w, h);
  // TODO:  Set up the model, view, and projection matrices
  // bind the shader first...shaderProgram_
  shaderProgram_.bind();

  // use built-in methods to create matrices for scale, rotate, translate...

  model_.setToIdentity();
  model_.translate(0, -.5);
  model_.scale(.25, .25, 1);
  // degrees, (x, y, z) of vector to rotate about
  model_.rotate(180, 1, 0, 0);
  view_.setToIdentity();
  // view_.rotate(0, 0, 0, 1);
  view_.translate(.5, .5);
  // view_.scale(.8, .8, 1);
  projection_.setToIdentity();

  shaderProgram_.setUniformValue("modelMatrix", model_);
  shaderProgram_.setUniformValue("viewMatrix", view_);
  shaderProgram_.setUniformValue("projectionMatrix", projection_);

  shaderProgram_.release();
  // END TODO
}

void BasicWidget::paintGL()
{
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);

  glClearColor(0.f, 0.f, 0.f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  shaderProgram_.bind();
  vao_.bind();
  glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
  vao_.release();
  shaderProgram_.release();
}
