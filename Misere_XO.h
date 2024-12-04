#include "BoardGame_Classes.h"
#include <bits/stdc++.h>


using namespace std;
#ifndef BOARD_GAMES_MISERE_XO_H
#define BOARD_GAMES_MISERE_XO_H

template <typename T>
class Misere_XO : public Board<T> {
private:
    int win = 0;
public:
    Misere_XO() {
        this->rows = this->columns = 3;
        this->board = new T*[this->rows];
        for(int i = 0; i< this->rows; i ++){
            this->board[i] = new T[this->columns];
            for(int j = 0; j<this->columns; j++){
                this->board[i][j] = 0;
            }
        }
        this->n_moves = 0;
    }

    ~Misere_XO() {
        for (int i = 0; i < this->rows; i++) {
            delete[] this->board[i];
        }
        delete[] this->board;
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
    void display_board() override {
        for (int i = 0; i < this-> rows; ++i) {
            for(int j = 0; j< this->columns; ++j){
                cout << (this->board[i][j] == 0 ? '.' : this->board[i][j]) << " ";
            }
            cout << endl;
        }
    }

//    bool is_loss(){
//        // Check rows and columns
//        for (int i = 0; i < this->rows; i++) {
//            if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
//                (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0)) {
//                return false;
//            }
//        }
//
//        // Check diagonals
//        if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
//            (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)) {
//            return false;
//        }
//        return true;
//    }

    bool is_win() override {
        if (win) return true;
        // Check rows and columns
        for (int i = 0; i < this->rows; i++) {
            if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
                (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0)) {
                if(!win){
                    win++;
                    return false;
                }
            }
        }

        // Check diagonals
        if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
            (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)) {
            if(!win){
                win++;
                return false;
            }
        }
        return false;
    }

    bool is_draw() override{
        return (this->n_moves == 9 && !is_win());
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }

};

template <typename T>
class Misere_XO_Player : public Player<T> {
public:
    Misere_XO_Player(string name , T symbol) :  Player<T>(name , symbol){

    }

    void getmove(int& x , int& y) override{
        cout << this->name << "'s turn. Enter move (row and column, 0-based): ";
        cin >> x >> y;
    }

};

template <typename T>
class Misere_XO_Random_Player : public Player<T> {
public:
    Misere_XO_Random_Player(T symbol) :  Player<T>("Random", symbol){}

    void getmove(int& x , int& y) override{
        x = rand() % 3;
        y = rand() % 3;
    }
};

#endif //BOARD_GAMES_MISERE_XO_H
