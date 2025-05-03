#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

class Game {
private:
    int score;  // Điểm hiện tại
    int bestScore;  // Điểm cao nhất
    static const int SIZE = 4;  // Kích thước bảng 2048 4x4
    int board[SIZE][SIZE];  // Mảng 2D lưu trữ giá trị của các ô trong bảng
    bool moved;  // Cờ kiểm tra xem có di chuyển bất kỳ ô nào trong lượt đi hiện tại không

    void addRandomTile();  // Thêm một ô mới 2 hoặc 4
    void rotateBoard();  // Xoay bảng 90 độ
    bool moveLeft();  // Di chuyển các ô về phía bên trái, đồng thời gộp các ô cùng giá trị nếu có
    bool canMove();  // Kiểm tra xem còn nước đi nào không

public:
    Game();

    int getScore() const { return score; }  // Trả về điểm hiện tại
    int getBestScore() const { return bestScore; }  // Trả về điểm cao nhất
    int getValue(int row, int col) const { return board[row][col]; }  // Trả về giá trị của ô tại vị trí (row, col)
    bool move(char direction);  // Xử lý di chuyển
    void spawnNewTile();  // Thêm một ô random mới vào bảng sau mỗi lượt đi hợp lệ
    bool isGameOver();  // Kiểm tra game có kết thúc hay không
    bool hasMoved() const { return moved; }  // Kiểm tra xem có di chuyển ô nào trong lượt đi hiện tại không
    bool hasWon();  // Kiểm tra người chơi có đạt được ô 2048 chưa
    void resetGame();  // Đặt lại game
};

#endif
