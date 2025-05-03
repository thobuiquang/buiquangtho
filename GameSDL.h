#ifndef GAME_SDL_H
#define GAME_SDL_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include "Game.h"

using namespace std;

const int SCORE_AREA_HEIGHT = 50;  // Chiều cao của khu vực hiển thị điểm số
const int TILE_SIZE = 100;  // Kích thước của mỗi ô trong bảng (100x100)
const int GRID_SIZE = 4;  // Kích thước của bảng game (4x4)

class GameSDL {
private:
    TTF_Font* font;  // Biến giữ đối tượng font cho việc render chữ
    SDL_Window* window;  // Cửa sổ SDL
    SDL_Renderer* renderer;  // Bộ vẽ SDL
    int screenWidth;  // Chiều rộng của cửa sổ
    int screenHeight;  // Chiều cao của cửa sổ
    SDL_Color getTileColor(int value);  // Hàm trả về màu sắc của ô dựa trên giá trị của ô đó
    Mix_Chunk* moveSound;  // Âm thanh khi người chơi di chuyển các ô

public:
    GameSDL();   // Hàm tạo
    ~GameSDL();  // Hàm hủy
    bool init();  // Khởi tạo các thành phần của SDL
    void render(Game& game);  // Vẽ lại toàn bộ game lên màn hình
    void handleEvents(Game& game, bool& running);  // Xử lý sự kiện bàn phím, đóng cửa sổ, điều khiển game
    void cleanUp();  // Giải phóng bộ nhớ SDL
    void showScoreWindow(int score, int bestScore);  // Hiển thị cửa sổ game over với điểm hiện tại và điểm cao nhất

};

#endif
