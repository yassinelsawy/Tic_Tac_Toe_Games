#include <iostream>
#include "BoardGame_Classes.h"
#include "3x3X_O.h"
#include "5x5_XO.h"
#include "pyramid_X_O.h"
#include "FourInRow.h"
#include "Numerical_Tic.h"
#include "Misere_XO.h"
#include "Word_TicTac.h"
#include "Ultimate_XO.h"
#include "4x4_XO.h"

using namespace std;


int main() {
    int choice , choice2;
    Player<char>* players[2];
   //FiveByFiveBoard<char>*  B = new FiveByFiveBoard<char>();
//    Pyramid_X_O_Board<char>*  B = new Pyramid_X_O_Board<char>();
//    NumericalTicTacToe<int>*  B = new NumericalTicTacToe<int>();
//    FourInRow<char>*  B = new FourInRow<char>();
   Misere_XO<char>*  B = new Misere_XO<char>();
//    Word_TicTac<char>*  B = new Word_TicTac<char>();
//    Ultimate_XO_Board<char>*  B = new Ultimate_XO_Board<char>();
   //<char>*  B = new FourByFour_XO_Board<char>();

    string player1Name, player2Name;

    cout << "Welcome to FCAI X-O Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> player1Name;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;
    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice2;


    switch(choice) {
        case 1:
            players[0] = new Misere_XO_Player<char>(player1Name, 'X',B);
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return 1;
    }

    char symb = 'O';

    switch(choice2) {
        case 1:
            players[1] = new Misere_XO_Player<char>(player2Name, 'O',B);
            break;
        case 2:
            players[1] = new FivebyFiveRandomPlayer<char>(symb);
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return 1;
    }

    // Create the game manager and run the game
    GameManager<char> FiveByFiveBoard(B, players);
    FiveByFiveBoard.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    return 0;
}



