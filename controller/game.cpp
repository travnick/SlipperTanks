#include "model/scene.hpp"

#include "game.hpp"
#include "mainwindow.hpp"

const char modelDirectory[]  = "models";

Game::Game(int &argc, char **argv, int flags):
    QApplication(argc, argv, flags)
{
}

Game::~Game()
{
}

void Game::setOpenGLParameters()
{
    QSurfaceFormat format = QSurfaceFormat::defaultFormat();
    qDebug() << "default format: " << format;

    //    format.setVersion(2, 1);
    format.setOption(QSurfaceFormat::DeprecatedFunctions, true);
    format.setOption(QSurfaceFormat::DebugContext);
    format.setProfile(QSurfaceFormat::CompatibilityProfile);
    format.setSwapInterval(1);

    QSurfaceFormat::setDefaultFormat(format);
    qDebug() << "new default format: " << QSurfaceFormat::defaultFormat();
}

int Game::exec()
{
    setOpenGLParameters();

    MainWindow mainWindow;
    OpenGLWidget &openGlWidget = mainWindow.getOpenGlWidget();

    connect(&mainWindow, &MainWindow::closed,
            [this]()
    {
        this->isRunning = false;
    });

    Scene scene(modelDirectory);
    scene.loadModels();

    openGlWidget.setScene(&scene);

    mainWindow.show();
    isRunning = true;
    while (isRunning)
    {
        processEvents(QEventLoop::AllEvents);
        openGlWidget.processInput();

        openGlWidget.update();
    }

    return 0;
}
