#include <iostream>
#include "MainWindow.h"
#include "ui_MainWindow.h"


MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent), m_ui(new Ui::MainWindow)
{
  m_ui->setupUi(this);
  m_gl=new  NGLScene(this);
  m_ui->mainWindowGridLayout->addWidget(m_gl,0,0,2,3);

  connect(m_ui->wireframe_checkBox,SIGNAL(toggled(bool)),m_gl,SLOT(toggleWireframe(bool)));
  //connect(m_gl, &NGLScene::textUpdateSignal, this, &MainWindow::updateTextBrowser);

  m_ui->cubeColorCombo->addItem("Solid Color");
  m_ui->cubeColorCombo->addItem("Checkered Color");

  m_ui->floorColorCombo->addItem("Checkered Color");
  m_ui->floorColorCombo->addItem("Solid Color");


  m_ui->algoComboBox->addItem("Prim's Algorithm");
  m_ui->algoComboBox->addItem("Wilson's Maze Generation Algorithm");
  m_ui->algoComboBox->addItem("Recursive Backtracking and Depth First Search Algorithm");


  connect(m_ui->resetMazeBtn,SIGNAL(clicked()),m_gl,SLOT(ResetMaze()));

  connect(m_ui->generateMazeBtn,&QPushButton::clicked,
          [=]()
          {

            m_gl -> GenerateMaze(m_ui -> widthMaze->value(),m_ui -> depthMaze->value(),m_ui->algoComboBox->currentIndex());
              QString newText = NGLScene::TextBrowserMessage();
              m_ui->textBrowser->setText(newText);

              NGLScene::cubeColorIndex = m_ui -> cubeColorCombo -> currentIndex();
              NGLScene::floorColorIndex = m_ui -> floorColorCombo -> currentIndex();

              if ( m_ui->defaultRadio->isChecked())
              {
                NGLScene::cameraIndex = 1;
                NGLScene::CameraSetup();
              }
              if ( m_ui->topRadio->isChecked())
              {
                NGLScene::cameraIndex = 0;
                NGLScene::CameraSetup();
              }
          });

  m_ui->textBrowser->setText(NGLScene::TextBrowserMessage());

}

MainWindow::~MainWindow()
{
    delete m_ui;
}



void MainWindow::keyPressEvent(QKeyEvent *_event)
{
  // that method is called every time the main window recives a key event.
  // we then switch on the key value and set the camera in the GLWindow
  switch (_event->key())
  {
    // escape key to quit
    case Qt::Key_Escape:
      QGuiApplication::exit(EXIT_SUCCESS);
      break;
// turn on wireframe rendering
#ifndef USINGIOS_
    case Qt::Key_W:
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      break;
      // turn off wire frame
    case Qt::Key_S:
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      break;
#endif
      // show full screen
    case Qt::Key_F:
      showFullScreen();
      break;
      // show windowed
    case Qt::Key_N:
      showNormal();
      break;
   /* case Qt::Key_Space:
      m_win.spinXFace = 0;
      m_win.spinYFace = 0;
      m_modelPos.set(ngl::Vec3::zero());
      break;

    case Qt::Key_L:
      m_transformLight ^= true;
      break;*/
    default:
      break;
  }
  update();
}

