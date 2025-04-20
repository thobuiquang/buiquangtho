#ifndef GAME_SDL_H
#define GAME_SDL_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include "Game.h"

using namespace std;

const int SCORE_AREA_HEIGHT = 50;
const int TILE_SIZE = 100;
const int GRID_SIZE = 4;

class GameSDL {
private:
    TTF_Font* font;
    SDL_Window* window;
    SDL_Renderer* renderer;
    int screenWidth;
    int screenHeight;
    SDL_Color getTileColor(int value);
    Mix_Chunk* moveSound;

public:
    GameSDL();
    ~GameSDL();
    bool init();
    void render(Game& game);
    void handleEvents(Game& game, bool& running);
    void cleanUp();
};

#endif
