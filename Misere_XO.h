#include "BoardGame_Classes.h"
#include <bits/stdc++.h>


using namespace std;
#ifndef BOARD_GAMES_MISERE_XO_H
#define BOARD_GAMES_MISERE_XO_H

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
        cout << BLUE << string(60, '=') << RESET << "\n";
        cout << "   " << MAGENTA << setw(2) << "0" << setw(4) << "1" << setw(4) << "2" << RESET << "\n";
        cout << "  " << BOLD << setfill('-') << setw(13) << "-" << RESET << setfill(' ') << "\n";
        for (int i = 0; i < this->rows; ++i) {
            cout << MAGENTA << i << RESET << " " << BOLD << "|" << RESET;
            for (int j = 0; j < this->columns; ++j) {
                string color = (this->board[i][j] == 'O') ? RED : GREEN;
                cout << " " << (this->board[i][j] == 0 ? BLACK "_" RESET : color + string(1, this->board[i][j]) + RESET) << " " << BOLD << "|" << RESET;
            }
            cout << BOLD << " " << RESET << "\n  " << BOLD << setfill('-') << setw(13) << "-" << RESET << setfill(' ') << "\n";
        }
        cout << BLUE << string(60, '=') << RESET << "\n";
    }

    bool is_win() override {
        if (win)
            return true;
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
        return (win > 1) || is_draw();
    }
    bool getWin(){
        return win;
    }

    int getMoves() {
        return this->n_moves;
    }
    void assign_move(int &x, int &y) {
        if (this->n_moves == 9) this->board[0][0] = '\0';
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
};

template <typename T>
class Misere_XO_Player : public Player<T> {
private:
    Misere_XO<T>* brd;
public:
    Misere_XO_Player(string name , T symbol,Misere_XO<T>* board) :  Player<T>(name , symbol){
        brd = board;
    }

    void getmove(int& x , int& y) override{
        if(brd->getWin() && brd->getMoves() <= 9){
            if (brd->getMoves() <= 9) {
                brd->assign_move(x,y);
            }
            return;
        }

        cout << this->name << "'s turn. Enter move (row and column, 0-based): ";
        cin >> x >> y;
    }

};

template <typename T>
class Misere_XO_Random_Player : public Player<T> {
public:
    Misere_XO_Random_Player(T symbol) :  Player<T>("Random", symbol){}

    void getmove(int& x , int& y) override{
        srand(time(0));
        x = rand() % 3;
        y = rand() % 3;
    }
};

#endif //BOARD_GAMES_MISERE_XO_H
