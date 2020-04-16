#include "BasicWidget.h"
#include <iostream>

//////////////////////////////////////////////////////////////////////
// Publics
BasicWidget::BasicWidget(QWidget* parent) : QOpenGLWidget(parent), logger_(this)
{
  setFocusPolicy(Qt::StrongFocus);
}

BasicWidget::~BasicWidget()
{
    for (auto renderable : renderables_) {
        delete renderable;
    }
    renderables_.clear();
}

//////////////////////////////////////////////////////////////////////
// Privates
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
  } else if (keyEvent->key() == Qt::Key_W) {
    qDebug() << "W Key Pressed";
    renderWireframe = !renderWireframe;
    // switch to rendering in wireframe mode
    update();
  } else {
    qDebug() << "You Pressed an unsupported Key!";
  }
}
void BasicWidget::initializeGL()
{
  makeCurrent();
  initializeOpenGLFunctions();

  qDebug() << QDir::currentPath();
  
  qDebug() << "HERE***********";
  std::cout << "HEREHEEEEE********";

  // QString texFile = "../../cat3.ppm";
  QString start = "../../objects";
  QString texFile;
  QVector<QVector3D> pos;
  QVector<QVector3D> norm;
  QVector<QVector2D> texCoord;
  QVector<uint> idx;


  if(false) {
    // Lab 7 Works here
    texFile = "../../cat3.ppm";
  
    pos << QVector3D(-0.8, -0.8, 0.0);
    pos << QVector3D(0.8, -0.8, 0.0);
    pos << QVector3D(-0.8, 0.8, 0.0);
    pos << QVector3D(0.8, 0.8, 0.0);
  // We don't actually use the normals right now, but this will be useful later!
    // norm << QVector3D(0.0, 0.0, 1.0);
    // norm << QVector3D(0.0, 0.0, 1.0);
    // norm << QVector3D(0.0, 0.0, 1.0);
    // norm << QVector3D(0.0, 0.0, 1.0);
  // TODO:  Make sure to add texture coordinates to pass into the initialization of our renderable
    idx << 0 << 1 << 2 << 2 << 1 << 3;

    texCoord << QVector2D(1.0, 1.0);
    texCoord << QVector2D(1.0, 0.0);
    texCoord << QVector2D(0.0, 1.0);
    texCoord << QVector2D(0.0, 0.0);
  }
  else {
    // Assignment 4 Case
    texFile = start + "/windmill/windmill_diffuse.ppm";
    OBJ currentOBJ;
    currentOBJ.parse("../../objects/windmill/windmill.obj");
    // for(int i = 0; i < currentOBJ.out_vertices.size(); i += 3) {
    //     pos += QVector3D(currentOBJ.out_vertices[i], currentOBJ.out_vertices[i+1], currentOBJ.out_vertices[i+2]);
    // }
    for(int i = 0; i < currentOBJ.out_indices.size(); i += 3) {
      // std::cout << i << "...1\n";
        // pos << QVector3D(currentOBJ.out_vertices[i], currentOBJ.out_vertices[i+1], currentOBJ.out_vertices[i+2]);
        pos << QVector3D(currentOBJ.out_vertices[currentOBJ.out_indices[i]], currentOBJ.out_vertices[currentOBJ.out_indices[i+1]], currentOBJ.out_vertices[currentOBJ.out_indices[i+2]]);
    }
    // for(int i = 0; i < currentOBJ.out_texs.size(); i += 2) {
        // texCoord += QVector2D(currentOBJ.out_texs[i], currentOBJ.out_texs[i+1]);
    // }


    for(int i = 0; i < currentOBJ.out_texIndices.size(); i += 3) {
        // std::cout << i << "...2\n";
        texCoord << QVector2D(currentOBJ.out_texs[currentOBJ.out_texIndices[i]], currentOBJ.out_texs[currentOBJ.out_texIndices[i+1]]);
    }


    // for(int i = 0; i < currentOBJ.out_normals.size(); i += 3) {
    //     norm += QVector3D(currentOBJ.out_normals[i], currentOBJ.out_normals[i+1], currentOBJ.out_normals[i+2]);
    // }
    printf("DID DID SOMETHING\n");
    // for(uint index: currentOBJ.out_indices) {
    //   idx += index;
    // }
    // TODO: GET PROPER IDX??
    for(int i = 0; i < pos.size(); i += 1) {
        // for(int j = 0; j < i; j += 1) {
          // std::cout << pos[j] << "\n";
          // std::cout << pos[i] << "\n";
          // std::cout << texCoord[j] << "\n";
          // std::cout << texCoord[i] << "\n";

        //   if(qFuzzyCompare(pos[j],pos[i]) && qFuzzyCompare(texCoord[j],texCoord[i])) {
        //     // std::cout << j << "\n";
        //     idx << j;
        //     break;
        //   }
        // }
        // std::cout << i << "...out\n";
        idx << i;
    }
    // pos = currentOBJ.getVertices();
    // norm = currentOBJ.getNormals();
    // texCoord = currentOBJ.getTexs();
    // idx = currentOBJ.out_indices.data();
    std::cout << idx.size();

  }

  // PARSING OBJ COMPLETE HERE

  Renderable* ren = new Renderable();
  ren->init(pos, norm, texCoord, idx, texFile);
  renderables_.push_back(ren);

  glViewport(0, 0, width(), height());
  frameTimer_.start();
}

void BasicWidget::resizeGL(int w, int h)
{
    if (!logger_.isLogging()) {
        logger_.initialize();
        // Setup the logger for real-time messaging
        connect(&logger_, &QOpenGLDebugLogger::messageLogged, [=]() {
            const QList<QOpenGLDebugMessage> messages = logger_.loggedMessages();
            for (auto msg : messages) {
                qDebug() << msg;
            }
            });
        logger_.startLogging();
    }
  glViewport(0, 0, w, h);
  view_.setToIdentity();
  view_.lookAt(QVector3D(0.0f, 0.0f, 2.0f),
      QVector3D(0.0f, 0.0f, 0.0f),
      QVector3D(0.0f, 1.0f, 0.0f));
  view_.scale(0.5f);
  projection_.setToIdentity();
  projection_.perspective(70.f, (float)w/(float)h, 0.001, 1000.0);
  glViewport(0, 0, w, h);
}

void BasicWidget::paintGL()
{
  qint64 msSinceRestart = frameTimer_.restart();
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);

  glClearColor(0.f, 0.f, 0.f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // wireframe check
  renderWireframe ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  for (auto renderable : renderables_) {
      renderable->update(msSinceRestart);
      renderable->draw(view_, projection_);
  }
  update();
}
