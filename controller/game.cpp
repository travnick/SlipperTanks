#include "game.hpp"
#include "mainwindow.hpp"

Game::Game(int &argc, char **argv, int flags):
    QApplication(argc, argv, flags)
{

}

Game::~Game()
{

}

int Game::exec()
{
    MainWindow mainWindow;
    OpenGLWidget &openGlWidget = mainWindow.getOpenGlWidget();

    connect(&mainWindow, &MainWindow::closed,
            [this]()
    {
        this->isRunning = false;
    });

    mainWindow.show();

    isRunning = true;
    while (isRunning)
    {
        processEvents(QEventLoop::AllEvents);
        openGlWidget.animate();
        openGlWidget.update();
    }

    return 0;
}
