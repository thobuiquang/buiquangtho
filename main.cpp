#include <stdio.h>
#include <SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[]) {
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;

    // 1️⃣ Khởi tạo SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Lỗi SDL: %s\n", SDL_GetError());
        return 1;
    } else {
        // 2️⃣ Tạo cửa sổ
        window = SDL_CreateWindow("Hướng dẫn SDL",
                                  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  SCREEN_WIDTH, SCREEN_HEIGHT,
                                  SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("Không thể tạo cửa sổ! SDL_Error: %s\n", SDL_GetError());
            SDL_Quit();
            return 1;
        } else {
            // 3️⃣ Lấy bề mặt của cửa sổ
            screenSurface = SDL_GetWindowSurface(window);
            if (screenSurface == NULL) {
                printf("Lỗi: Không lấy được surface! SDL_Error: %s\n", SDL_GetError());
                SDL_DestroyWindow(window);
                SDL_Quit();
                return 1;
            }

            // 4️⃣ Tô màu đỏ cho bề mặt
            printf("Đang tô màu đỏ...\n");
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0x00, 0x00));
            SDL_UpdateWindowSurface(window);
            printf("Đã tô màu đỏ!\n");

            // 5️⃣ Giữ cửa sổ mở cho đến khi người dùng đóng
            SDL_Event e;
            bool quit = false;
            printf("Chạy vòng lặp sự kiện...\n");
            while (!quit) {
                while (SDL_PollEvent(&e)) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                }
            }
        }

        // 6️⃣ Hủy cửa sổ và thoát SDL
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
    return 0;
}
