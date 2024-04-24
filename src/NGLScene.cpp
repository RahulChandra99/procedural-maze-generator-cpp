#include "NGLScene.h"
#include <ngl/NGLInit.h>
#include <ngl/NGLStream.h>
#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>
#include <QGuiApplication>
#include <ngl/Util.h>
#include <ngl/Transformation.h>
#include <QMouseEvent>
#include <QRect>
#include <QApplication>
#include <memory>
#include <iostream>



//----------------------------------------------------------------------------------------------------------------------
NGLScene::NGLScene( QWidget *_parent ) : QOpenGLWidget( _parent )
{

  // set this widget to have the initial keyboard focus
  setFocus();
  // re-size the widget to that of the parent (in this case the GLFrame passed in on construction)
  resize(_parent->size());

}


NGLScene::~NGLScene()
{
  std::cout << "Shutting down NGL, removing VAO's and Shaders\n";
}

void NGLScene::resizeGL(int _w, int _h)
{
  m_projection = ngl::perspective(45.0f, static_cast<float>(_w) / _h, 0.1f, 200.0f);

  m_win.width = static_cast<int>(_w * devicePixelRatio());
  m_win.height = static_cast<int>(_h * devicePixelRatio());
}

int NGLScene::algoIndex = 0;
int NGLScene::cubeColorIndex = 0;
int NGLScene::floorColorIndex = 0;
int NGLScene::cameraIndex;
ngl::Mat4 NGLScene::m_view = ngl::Mat4();

void NGLScene::CameraSetup()
{
  if(cameraIndex == 1)
  {
    //default camera
    ngl::Vec3 from{0.0f, 2.0f, 2.0f};
    ngl::Vec3 to{0.0f, 0.0f, 0.0f};
    ngl::Vec3 up{0.0f, 1.0f, 0.0f};
    // now load to our new camera
    m_view = ngl::lookAt(from, to, up);
    ngl::ShaderLib::setUniform("camPos", from);
  }
  if(cameraIndex == 0)
  {
    //top down camera
    ngl::Vec3 from{0.0f, 30.0f, 2.0f};
    ngl::Vec3 to{0.0f, 0.0f, 0.0f};
    ngl::Vec3 up{0.0f, 1.0f, 0.0f};
    // now load to our new camera
    m_view = ngl::lookAt(from, to, up);
    ngl::ShaderLib::setUniform("camPos", from);
  }
}

void NGLScene::initializeGL()
{
  TextBrowserMessage();

  ngl::NGLInit::initialize();

  glClearColor(0.4f, 0.4f, 0.4f, 1.0f); // Grey Background
  // enable depth testing for drawing
  glEnable(GL_DEPTH_TEST);
  // enable multisampling for smoother drawing
  glEnable(GL_MULTISAMPLE);

  // We now create our view matrix for a static camera

  if(cameraIndex == 1)
  {
    std::cout<<"Default Camera";

    //default camera
    ngl::Vec3 from{2.0f, 0.0f, 2.0f};
    ngl::Vec3 to{0.0f, 0.0f, 0.0f};
    ngl::Vec3 up{0.0f, 1.0f, 0.0f};
    // now load to our new camera
    m_view = ngl::lookAt(from, to, up);
    ngl::ShaderLib::setUniform("camPos", from);
  }
  if(cameraIndex == 0)
  {
    std::cout<<"Top down  Camera";

    //top down camera
    ngl::Vec3 from{0.0f, 30.0f, 2.0f};
    ngl::Vec3 to{0.0f, 0.0f, 0.0f};
    ngl::Vec3 up{0.0f, 1.0f, 0.0f};
    // now load to our new camera
    m_view = ngl::lookAt(from, to, up);
    ngl::ShaderLib::setUniform("camPos", from);
  }

  // now a light
  m_lightPos.set(0.0, 2.0f, 2.0f, 1.0f);

  ngl::VAOPrimitives::createTrianglePlane("floor", 20, 20, 1, 1, ngl::Vec3::up());


  //set up the walls and corridors
  Maze::InitialiseMap();
  Maze::Generate(0);

}

void NGLScene::loadMatricesToShader()
{
  struct transform
  {
      ngl::Mat4 MVP;
      ngl::Mat4 normalMatrix;
      ngl::Mat4 M;
  };

  transform t;
  t.M = m_view * m_mouseGlobalTX;

  t.MVP = m_projection * t.M;
  t.normalMatrix = t.M;
  t.normalMatrix.inverse().transpose();
  ngl::ShaderLib::setUniformBuffer("TransformUBO", sizeof(transform), &t.MVP.m_00);

  if (m_transformLight)
  {
    ngl::ShaderLib::setUniform("lightPosition", (m_mouseGlobalTX * m_lightPos).toVec3());
  }
}


void NGLScene::paintGL()
{
  glViewport(0, 0, m_win.width, m_win.height);
  // clear the screen and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


  //wireframe toggle
  if(m_wireframe)
  {
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  }
  else
  {
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  }

  // Rotation based on the mouse position for our global transform
  auto rotX = ngl::Mat4::rotateX(m_win.spinXFace * 2.0f);
  auto rotY = ngl::Mat4::rotateY(m_win.spinYFace * 2.0f);

  // multiply the rotations
  m_mouseGlobalTX = rotX * rotY;
  // add the translations
  m_mouseGlobalTX.m_m[3][0] = m_modelPos.m_x * 2.0f;
  m_mouseGlobalTX.m_m[3][1] = m_modelPos.m_y * 2.0f;
  m_mouseGlobalTX.m_m[3][2] = m_modelPos.m_z * 2.0f;

  // draw
  loadMatricesToShader();


  if(cubeColorIndex == 1)
  {

    ngl::ShaderLib::use(ngl::nglCheckerShader);
    ngl::ShaderLib::setUniform("lightDiffuse", 1.0f, 1.0f, 1.0f, 1.0f);
    ngl::ShaderLib::setUniform("checkOn", true);
    ngl::ShaderLib::setUniform("lightPos", m_lightPos.toVec3());
    ngl::ShaderLib::setUniform("colour1", 0.3f, 0.3f, 0.3f, 1.0f);
    ngl::ShaderLib::setUniform("colour2", 0.6f, 0.6f, 0.6f,1.0f);
    ngl::ShaderLib::setUniform("checkSize", 60.0f);
  }

  if(cubeColorIndex == 0)
  {
    ngl::ShaderLib::use("nglDiffuseShader");

    std::srand(std::time(0));
    float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    float g = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    float b = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    ngl::ShaderLib::setUniform("Colour", r, g, b, 1.0f);

    ngl::ShaderLib::setUniform("lightPos", 1.0f, 1.0f, 1.0f);
    ngl::ShaderLib::setUniform("lightDiffuse", 1.0f, 1.0f, 1.0f, 1.0f);
  }

  //draw maze
  for(int z = 0;z < Maze::myDepth; z++)
  {
    for(int x = 0; x< Maze::myWidth; x++)
    {
      if(Maze::map[x][z] == 1)
      {
        ngl::Transformation tx;
        ngl::Mat3 normalMatrix = m_view * m_mouseGlobalTX;
        normalMatrix.inverse().transpose();
        tx.setPosition(x,0,z);
        tx.setScale(1,0.5,1);
        ngl::ShaderLib::setUniform("MVP",m_projection * m_view * m_mouseGlobalTX * tx.getMatrix());
        ngl::VAOPrimitives::draw(ngl::cube);
        ngl::ShaderLib::setUniform("normalMatrix", normalMatrix);
        tx.reset();

      }
    }
  }


  if (m_transformLight)
  {
    ngl::ShaderLib::setUniform("lightPosition", (m_mouseGlobalTX * m_lightPos).toVec3());
  }

  //Floor

  ngl::Transformation ty;
  ty.setPosition(Maze::myWidth/2,-0.5,Maze::myDepth/2);
  ty.setScale(Maze::myWidth/15,1,Maze::myDepth/15);

if(floorColorIndex == 0)
{

  ngl::ShaderLib::use(ngl::nglCheckerShader);
  ngl::ShaderLib::setUniform("lightDiffuse", 1.0f, 1.0f, 1.0f, 1.0f);
  ngl::ShaderLib::setUniform("checkOn", true);
  ngl::ShaderLib::setUniform("lightPos", m_lightPos.toVec3());
  ngl::ShaderLib::setUniform("colour1", 0.0f, 0.0f, 0.0f, 0.0f);
  ngl::ShaderLib::setUniform("colour2", 0.6f, 0.6f, 0.6f,1.0f);
  ngl::ShaderLib::setUniform("checkSize", 60.0f);
}

if(floorColorIndex == 1)
{
  ngl::ShaderLib::use("nglDiffuseShader");

  ngl::ShaderLib::setUniform("Colour", 0.0f, 0.0f, 0.0f, 1.0f);
  ngl::ShaderLib::setUniform("lightPos", 1.0f, 1.0f, 1.0f);
  ngl::ShaderLib::setUniform("lightDiffuse", 1.0f, 1.0f, 1.0f, 1.0f);
}


  ngl::ShaderLib::setUniform("MVP",m_projection * m_view * m_mouseGlobalTX * ty.getMatrix());
  ngl::VAOPrimitives::draw("floor");

}


void NGLScene::keyPressEvent(QKeyEvent *_event)
{
  // that method is called every time the main window recives a key event.
  // we then switch on the key value and set the camera in the GLWindow
  switch (_event->key())
  {
    // escape key to quit
    case Qt::Key_Escape:
      QGuiApplication::exit(EXIT_SUCCESS);
      break;
/*// turn on wireframe rendering
#ifndef USINGIOS_
    case Qt::Key_W:
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      break;
      // turn off wire frame
    case Qt::Key_S:
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      break;
#endif*/
      // show full screen
    case Qt::Key_F:
      showFullScreen();
      break;
      // show windowed
    case Qt::Key_N:
      showNormal();
      break;
    default:
      break;
  }
  update();
}

void NGLScene::wireFrameMode()
{
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  update();
}

void NGLScene::GenerateMaze(int width,int depth,int algoValue)
{
  //CentreMaze();
  Maze::myWidth = width;
  Maze::myDepth = depth;
  Maze::InitialiseMap();
  Maze::Generate(algoValue);
  algoIndex = algoValue;
  NGLScene::paintGL();
  update();
}

void NGLScene::ResetMaze()
{
  CentreMaze();
  Maze::myWidth = 0;
  Maze::myDepth = 0;
  Maze::InitialiseMap();
  //Maze::Generate(algoValue);
  NGLScene::paintGL();
  update();
}


void NGLScene::toggleWireframe( bool _mode	)
{
  m_wireframe = _mode;
  update();
}

void NGLScene::CentreMaze()
{
  m_win.spinXFace = 0;
  m_win.spinYFace = 0;
  m_modelPos.set(ngl::Vec3::zero());
}

QString NGLScene::TextBrowserMessage()
{
  QString myMessage;
  switch (algoIndex)
  {
    case 0:
      myMessage = "<div align='center'><u>Instructions:<br></U></div>"
                  "<div align='left'><u>Camera Operations</u> : Use Mouse click to tumble scene ; "
                          "Right Mouse to Translate ; "
                          "Mouse Wheel to Zoom<br>"
                          "<u>Keyboard Operations</u> :"
                          " 'F' for Full Screen Mode ; "
                          "'N' for Windowed Mode<br>"
                          "<u>Current Algorithm</u> : Prim's Maze Generation Algorithm<br><br>"
                          "<u>How to operate</u> : "
                          "Adjust the width and height of the maze, select the camera angle,"
                          " select the appropriate algorithm for generation and press Generate.</div>" ;
      break;
    case 1:
      myMessage = "<div align='center'><u>Instructions:<br></U></div>"
                  "<div align='left'><u>Camera Operations</u> : Use Mouse click to tumble scene ; "
                  "Right Mouse to Translate ; "
                  "Mouse Wheel to Zoom<br>"
                  "<u>Keyboard Operations</u> :"
                  " 'F' for Full Screen Mode ; "
                  "'N' for Windowed Mode<br>"
                  "<u>Current Algorithm</u> : Wilson's Maze Generation Algorithm<br><br>"
                  "<u>How to operate</u> : "
                  "Adjust the width and height of the maze, select the camera angle,"
                  " select the appropriate algorithm for generation and press Generate.</div>" ;
      break;
    case 2:
      myMessage = "<div align='center'><u>Instructions:<br></U></div>"
                  "<div align='left'><u>Camera Operations</u> : Use Mouse click to tumble scene ; "
                  "Right Mouse to Translate ; "
                  "Mouse Wheel to Zoom<br>"
                  "<u>Keyboard Operations</u> :"
                  " 'F' for Full Screen Mode ; "
                  "'N' for Windowed Mode<br>"
                  "<u>Current Algorithm</u> : Depth First Search and Recursive Backtracking Maze Generation Algorithm<br><br>"
                  "<u>How to operate</u> : "
                  "Adjust the width and height of the maze, select the camera angle,"
                  " select the appropriate algorithm for generation and press Generate.</div>" ;
      break;
    default:
      break;
  }

  return myMessage;
}







//----------------------------------------------------------------------------------------------------------------------



