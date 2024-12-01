#include <bits/stdc++.h>
using namespace std;
#include "BoardGame_Classes.h"

#ifndef BOARD_GAMES_PYRAMID_X_O_H
#define BOARD_GAMES_PYRAMID_X_O_H

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

//   ~Pyramid_X_O_Board(){
//       for (int i = 0; i < this->rows ; ++i) {
//           delete [] this->board[i];
//       }
//       delete [] this->board;
//   }

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
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                if (this->board[i][j] == '-') cout << " ";
                else if (this->board[i][j] == 0) cout << ".";
                else cout << this->board[i][j];
                cout << " ";
            }
            cout << endl;
        }

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

    void computer_move(T symbol){
        int x, y;
        do {
            x = rand() % this->rows;
            y = rand() % this->columns;
        } while (!update_board(x, y, symbol));
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




#endif //BOARD_GAMES_PYRAMID_X_O_H
