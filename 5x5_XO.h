#include <bits/stdc++.h>
using namespace std;
#include "board_games.h"
#ifndef BOARD_GAMES_5X5_XO_H
#define BOARD_GAMES_5X5_XO_H

class board_5x5 : public Board {
    char board[5][5];
    char current_player;
    bool is_player1_turn;
};

#endif //BOARD_GAMES_5X5_XO_H
