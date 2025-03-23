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
    private:
    int score;
    int bestScore;
    static const int SIZE = 4;
    int board[SIZE][SIZE];
    bool moved;

    void addRandomTile();
    void rotateBoard();
    bool moveLeft();
    bool canMove();

public:
    Game();
    int getScore() const { return score; }
    int getBestScore() const { return bestScore; }
    int getValue(int row, int col) const { return board[row][col]; }
    bool move(char direction);  // Trả về true nếu có sự di chuyển
    void spawnNewTile();  // Thêm ô mới sau mỗi lần di chuyển
    void printBoard();
    bool isGameOver();
    bool hasMoved() const { return moved; }
    bool hasWon();

};

#endif // G
