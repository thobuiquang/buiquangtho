#include "Game.h"

Game::Game() : score(0), bestScore(0) {
    srand(time(0));
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            board[i][j] = 0;
    addRandomTile();
    addRandomTile();
    moved = false;
}

bool Game::hasWon() {
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if (board[i][j] == 2048) return true;
    return false;
}

void Game::addRandomTile() {
    vector<pair<int, int>> emptyCells;
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if (board[i][j] == 0)
                emptyCells.push_back({i, j});

    if (!emptyCells.empty()) {
        int randIndex = rand() % emptyCells.size();
        int value = (rand() % 10 < 9) ? 2 : 4;
        board[emptyCells[randIndex].first][emptyCells[randIndex].second] = value;
    }
}

void Game::rotateBoard() {
    int temp[SIZE][SIZE];
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            temp[j][SIZE - 1 - i] = board[i][j];

    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            board[i][j] = temp[i][j];
}

bool Game::moveLeft() {
    moved = false;
    for (int i = 0; i < SIZE; ++i) {
        int compressed[SIZE] = {0};
        int index = 0;
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] != 0) {
                if (index > 0 && compressed[index - 1] == board[i][j]) {
                    compressed[index - 1] *= 2;
                    score += compressed[index - 1];
                    if (score > bestScore) bestScore = score;
                    moved = true;
                } else {
                    compressed[index++] = board[i][j];
                }
            }
        }
        for (int j = 0; j < SIZE; ++j)
            if (board[i][j] != compressed[j]) moved = true;

        for (int j = 0; j < SIZE; ++j)
            board[i][j] = compressed[j];
    }
    return moved;
}

bool Game::move(char direction) {
    moved = false;
    if (direction == 'a') {
        moved = moveLeft();
    } else if (direction == 'd') {
        rotateBoard();
        rotateBoard();
        moved = moveLeft();
        rotateBoard();
        rotateBoard();
    } else if (direction == 'w') {
        rotateBoard();
        rotateBoard();
        rotateBoard();
        moved = moveLeft();
        rotateBoard();
    } else if (direction == 's') {
        rotateBoard();
        moved = moveLeft();
        rotateBoard();
        rotateBoard();
        rotateBoard();
    }
    return moved;
}

void Game::spawnNewTile() {
    addRandomTile();
}

bool Game::isGameOver() {
    if (!canMove()) {
        cout << "Game Over! No more possible moves.\n";
        cout << "Best Score: " << bestScore << endl;
        return true;
    }
    return false;
}
bool Game::canMove() {
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if (board[i][j] == 0) return true;

    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE - 1; ++j)
            if (board[i][j] == board[i][j + 1]) return true;

    for (int i = 0; i < SIZE - 1; ++i)
        for (int j = 0; j < SIZE; ++j)
            if (board[i][j] == board[i + 1][j]) return true;

    return false;
}
void Game::resetGame() {
    score = 0;
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            board[i][j] = 0;

    addRandomTile();
    addRandomTile();
    moved = false;
}
