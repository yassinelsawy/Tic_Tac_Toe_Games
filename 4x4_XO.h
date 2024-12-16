#include "BoardGame_Classes.h"
#include <bits/stdc++.h>


using namespace std;
#ifndef BOARD_GAMES_4X4_XO_H
#define BOARD_GAMES_4X4_XO_H

template <typename T>
class FourByFour_XO_Board : public Board<T> {
public:
    FourByFour_XO_Board(){
        this->rows = 4;
        this->columns = 4;
        this->board = new T*[this->rows];
        string xo = "OX"; int ind = 1;
        for(int i = 0; i< this->rows; i ++){
            this->board[i] = new T[this->columns];
            for(int j = 0; j<this->columns; j++){
                ind = 1 - ind;
                if (i == 0) {
                    this->board[i][j] = xo[ind];
                }
                else if (i == 3) {
                    this->board[i][j] = xo[1-ind];
                }
                else {
                    this->board[i][j] = 0;
                }
            }
        }


        this->n_moves = 0;
    }

    ~FourByFour_XO_Board() {
        for (int i = 0; i < this->rows; i++) {
            delete[] this->board[i];

        }
        delete[] this->board;
    }

    void validate_token(int& x, int& y, T symbol) {
        while (x < 0 || x >= 4 || y < 0 || y >= 4 || this->board[x][y] != symbol) {
            cout << "Invalid token position. Enter a token position (row and column, 0-based): ";
            cin >> x >> y;
        }
    }

    bool update_board(int x, int y, T symbol) override{
        if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || symbol == 0)) {
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

    void delete_old(int x, int y) {
        this->board[x][y] = 0;
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
        // Check rows and columns
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns - 2; j++) {
                if ((this->board[i][j] == this->board[i][j+1] && this->board[i][j+1] == this->board[i][j+2] && this->board[i][j] != 0) ||
                    (this->board[j][i] == this->board[j+1][i] && this->board[j+1][i] == this->board[j+2][i] && this->board[j][i] != 0)) {
                    return true;
                }
            }
        }
        // Check diagonals
        for (int i = 0; i < this->rows - 2; i++) {
            for (int j = 0; j < this->columns - 2; j++) {
                if ((this->board[i][j] == this->board[i+1][j+1] && this->board[i+1][j+1] == this->board[i+2][j+2] && this->board[i][j] != 0) ||
                    (this->board[i][j+2] == this->board[i+1][j+1] && this->board[i+1][j+1] == this->board[i+2][j] && this->board[i][j+2] != 0)) {
                    return true;
                }
            }
        }
        return false;
    }

    bool is_draw() override {
        return this->n_moves == 16 && !is_win();
    }

    bool game_is_over() override {
        return this->is_win() || this->is_draw();
    }


};

template <typename T>
class FourByFour_XO_Player : public Player<T> {
private:
    FourByFour_XO_Board<T>* brd;
public:
    FourByFour_XO_Player(string name, T symbol, FourByFour_XO_Board<T>* board) : Player<T>(name, symbol) {
        brd = board;
    }

    void getmove(int& x, int& y) override {
        cout << this->name << "'s turn. Enter a token position (row and column, 0-based): ";
        int a, b; cin >> a >> b;
        brd->validate_token(a, b, this->symbol);
        brd->delete_old(a, b);
        cout << this->name << "'s turn. Enter move (row and column, 0-based): ";
        cin >> x >> y;
        while (!((x == a && abs(y - b) == 1) || (y == b && abs(x - a) == 1))) {
            cout << "Invalid move. Enter a move (row and column, 0-based): ";
            cin >> x >> y;
        }
    }
};

template <typename T>
class FourByFour_XO_Random_Player : public Player<T> {
public:
    FourByFour_XO_Random_Player(T symbol) : Player<T>("Random", symbol) {}

    void getmove(int& x, int& y) override {
        x = rand() % 4;
        y = rand() % 4;
    }
};

#endif //BOARD_GAMES_4X4_XO_H
