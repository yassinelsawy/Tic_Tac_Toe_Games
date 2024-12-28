#include <bits/stdc++.h>
using namespace std;
#include "BoardGame_Classes.h"

#ifndef BOARD_GAMES_FOURINROW_H
#define BOARD_GAMES_FOURINROW_H
#include "BoardGame_Classes.h"

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
        cout << BLUE << string(60, '=') << RESET << "\n";
        cout << "   " << MAGENTA << setw(2) << "0" << setw(4) << "1" << setw(4) << "2" << setw(4) << "3" << setw(4) << "4" << setw(4) << "5" << setw(4) << "6" << RESET << "\n";
        cout << "  " << BOLD << setfill('-') << setw(29) << "-" << RESET << setfill(' ') << "\n";
        for (int i = 0; i < this->rows; ++i) {
            cout << MAGENTA << i << RESET << " " << BOLD << "|" << RESET;
            for (int j = 0; j < this->columns; ++j) {
                string color = (this->board[i][j] == 'X') ? GREEN : (this->board[i][j] == 'O') ? RED : BLACK;
                cout << " " << (this->board[i][j] == 0 ? BLACK "_" RESET : color + string(1, this->board[i][j]) + RESET) << " " << BOLD << "|" << RESET;
            }
            cout << BOLD << " " << RESET << "\n  " << BOLD << setfill('-') << setw(29) << "-" << RESET << setfill(' ') << "\n";
        }
        cout << BLUE << string(60, '=') << RESET << "\n";
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

        // Check Primary Diagonal
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

        // Check Secondary Diagonal
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

template <typename T>
class FourInRow_Random_Player : public RandomPlayer<T> {
public:
    FourInRow_Random_Player(T symbol) : RandomPlayer<T>(symbol) {}

    void getmove(int &x, int &y) override {
        srand(time(0));
        x = rand() % 6;
        y = rand() % 7;
    }
};
#endif //BOARD_GAMES_FOURINROW_H
