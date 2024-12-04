#ifndef _5X5_XO_H
#define _5X5_XO_H

#include "BoardGame_Classes.h"
#include <bits/stdc++.h>


using namespace std;

template <typename T>
class FiveByFiveBoard : public Board<T> {
public:
    FiveByFiveBoard() {
        this->rows = this->columns = 5;
        this->board = new T*[this->rows];
        for (int i = 0; i < this->rows; ++i) {
            this->board[i] = new T[this->columns];
            for (int j = 0; j < this->columns; ++j) {
                this->board[i][j] = '\0';
            }
        }
        this->n_moves = 0;
    }

    ~FiveByFiveBoard() {
        for (int i = 0; i < this->rows; ++i) {
            delete[] this->board[i];
        }
        delete[] this->board;
    }

    bool update_board(int x, int y, T symbol) override {
        if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != '\0') {
            return false;
        }
        this->board[x][y] = symbol;
        this->n_moves++;
        return true;
    }

    void display_board() override {
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->columns; ++j) {
                cout << (this->board[i][j] == '\0' ? '.' : this->board[i][j]) << " ";
            }
            cout << endl;
        }
    }

    int countSequences(T player) {
        int count = 0;

        // Check rows
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j <= 2; j++) {
                if (this->board[i][j] == player && this->board[i][j + 1] == player && this->board[i][j + 2] == player) {
                    count++;
                }
            }
        }

        // Check columns
        for (int j = 0; j < this->columns; j++) {
            for (int i = 0; i <= 2; i++) {
                if (this->board[i][j] == player && this->board[i + 1][j] == player && this->board[i + 2][j] == player) {
                    count++;
                }
            }
        }

        // Check diagonals
        for (int i = 0; i <= 2; i++) {
            for (int j = 0; j <= 2; j++) {
                if (this->board[i][j] == player && this->board[i + 1][j + 1] == player && this->board[i + 2][j + 2] == player) {
                    count++;
                }
                if (this->board[i][j + 2] == player && this->board[i + 1][j + 1] == player && this->board[i + 2][j] == player) {
                    count++;
                }
            }
        }

        return count;
    }

    bool is_win() override {
        int cs1 = countSequences('X'), cs2 = countSequences('O');
        return ((cs1 > cs2) || (cs2 > cs1)) && (this->n_moves == 24);
    }

    bool is_draw() override {
        return this->n_moves >= 25 && !is_win();
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }


};

template <typename T>
class FiveByFivePlayer : public Player<T> {
public:
    FiveByFivePlayer(string name, T symbol) : Player<T>(name, symbol) {}

    void getmove(int& x, int& y) override {
        cout << this->name << "'s turn. Enter move (row and column, 0-based): ";
        cin >> x >> y;
    }
};

template <typename T>
class  FivebyFiveRandomPlayer : public Player<T> {
public:
    FivebyFiveRandomPlayer(T symbol) : Player<T>("Random", symbol) {}

    void getmove(int& x, int& y) override {
        x = rand() % 5;
        y = rand() % 5;
    }
};



#endif // _5X5_XO_H