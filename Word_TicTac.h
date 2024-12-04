#include "BoardGame_Classes.h"
#include <bits/stdc++.h>


using namespace std;

#ifndef BOARD_GAMES_WORD_TICTAC_H
#define BOARD_GAMES_WORD_TICTAC_H

template <typename T>
class Word_TicTac : public Board<T> {
private:
    set <string> dic;

public:
    Word_TicTac() {
        this->rows = this->columns = 3;
        this->board = new T*[this->rows];
        for(int i = 0; i< this->rows; i ++){
            this->board[i] = new T[this->columns];
            for(int j = 0; j<this->columns; j++){
                this->board[i][j] = 0;
            }
        }
        this->n_moves = 0;

        ifstream file("dic.txt");

        string word;
        while (file >> word) {
            dic.insert(word);
        }
    }

    ~Word_TicTac() {
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

    bool is_win() override{
        // Check rows and columns
        for (int i = 0; i < this->rows; i++) {
            string row;
            row += this->board[i][0]; row += this->board[i][1]; row += this->board[i][2];
            string col;
            col += this->board[0][i]; col += this->board[1][i]; col += this->board[2][i];

            if (dic.count(row) || dic.count(col)) return true;
        }

        // Check diagonals
        string dg1;
        dg1 += this->board[0][0]; dg1 += this->board[1][1]; dg1 += this->board[2][2];
        string dg2;
        dg2 += this->board[0][2]; dg2 += this->board[1][1]; dg2 += this->board[2][0];

        if (dic.count(dg1) || dic.count(dg2)) return true;

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
class Word_TicTac_Player : public Player<T> {
public:
    Word_TicTac_Player(string name, T symbol) : Player<T>(name, symbol) {

    }

    void get_value(T &symbol) {
        do{
            cout << "Enter a letter between (A-Z): ";
            cin >> symbol;
            symbol = toupper(symbol);
        }
        while(symbol < 'A' || symbol > 'Z');
    }

    void getmove(int& x, int& y) override {
        get_value(this->symbol);
        cout << this->name << "'s turn. Enter move (row and column, 0-based): ";
        cin >> x >> y;
    }
};

template <typename T>
class Word_TicTac_Random_Player : public RandomPlayer<T> {
public:
    Word_TicTac_Random_Player(T &symbol) : RandomPlayer<T>(symbol) {
        this->name = "Random Computer";
    }

    void getmove(int& x, int& y) override {
        this->symbol = (rand() % 26) + 65;
        x = rand() % 3;
        y = rand() % 3;
    }
};
#endif //BOARD_GAMES_WORD_TICTAC_H
