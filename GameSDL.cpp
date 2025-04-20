#include "GameSDL.h"
#include <SDL_ttf.h>
#include <SDL_mixer.h>

GameSDL::GameSDL() {
    window = nullptr;
    renderer = nullptr;
    font = nullptr;
    moveSound = nullptr;
    screenWidth = GRID_SIZE * TILE_SIZE;
    screenHeight = GRID_SIZE * TILE_SIZE + SCORE_AREA_HEIGHT;
}

GameSDL::~GameSDL() {
    cleanUp();
}

bool GameSDL::init() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
        return false;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

    if (TTF_Init() == -1) {
        cout << "SDL_ttf could not initialize! TTF Error: " << TTF_GetError() << endl;
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cout << "SDL_mixer could not initialize! Mix Error: " << Mix_GetError() << endl;
        return false;
    }

    font = TTF_OpenFont("Arial.ttf", 26);
    if (!font) {
        cout << "Failed to load font! TTF Error: " << TTF_GetError() << endl;
        return false;
    }

    moveSound = Mix_LoadWAV("move.wav");
    if (!moveSound) {
        cout << "Failed to load move sound! Mix Error: " << Mix_GetError() << endl;
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

    SDL_Rect scoreArea = {0, 0, screenWidth, SCORE_AREA_HEIGHT};
    SDL_SetRenderDrawColor(renderer, 220, 220, 220, 255);
    SDL_RenderFillRect(renderer, &scoreArea);

    SDL_Color textColor = {0, 0, 0, 255};

    string scoreText = "Score: " + to_string(game.getScore());
    string bestScoreText = "Best: " + to_string(game.getBestScore());

    SDL_Surface* scoreSurface = TTF_RenderText_Blended(font, scoreText.c_str(), textColor);
    SDL_Surface* bestScoreSurface = TTF_RenderText_Blended(font, bestScoreText.c_str(), textColor);

    SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
    SDL_Texture* bestScoreTexture = SDL_CreateTextureFromSurface(renderer, bestScoreSurface);

    SDL_Rect scoreRect = {10, 10, scoreSurface->w, scoreSurface->h};
    SDL_Rect bestScoreRect = {screenWidth - bestScoreSurface->w - 10, 10, bestScoreSurface->w, bestScoreSurface->h};

    SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
    SDL_RenderCopy(renderer, bestScoreTexture, NULL, &bestScoreRect);

    SDL_FreeSurface(scoreSurface);
    SDL_FreeSurface(bestScoreSurface);
    SDL_DestroyTexture(scoreTexture);
    SDL_DestroyTexture(bestScoreTexture);

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            SDL_Rect tile = { j * TILE_SIZE, i * TILE_SIZE + SCORE_AREA_HEIGHT, TILE_SIZE, TILE_SIZE };

            int value = game.getValue(i, j);
            SDL_Color tileColor = getTileColor(value);
            SDL_SetRenderDrawColor(renderer, tileColor.r, tileColor.g, tileColor.b, tileColor.a);
            SDL_RenderFillRect(renderer, &tile);

            if (value != 0) {
                SDL_Color textColor = { 0, 0, 0, 255 };
                string text = to_string(value);
                SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), textColor);
                SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

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

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (int i = 0; i <= GRID_SIZE; ++i) {
        SDL_RenderDrawLine(renderer, 0, i * TILE_SIZE + SCORE_AREA_HEIGHT, screenWidth, i * TILE_SIZE + SCORE_AREA_HEIGHT);
        SDL_RenderDrawLine(renderer, i * TILE_SIZE, SCORE_AREA_HEIGHT, i * TILE_SIZE, screenHeight);
    }

    SDL_RenderPresent(renderer);
}

void GameSDL::handleEvents(Game& game, bool& running) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            cout << "Exiting game...\n";
            cout << "Your Score: " << game.getScore() << endl;
            cout << "Best Score: " << game.getBestScore() << endl;
            running = false;
        } else if (e.type == SDL_KEYDOWN) {
            bool moved = false;
            switch (e.key.keysym.sym) {
                case SDLK_UP: moved = game.move('w'); break;
                case SDLK_DOWN: moved = game.move('s'); break;
                case SDLK_LEFT: moved = game.move('a'); break;
                case SDLK_RIGHT: moved = game.move('d'); break;
                case SDLK_ESCAPE:
                    cout << "Exiting game...\n";
                    cout << "Your Score: " << game.getScore() << endl;
                    cout << "Best Score: " << game.getBestScore() << endl;
                    running = false;
                    break;
            }
            if (moved) {
                Mix_PlayChannel(-1, moveSound, 0);
                game.spawnNewTile();
                render(game);
            }
        }
    }
}

void GameSDL::cleanUp() {
    if (moveSound) {
        Mix_FreeChunk(moveSound);
        moveSound = nullptr;
    }
    Mix_Quit();

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

SDL_Color GameSDL::getTileColor(int value) {
    switch (value) {
        case 2:    return {238, 228, 218, 255};
        case 4:    return {237, 224, 200, 255};
        case 8:    return {242, 177, 121, 255};
        case 16:   return {245, 149, 99, 255};
        case 32:   return {246, 124, 95, 255};
        case 64:   return {246, 94, 59, 255};
        case 128:  return {237, 207, 114, 255};
        case 256:  return {237, 204, 97, 255};
        case 512:  return {237, 200, 80, 255};
        case 1024: return {237, 197, 63, 255};
        case 2048: return {237, 194, 46, 255};
        default:   return {205, 193, 180, 255};
    }
}
