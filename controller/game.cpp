#include <functional>
#include <ratio>

#include <QElapsedTimer>

#include "model/scene.hpp"
#include "model/player.hpp"

#include "game.hpp"
#include "inputeventmanager.hpp"
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

    format.setVersion(3, 3);
    format.setOption(QSurfaceFormat::DeprecatedFunctions, false);
    format.setOption(QSurfaceFormat::DebugContext);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setSwapInterval(1);

    QSurfaceFormat::setDefaultFormat(format);
    qDebug() << "new default format: " << QSurfaceFormat::defaultFormat();
}

qint64 measureNsec(std::function<void()> function)
{
    static QElapsedTimer timer;
    timer.restart();

    function();

    return timer.nsecsElapsed();
}

int Game::exec()
{
    QElapsedTimer gameTimer;
    QElapsedTimer fpsTimer;
    QElapsedTimer fpsUpdateTimer;

    InputEventManager inputEventManager;
    Player player;
    Scene scene(modelDirectory, player);

    setOpenGLParameters();

    MainWindow mainWindow;
    OpenGLWidget &openGlWidget = mainWindow.getOpenGlWidget();
    QStatusBar &statusBar = *mainWindow.statusBar();

    connect(&mainWindow, &MainWindow::closed,
            [this]()
    {
        this->isRunning = false;
    });

    scene.loadModels();
    scene.createNodeForModel("ground", "models/ground.obj");
    scene.createNodeForModel("static_tank", "models/tank.obj");

    player.getAttachedNode().setInputEventManager(&inputEventManager);
    player.setSpeed(5);

    openGlWidget.setInputEventManager(&inputEventManager);
    openGlWidget.setScene(&scene);
    openGlWidget.attachCameraToPlayer(player);

    QString statusBarText("%1 FPS."
                          " Frame: %2 micro sec."
                          " OpenGL: %3 nsec."
                          " QT events: %4 micro sec."
                          " Input events: %5 nsec.");

    mainWindow.show();
    isRunning = true;
    fpsUpdateTimer.start();
    gameTimer.start();

    qint64 frameTime = 0;
    while (isRunning)
    {
        fpsTimer.restart();

        qint64 qtEventsTime = measureNsec([&]()
        {
            processEvents(QEventLoop::AllEvents);
        });

        qint64 inputEventHandlerTime = measureNsec([&]()
        {
            float secondsElapsed = frameTime / static_cast<float>(std::nano::den);
            inputEventManager.processEvents(secondsElapsed);
        });

        openGlWidget.setTime(gameTimer.elapsed());

        qint64 openglTime = measureNsec([&]()
        {
            openGlWidget.update();
        });

        if (fpsUpdateTimer.elapsed() >= std::milli::den)
        {
            frameTime = fpsTimer.nsecsElapsed();
            qint64 fps = std::nano::den / frameTime;

            statusBar.showMessage(statusBarText
                                  .arg(fps)
                                  .arg(frameTime / std::kilo::num)
                                  .arg(openglTime)
                                  .arg(qtEventsTime / std::kilo::num)
                                  .arg(inputEventHandlerTime));
            fpsUpdateTimer.restart();
        }
    }

    return 0;
}
