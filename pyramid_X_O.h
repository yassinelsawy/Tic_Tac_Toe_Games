#include <bits/stdc++.h>
using namespace std;
#include "BoardGame_Classes.h"

#ifndef BOARD_GAMES_PYRAMID_X_O_H
#define BOARD_GAMES_PYRAMID_X_O_H

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
class Pyramid_X_O_Board : public Board<T> {
public:
   Pyramid_X_O_Board(){
       this->rows = 3;
       this->columns = 5;

        int inc = 4;
        this->board = new T*[this->rows];
        for (int i = 0; i < this->rows; i++) {
            this->board[i] = new T[this->columns];
            for (int j = 0; j < this->columns; j++) {
                this->board[i][j] = '-';
            }
            for (int j = i + (inc -= 2); j <= i + 2; j++) {
                this->board[i][j] = 0;
            }
        }
        this->n_moves = 0;
   }

   ~Pyramid_X_O_Board(){
       for (int i = 0; i < this->rows ; ++i) {
           delete [] this->board[i];
       }
       delete [] this->board;
   }

   bool update_board(int x, int y, T symbol) override {
       if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| symbol == 0)) {
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
        cout << MAGENTA << setw(5) << "0" << setw(4) << "1" << setw(4) << "2" << setw(4) << "3" << setw(4) << "4" << RESET << "\n";
        cout << string(10, ' ') << BOLD << setfill('-') << setw(5) << "-" << RESET << setfill(' ') << "\n";
        for (int i = 0; i < this->rows; i++) {
            int num = 6 - 3 * i;
            if (i == 1) num++;
            cout << MAGENTA << i << RESET << " " << string(num, ' ') << setw(num) << BOLD << "|";
            for (int j = 0; j < this->columns; j++) {
                if (!(this->board[i][j] == '-')) {
                    string color = (this->board[i][j] == 'X') ? GREEN : RED;
                    cout << " " << (this->board[i][j] == 0 ? string(BLACK "_") + RESET : color + string(1, this->board[i][j]) + RESET) << " " << BOLD << "|";
                }
            }
            cout << RESET << "\n" << string(4 - 2 * i + 2, ' ') << BOLD << setfill('-') << setw(25 - 4 * (this->rows - i)) << "-" << RESET << setfill(' ') << "\n";
        }
        cout << BLUE << string(60, '=') << RESET << "\n";
    }


    bool is_win() override{
       // Check rows
       if ((this->board[1][1] == this->board[1][2] && this->board[1][2] == this->board[1][3] && this->board[1][3] != 0)
            || (this->board[2][0] == this->board[2][1] && this->board[2][1] == this->board[2][2] && this->board[2][2] != 0)
            || (this->board[2][1] == this->board[2][2] && this->board[2][2] == this->board[2][3] && this->board[2][3] != 0)
            || (this->board[2][2] == this->board[2][3] && this->board[2][3] == this->board[2][4] && this->board[2][4] != 0)
            ) {
              return true;
       }
       // Check center column
       if (this->board[0][2] == this->board[1][2] && this->board[1][2] == this->board[2][2] && this->board[2][2] != 0) {
              return true;
       }

       // Check diagonals
       if ((this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[2][0] != 0) ||
            (this->board[0][2] == this->board[1][3] && this->board[1][3] == this->board[2][4]) && this->board[2][4] != 0) {
             return true;
       }
       return false;
   }

   bool is_draw() override{
       return (this->n_moves == 9 && !is_win());
   }

    bool game_is_over() override{
         return is_win() || is_draw();
    }


};

template <typename T>
class Pyramid_X_O_Player : public Player<T> {
public:
    Pyramid_X_O_Player(string name , T symbol) :  Player<T>(name , symbol){}

    void getmove(int& x , int& y) override{
        cout << this->name << "'s turn. Enter move (row and column, 0-based): ";
        cin >> x >> y;
    }

};

template <typename T>
class Pyramid_X_O_Random_Player : public Player<T> {
public:
    Pyramid_X_O_Random_Player(T symbol) :  Player<T>("Random", symbol){}

    void getmove(int& x , int& y) override{
        srand(time(0));
        x = rand() % 3;
        y = rand() % 5;
    }
};



#endif //BOARD_GAMES_PYRAMID_X_O_H
