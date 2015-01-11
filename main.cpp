#include "controller/game.hpp"

int main(int argc, char *argv[])
{
    Game game(argc, argv);

    return game.exec();
}
