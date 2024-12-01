#include <iostream>
#include "BoardGame_Classes.h"
#include "3x3X_O.h"
#include "5x5_XO.h"


using namespace std;

int main() {
    int choice;
    Player<char>* players[2];
    FiveByFiveBoard<char>*  B = new FiveByFiveBoard<char>();
    string playerXName, player2Name;

    cout << "Welcome to FCAI X-O Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new FiveByFivePlayer<char>(playerXName, 'X');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return 1;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new FiveByFivePlayer<char>(player2Name, 'O');
            break;
//        case 2:
//            players[1] = new X_O_Random_Player<char>('O');
//            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return 1;
    }

    // Create the game manager and run the game
    GameManager<char> FivebyFiveGame(B, players);
    FivebyFiveGame.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    return 0;
}



