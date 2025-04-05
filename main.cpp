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
            cout << "Press SPACE to restart \n";
            bool waitForInput = true;
            while (waitForInput) {
            SDL_Event e;
            SDL_WaitEvent(&e);
            if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_q)) {
            running = false;
            waitForInput = false;
            } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE) {
            game.resetGame();
            waitForInput = false;
                }
            }

        }

        SDL_Delay(100);
    }

    gameSDL.cleanUp();
    return 0;
}
