#ifndef NGLSCENE_H_
#define NGLSCENE_H_

#include <ngl/Vec3.h>
#include "WindowParams.h"
#include <QResizeEvent>
#include <QOpenGLWidget>
#include <memory>
#include <ngl/Text.h>
#include <ngl/Vec4.h>
#include <ngl/Mat4.h>
#include "WindowParams.h"
#include <QOpenGLWindow>

#include "Maze.h"


class NGLScene : public QOpenGLWidget
{
Q_OBJECT        // must include this if you use Qt signals/slots
public :
  /// @brief Constructor for GLWindow
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Constructor for GLWindow
  /// @param [in] _parent the parent window to create the GL context in
  //----------------------------------------------------------------------------------------------------------------------
  static int cameraIndex;
  static int cubeColorIndex;
  static int floorColorIndex;
  static QString TextBrowserMessage();
  static void CameraSetup();
    NGLScene(QWidget *_parent = nullptr);

		/// @brief dtor
  ~NGLScene() override;

 public slots :
    void wireFrameMode();
    void GenerateMaze(int width,int depth,int algoValue);
    void ResetMaze();
    void toggleWireframe( bool _mode);
    void CentreMaze();

protected:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the windows params such as mouse and rotations etc
  //----------------------------------------------------------------------------------------------------------------------
  WinParams m_win;
  /// @brief  The following methods must be implimented in the sub class
  /// this is called when the window is created
  void initializeGL() override;

  /// @brief this is called whenever the window is re-sized
  /// @param[in] _w the width of the resized window
  /// @param[in] _h the height of the resized window
  void resizeGL(int _w , int _h) override;
  /// @brief this is the main gl drawing routine which is called whenever the window needs to
  // be re-drawn
  void paintGL() override;





private :
     static int algoIndex;

    /// @brief this method is called every time a mouse is moved
  /// @param _event the Qt Event structure
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the windows params such as mouse and rotations etc
  //----------------------------------------------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief used to store the global mouse transforms
    //----------------------------------------------------------------------------------------------------------------------
    ngl::Mat4 m_mouseGlobalTX;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the model position for mouse movement
    //----------------------------------------------------------------------------------------------------------------------
    ngl::Vec3 m_modelPos;
    // text for rendering
    //----------------------------------------------------------------------------------------------------------------------
    std::unique_ptr<ngl::Text> m_text;
    /// @brief m_wireframe mode
    bool m_wireframe=false;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the view matrix for camera
    //----------------------------------------------------------------------------------------------------------------------
    static ngl::Mat4 m_view;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the projection matrix for camera
    //----------------------------------------------------------------------------------------------------------------------
    ngl::Mat4 m_projection;
    bool m_transformLight=false;
    ngl::Vec4 m_lightPos;
    /// @brief load the texture and store the id in m_textureName
    //----------------------------------------------------------------------------------------------------------------------
    void loadTexture();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief opengl texture id for the crate texture
    //----------------------------------------------------------------------------------------------------------------------
    GLuint m_textureName;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief method to load transform matrices to the shader
    //----------------------------------------------------------------------------------------------------------------------
    void loadMatricesToShader();
    /// @brief Qt Event called when a key is pressed
    /// @param [in] _event the Qt event to query for size etc
    //----------------------------------------------------------------------------------------------------------------------
    void keyPressEvent(QKeyEvent *_event) override;
    /// @brief Qt Event called when a key is pressed
    /// @param [in] _event the Qt event to query for size etc
    //----------------------------------------------------------------------------------------------------------------------void keyPressEvent(QKeyEvent *_event) override;
  void mouseMoveEvent (QMouseEvent * _event   ) override;
  /// @brief this method is called everytime the mouse button is pressed
  /// inherited from QObject and overridden here.
  /// @param _event the Qt Event structure

  void mousePressEvent ( QMouseEvent *_event  ) override;

  /// @brief this method is called everytime the mouse button is released
  /// inherited from QObject and overridden here.
  /// @param _event the Qt Event structure
  void mouseReleaseEvent (QMouseEvent *_event ) override;
  void wheelEvent( QWheelEvent* _event ) override;


};

#endif
