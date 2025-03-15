#include "GameSDL.h"
#include <SDL_ttf.h>

GameSDL::GameSDL() {
    window = nullptr;
    renderer = nullptr;
    screenWidth = GRID_SIZE * TILE_SIZE;
    screenHeight = GRID_SIZE * TILE_SIZE;
}

GameSDL::~GameSDL() {
    cleanUp();
}

bool GameSDL::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
        return false;
    }

    if (TTF_Init() == -1) {
        cout << "SDL_ttf could not initialize! TTF Error: " << TTF_GetError() << endl;
        return false;
    }

    font = TTF_OpenFont("D:/SDL2/2048GAME/bin/Debug/Arial.ttf", 24);
    if (!font) {
        cout << "Failed to load font! TTF Error: " << TTF_GetError() << endl;
        return false;
    }

    window = SDL_CreateWindow("2048 Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    if (!window) {
        cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
        return false;
    }

    return true;
}

void GameSDL::render(Game& game) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Vẽ các ô và số
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            SDL_Rect tile = { j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE };

            // Chọn màu ô dựa vào giá trị
            SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
            SDL_RenderFillRect(renderer, &tile);

            int value = game.getValue(i, j);
            if (value != 0) {
                SDL_Color textColor = { 0, 0, 0, 255 };
                string text = to_string(value);
                SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
                SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

                // Căn giữa số trong ô
                int textWidth = textSurface->w;
                int textHeight = textSurface->h;
                SDL_Rect textRect = {
                    tile.x + (TILE_SIZE - textWidth) / 2,
                    tile.y + (TILE_SIZE - textHeight) / 2,
                    textWidth,
                    textHeight
                };

                SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
                SDL_FreeSurface(textSurface);
                SDL_DestroyTexture(textTexture);
            }
        }
    }

    // Vẽ lưới ô vuông
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Màu đen cho đường kẻ
    for (int i = 1; i < GRID_SIZE; ++i) {
        SDL_RenderDrawLine(renderer, 0, i * TILE_SIZE, screenWidth, i * TILE_SIZE); // Đường ngang
        SDL_RenderDrawLine(renderer, i * TILE_SIZE, 0, i * TILE_SIZE, screenHeight); // Đường dọc
    }

    SDL_RenderPresent(renderer);
}

void GameSDL::handleEvents(Game& game, bool& running) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            running = false;
        } else if (e.type == SDL_KEYDOWN) {
            bool moved = false;
            switch (e.key.keysym.sym) {
                case SDLK_UP: moved = game.move('w'); break;
                case SDLK_DOWN: moved = game.move('s'); break;
                case SDLK_LEFT: moved = game.move('a'); break;
                case SDLK_RIGHT: moved = game.move('d'); break;
                case SDLK_q: running = false; break;
            }
            if (moved) {
                game.spawnNewTile();
                render(game);
            }
        }
    }
}

void GameSDL::cleanUp() {
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    TTF_Quit();
    SDL_Quit();
}
