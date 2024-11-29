#include <bits/stdc++.h>
using namespace std;
#ifndef BOARD_GAME_CLASSES_H
#define BOARD_GAME_CLASSES_H


class Board {
public:
    virtual void display_board() const = 0;
    virtual bool update_board(int x, int y, char symbol) = 0;
    virtual bool is_win() const = 0;
    virtual bool is_draw() const = 0;
    virtual bool game_is_over() const = 0;
};

class Player {
public:
    string name;
    char symbol;

    Player(const string& name, char symbol) : name(name), symbol(symbol) {}
    virtual void get_move(int& x, int& y) const = 0;
};


class GameManager {
    Board& board;
    Player& player1;
    Player& player2;

public:
    GameManager(Board& board, Player& player1, Player& player2)
        : board(board), player1(player1), player2(player2) {}

    void run() {}
};

#endif // BOARD_GAME_CLASSES_H