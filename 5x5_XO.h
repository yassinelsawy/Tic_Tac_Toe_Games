#ifndef _5X5_XO_H
#define _5X5_XO_H

#include "BoardGame_Classes.h"
#include <bits/stdc++.h>

//=== Text Formatting ===
#define RESET "\033[0m"
#define BLACK "\033[30m"
#define WHITE "\033[37m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define GREEN "\033[32m"
#define CYAN "\033[36m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"

#define BOLD "\033[1m"
#define UNDERLINE "\033[4m"

//If color codes are not working properly uncomment the next section
//  #define RESET ""
//  #define BLACK ""
//  #define WHITE ""
//  #define RED ""
//  #define YELLOW ""
//  #define GREEN ""
//  #define CYAN ""
//  #define BLUE ""
//  #define MAGENTA ""
//  #define BOLD ""
//  #define UNDERLINE ""
// #define UNDERLINE ""

using namespace std;

template <typename T>
class FiveByFiveBoard : public Board<T> {
private:
    int win = 0;
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
        if(this->n_moves == 25){
            return true;
        }
        if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != '\0') {
            return false;
        }
        this->board[x][y] = symbol;
        this->n_moves++;
        return true;
    }

    void display_board() override {
        cout << BLUE << string(60, '=') << RESET << "\n";
        cout << "   " << MAGENTA << setw(2) << "0" << setw(4) << "1" << setw(4) << "2" << setw(4) << "3" << setw(4) << "4" << RESET << "\n";
        cout << "  " << BOLD << setfill('-') << setw(21) << "-" << RESET << setfill(' ') << "\n";
        for (int i = 0; i < this->rows; ++i) {
            cout << MAGENTA << i << RESET << " " << BOLD << "|" << RESET;
            for (int j = 0; j < this->columns; ++j) {
                string color = (this->board[i][j] == 'X') ? GREEN : (this->board[i][j] == 'O') ? RED : BLACK;
                cout << " " << (this->board[i][j] == '\0' ? BLACK "_" RESET : color + string(1, this->board[i][j]) + RESET) << " " << BOLD << "|" << RESET;
            }
            cout << BOLD << " " << RESET << "\n  " << BOLD << setfill('-') << setw(21) << "-" << RESET << setfill(' ') << "\n";
        }
        cout << BLUE << string(60, '=') << RESET << "\n";
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

    int getMoves() {
        return this->n_moves;
    }

    void assign_move(int &x, int &y) {
        for (int i = 0; i < this->rows; i++){
            for(int j = 0; j<this->columns; j++){
                if(this->board[i][j] == '\0'){
                    x = i;
                    y = j;
                    return;
                }
            }
        }
    }
    bool is_win() override {
        int cs1 = countSequences('X'), cs2 = countSequences('O');
        if (win && this->n_moves == 25)  {
            return true;
        }

        if ((cs1 != cs2) && this->n_moves == 24) {
            if (cs2 > cs1) {
                return true;
            }
            else {
                win++;
                return false;
            }
        }
        else {
            return false;
        }
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
private:
    FiveByFiveBoard<T>* brd;

public:
    FiveByFivePlayer(string name, T symbol,FiveByFiveBoard<T>* board) : Player<T>(name, symbol) {
        brd = board;
    }


    void getmove(int& x, int& y) override {
        if(brd->getMoves() == 24){
            brd->assign_move(x, y);
        }
        else{
            cout << this->name << "'s turn. Enter move (row and column, 0-based): ";
            cin >> x >> y;
        }
    }

};

template <typename T>
class  FivebyFiveRandomPlayer : public Player<T> {
public:
    FivebyFiveRandomPlayer(T symbol) : Player<T>("Random", symbol) {}



    void getmove(int& x, int& y) override {
        srand(time(0));
        x = rand() % 5;
        y = rand() % 5;
    }
};



#endif // _5X5_XO_H