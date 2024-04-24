#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "NGLScene.h"
#include <QKeyEvent>



namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *_event) override;

private:
    Ui::MainWindow *m_ui;
		/// @brief our openGL widget
		NGLScene *m_gl;


};

#endif // MAINWINDOW_H
