// GameSDL.h
class Game;  // Khai báo trước (forward declaration)
#ifndef GAME_SDL_H
#define GAME_SDL_H
#include <SDL_ttf.h>
#include <SDL.h>
#include <iostream>
#include "Game.h"


using namespace std;
const int SCORE_AREA_HEIGHT = 50;
const int TILE_SIZE = 100;  // Tile size
const int GRID_SIZE = 4;    // 4x4 grid

class GameSDL {
private:
    TTF_Font* font;
    SDL_Window* window;
    SDL_Renderer* renderer;
    int screenWidth;
    int screenHeight;
public:
    GameSDL();
    ~GameSDL();
    bool init();
    void render(Game& game);
    void handleEvents(Game& game, bool& running);
    void cleanUp();
};
#endif
