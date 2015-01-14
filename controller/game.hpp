#pragma once

#include <QApplication>

class Game : protected QApplication
{
public:
    Game(int &argc, char **argv, int flags = ApplicationFlags);
    ~Game();

    int exec();
private:
    void setOpenGLParameters();

    bool isRunning;
};
