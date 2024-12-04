#include "BoardGame_Classes.h"
#include <bits/stdc++.h>


using namespace std;

#ifndef BOARD_GAMES_NUMERICAL_TIC_H
#define BOARD_GAMES_NUMERICAL_TIC_H

template <typename T>
class NumericalTicTacToe : public Board<T> {
public:
    NumericalTicTacToe() {
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

    ~NumericalTicTacToe() {
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
                this->board[x][y] = symbol;
            }

            return true;
        }
        return false;
    }

    void display_board() override {
        for (int i = 0; i < this-> rows; ++i) {
            for(int j = 0; j< this->columns; ++j){
                if(this->board[i][j] == 0) cout<<'.';
                else cout << this->board[i][j];
                cout << ' ';
            }
            cout << endl;
        }
    }

    bool is_win() override{

        // Check rows
        for (int i = 0; i <this->rows ; ++i) {
            int sum = 0;
            for(int j = 0; j < this->columns; ++j){
                sum += this->board[i][j];
            }
            if(sum == 15) return true;
        }

        // Check Columns
        for (int i = 0; i <this->columns ; ++i) {
            int sum = 0;
            for (int j = 0; j <this->rows; ++j) {
                sum += this->board[j][i];
            }
            if(sum == 15) return true;
        }
        // Check diagonals
        int sum = 0;
        for (int i = 0; i < this->rows; i++) {
            sum += this->board[i][i];
        }
        if (sum == 15) return true;

        sum = 0;
        for (int i = 0; i < this->rows; i++) {
            sum += this->board[i][this->columns - i - 1];
        }
        if (sum == 15) return true;

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
class NumericalTicTacToe_Player : public Player<T> {
private:
    set <int> used;
public:
    NumericalTicTacToe_Player(string name, T symbol) : Player<T>(name, symbol) {}

    void get_value(T &symbol) {
        int p = symbol;
        if(p % 2 == 1){
            do{
                cout << "Enter the number you want to put (1 to 9): ";
                cin >> symbol;

            }while(symbol < 1 || symbol > 9 || symbol % 2 == 0 || used.count(symbol));
        }else{
            do{
                cout << "Enter the number you want to put (2 to 8): ";
                cin >> symbol;
            }while(symbol < 2 || symbol > 8 || symbol % 2 != 0 || used.count(symbol));
        }
        used.insert(symbol);
    }

    void getmove(int& x, int& y) override {
        get_value(this->symbol);
        cout << this->name << "'s turn. Enter move (row and column, 0-based): ";
        cin >> x >> y;
    }

};

template <typename T>
class NumericalTicTacToe_Random_Player : public Player<T> {
public:
    NumericalTicTacToe_Random_Player(T symbol) : Player<T>("Computer", symbol) {}

    void getmove(int& x, int& y) override {
        this->symbol = (rand() % 9);
        if (this->symbol % 2 == 1) this->symbol++;
        this->symbol %= 8;
        x = rand() % 3;
        y = rand() % 3;
    }
};

#endif //BOARD_GAMES_NUMERICAL_TIC_H
