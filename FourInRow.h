#include <bits/stdc++.h>
using namespace std;
#include "BoardGame_Classes.h"

#ifndef BOARD_GAMES_FOURINROW_H
#define BOARD_GAMES_FOURINROW_H


template <typename T>
class FourInRow : public Board<T> {
public:
    FourInRow(){
        this->rows = 6;
        this->columns = 7;
        this->board = new T*[this->rows];
        for(int i = 0; i< this->rows; i ++){
            this->board[i] = new T[this->columns];
            for(int j = 0; j<this->columns; j++){
                this->board[i][j] = 0;
            }
        }
        this->n_moves = 0;
    }

    ~FourInRow() {
        for (int i = 0; i < this->rows; i++) {
            delete[] this->board[i];

        }
        delete[] this->board;
    }

    bool update_board(int x, int y, T symbol) override{
        if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || symbol == 0)) {
            if (x != this->rows - 1 && this->board[x+1][y] == 0) return false;
            if (symbol == 0){
                this->n_moves--;
                this->board[x][y] = 0;
            }
            else {
                this->n_moves++;
                this->board[x][y] = toupper(symbol);
            }

            return true;
        }
        return false;

    }
    void display_board() override {
        for (int i = 0; i < this-> rows; ++i) {
            for(int j = 0; j< this->columns; ++j){
                cout << (this->board[i][j] == 0 ? '.' : this->board[i][j]) << " ";
            }
            cout << endl;
        }
    }

    bool is_win() override {
        // Check on rows
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns - 3; j++) {
                bool ck = 1;
                for (int k = j; k < j + 3; k++) {
                    if ((this->board[i][k] != this->board[i][k+1]) || (this->board[i][k] == 0)) ck = 0;
                }
                if (ck)
                    return true;
            }
        }
        // check columns
        for(int i = 0; i<this->columns; i++){
            for(int j = 0; j<this->rows - 3; j++){
                bool ck = 1;
                for (int k = j; k < j + 3; k++) {
                    if ((this->board[k][i] != this->board[k + 1][i]) || (this->board[k][i] == 0)) ck = 0;
                }
                if (ck)
                    return true;
            }
        }

        // Check Secondary Diagonal
        for(int i = 0; i<this->rows - 3; i++){
            for(int j = 0; j<this->columns - 3; j++){
                bool ck = 1;
                for (int k = 0; k < 3; k++) {
                    if ((this->board[i + k][j + k] != this->board[i + k + 1][j + k + 1]) || (this->board[i + k][j + k] == 0)) ck = 0;
                }
                if (ck)
                    return true;
            }
        }

        // Check Primary Diagonal
        for(int i = 3; i<this->rows ; i++){
            for(int j = 0; j<this->columns - 3; j++){
                bool ck = 1;
                for (int k = 0; k < 3; k++) {
                    if ((this->board[i - k][j + k] != this->board[i - k - 1][j + k + 1]) || (this->board[i - k][j + k] == 0)) ck = 0;
                }
                if (ck)
                    return true;
            }
        }
        return false;
    }

    bool is_draw() override {
        return (this->n_moves == this->rows * this->columns) && !is_win();
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }

    void computer_move(T symbol){
        int x, y;
        do {
            x = rand() % this->rows;
            y = rand() % this->columns;
        } while (!update_board(x, y, symbol));
    }
};

template <typename T>
class FourInRow_Player : public Player<T> {
public:
    FourInRow_Player(string name, T symbol) : Player<T>(name, symbol) {}

    void getmove(int &x, int &y) override {
        cout << this->name << "'s turn. Enter move (row and column, 0-based): ";
        cin >> x >> y;
    }
};
#endif //BOARD_GAMES_FOURINROW_H
