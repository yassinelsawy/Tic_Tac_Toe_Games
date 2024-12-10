#include "BoardGame_Classes.h"
#include <bits/stdc++.h>
using namespace std;


#ifndef BOARD_GAMES_ULTIMATE_XO_H
#define BOARD_GAMES_ULTIMATE_XO_H

template <typename T>
class Ultimate_XO_Board : public Board<char> {
private:
    char small_board[3][3];

public:
    Ultimate_XO_Board() {
        this->rows = this->columns = 9;
        this->board = new char*[this->rows];
        for (int i = 0; i < this->rows; ++i) {
            this->board[i] = new char[this->columns];
            for (int j = 0; j < this->columns; ++j) {
                this->board[i][j] = '\0';
            }
        }
        this->n_moves = 0;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                small_board[i][j] = '\0';
            }
        }
    }

    ~Ultimate_XO_Board() {
        for (int i = 0; i < this->rows; ++i) {
            delete[] this->board[i];
        }
        delete[] this->board;
    }

    bool update_board(int x, int y, char symbol) override {
        if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != '\0' || small_board[x/3][y/3] != '\0') {
            return false;
        }
        this->board[x][y] = symbol;
        this->n_moves++;
        return true;
    }

    void display_board() override {
        for (int i = 0; i < this->rows; ++i) {
            if (i % 3 == 0 && i != 0) {
                cout << "------+-------+------" << endl;
            }
            for (int j = 0; j < this->columns; ++j) {
                if (j % 3 == 0 && j != 0) {
                    cout << "| ";
                }
                cout << (this->board[i][j] == '\0' ? '.' : this->board[i][j]) << " ";
            }
            cout << endl;
        }
    }

    char check_win(int r, int c) {
        for (int i = r; i < r + 3; i++) {
            if (this->board[i][c+0] == this->board[i][c+1] && this->board[i][c+1] == this->board[i][c+2] && this->board[i][c+0] != 0)
            {
                return this->board[i][c+0];
            }
        }
        for (int j = c; j < c + 3; j++) {
            if (this->board[r+0][j] == this->board[r+1][j] && this->board[r+1][j] == this->board[r+2][j] && this->board[r+0][j] != 0) {
                return this->board[r+0][j];
            }
        }

        // Check diagonals
        if (this->board[r+0][c+0] == this->board[r+1][c+1] && this->board[r+1][c+1] == this->board[r+2][c+2] && this->board[r+0][c+0] != 0) {
            return this->board[r+0][c+0];
        }
        if (this->board[r+0][c+2] == this->board[r+1][c+1] && this->board[r+1][c+1] == this->board[r+2][c+0] && this->board[r+0][c+2] != 0) {
            return this->board[r+0][c+2];
        }
        return '\0';
    }

    bool is_win() override {
        for (int i = 0; i < 3 ; i++) {
            for (int j = 0; j < 3; j++) {
                if (small_board[i][j] == '\0') {
                    char c = check_win(i*3, j*3);
                    small_board[i][j] = c;
                }
            }
        }

//        cout << "----------" << endl;
//        for (int i = 0; i < 3; i++) {
//            for (int j = 0; j < 3; j++) {
//                cout << small_board[i][j] << " ";
//            }
//            cout << endl;
//        }
//        cout << "----------" << endl;

        for (int i = 0; i < 3; i++) {
            if ((this->small_board[i][0] == this->small_board[i][1] && this->small_board[i][1] == this->small_board[i][2] && this->small_board[i][0] != 0) ||
                (this->small_board[0][i] == this->small_board[1][i] && this->small_board[1][i] == this->small_board[2][i] && this->small_board[0][i] != 0)) {
                return true;
            }
        }

        // Check diagonals
        if ((this->small_board[0][0] == this->small_board[1][1] && this->small_board[1][1] == this->small_board[2][2] && this->small_board[0][0] != 0) ||
            (this->small_board[0][2] == this->small_board[1][1] && this->small_board[1][1] == this->small_board[2][0] && this->small_board[0][2] != 0)) {
            return true;
        }

        return false;

    }

    bool is_draw() override {
        return this->n_moves >= 81 && !is_win();
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }
};

template <typename T>
class Ultimate_XO_Player : public Player<T> {
public:
    Ultimate_XO_Player(string name, T symbol) : Player<T>(name, symbol) {}

    void getmove(int& x, int& y) override {
        cout << this->name << " enter your move (x y): ";
        cin >> x >> y;
    }

};

template <typename T>
class Ultimate_XO_Random_Player : public Player<T> {
public:
    Ultimate_XO_Random_Player(T symbol) : Player<T>("Random", symbol) {}

    void getmove(int& x, int& y) override {
        x = rand() % 9;
        y = rand() % 9;
    }
};

#endif //BOARD_GAMES_ULTIMATE_XO_H
