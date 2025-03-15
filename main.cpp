// main.cpp
#include "Game.h"
#include "GameSDL.h"

int main(int argc, char* argv[]) {
    Game game;
    GameSDL gameSDL;

    if (!gameSDL.init()) {
        return -1;
    }

    bool running = true;
    while (running) {
    gameSDL.handleEvents(game, running);
    gameSDL.render(game);

    if (game.hasWon()) {
        cout << "Congratulations! You won by reaching 2048!\n";
        running = false;
    }
    if (game.isGameOver()) {
        running = false;
    }

    SDL_Delay(100);
}
    gameSDL.cleanUp();
    return 0;
}
