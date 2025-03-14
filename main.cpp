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
        SDL_Delay(100);  // Prevent CPU from running too fast
    }

    gameSDL.cleanUp();
    return 0;
}
