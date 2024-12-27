#include <iostream>
#include "BoardGame_Classes.h"
#include "5x5_XO.h"
#include "pyramid_X_O.h"
#include "FourInRow.h"
#include "Numerical_Tic.h"
#include "Misere_XO.h"
#include "Word_TicTac.h"
#include "Ultimate_XO.h"
#include "4x4_XO.h"

using namespace std;

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

void getChoice(vector <string> choices, string &choice) {
    while (find(choices.begin(), choices.end(), choice) == choices.end()) {
        cout << RED << "!! Invalid input, please enter a valid choice\n" << RESET
             << CYAN << ">>" << RESET;
        getline(cin, choice);
    }
}

void numberChecker(string &number) {
    while (true) {
        bool isNumber = true;
        for (int i = 0; i < number.size(); i++) {
            if (!isdigit(number[i])) {
                isNumber = false;
                break;
            }
        }
        if (isNumber) {
            break;
        }
        cout << RED << "!! Invalid input, please enter a valid number\n" << RESET
             << CYAN << ">>" << RESET;
        getline(cin, number);
    }
}

void printChoices(vector <string> choices) {
    cout << endl;
    for (int i = 0; i < choices.size(); i++) {
        cout << BLUE << i + 1 << ") " << RESET << choices[i] << endl;
    }
    cout << "<< Choose an option >>\n";
    cout << CYAN << ">>" << RESET;
}

int main() {
    while (true) {
        vector <string> choices = {"Pyramid Tic-Tac-Toe",
                                   "4 in a row",
                                   "5x5 Tic-Tac-Toe",
                                   "Word Tic-Tac-Toe",
                                   "Numerical Tic-Tac-Toe",
                                   "Misere Tic-Tac-Toe",
                                   "Ultimate Tic-Tac-Toe",
                                   "4x4 Tic-Tac-Toe",
                                   "Exit"
                                   };

        cout << setw(75) << UNDERLINE << BLUE << "--> Board Games (Tic-Tac-Toe) <--\n\n" << RESET;
        printChoices(choices);

        string choice;
        getline(cin, choice);
        getChoice({"1", "2", "3", "4", "5", "6", "7", "8", "9"}, choice);

        vector <string> playerChoices = {"Human", "Random Computer"};
        string player1Choice, player2Choice;


        string Player1 , Player2;
        Player<char>* players[2];

        // Set up player 1
        cout << "Enter Player X name: ";
        getline(cin, Player1);
        cout << "Choose Player X type:\n";
        printChoices(playerChoices);
        getline(cin, player1Choice);
        getChoice({"1", "2"}, player1Choice);

        // Set up player 2
        cout << "Enter Player 2 name: ";
        //cin.ignore();
        getline(cin, Player2);
        cout << "Choose Player 2 type:\n";
        printChoices(playerChoices);
        getline(cin, player2Choice);
        getChoice({"1", "2"}, player2Choice);

        if (choice == "1") {
            Pyramid_X_O_Board<char>*  B = new Pyramid_X_O_Board<char>();
            if (player1Choice == "1") {
                players[0] = new Pyramid_X_O_Player<char>(Player1, 'X');
            }
            else {
                players[0] = new Pyramid_X_O_Random_Player<char>('X');
            }
            if (player2Choice == "1"){
                players[1] = new Pyramid_X_O_Player<char>(Player2, 'O');
            }
            else {
                players[1] = new Pyramid_X_O_Random_Player<char>('O');
            }
            GameManager<char> Pyramid_X_O_Board(B, players);
            Pyramid_X_O_Board.run();
            delete B;

        }

        else if (choice == "2") {
            FourInRow<char>*  B = new FourInRow<char>();
            if (player1Choice == "1") {
                players[0] = new FourInRow_Player<char>(Player1, 'X');
            }
            else {
                players[0] = new FourInRow_Random_Player<char>('X');
            }
            if (player2Choice == "1"){
                players[1] = new FourInRow_Player<char>(Player2, 'O');
            }
            else {
                players[1] = new FourInRow_Random_Player<char>('O');
            }
            GameManager<char> FourInRow_Board(B, players);
            FourInRow_Board.run();
            delete B;

        }
        else if (choice == "3") {
            FiveByFiveBoard<char>*  B = new FiveByFiveBoard<char>();
            if (player1Choice == "1") {
                players[0] = new FiveByFivePlayer<char>(Player1, 'X', B);
            }
            else {
                players[0] = new FivebyFiveRandomPlayer<char>('X');
            }
            if (player2Choice == "1"){
                players[1] = new FiveByFivePlayer<char>(Player2, 'O', B);
            }
            else {
                players[1] = new FivebyFiveRandomPlayer<char>('O');
            }
            GameManager<char> FiveByFive_Board(B, players);
            FiveByFive_Board.run();
            delete B;

        }
        else if (choice == "4") {
            Word_TicTac<char>*  B = new Word_TicTac<char>();
            char symb = 0;
            if (player1Choice == "1") {
                players[0] = new Word_TicTac_Player<char>(Player1, symb);
            }
            else {
                players[0] = new Word_TicTac_Random_Player<char>(symb);
            }
            if (player2Choice == "1"){
                players[1] = new Word_TicTac_Player<char>(Player2, symb);
            }
            else {
                players[1] = new Word_TicTac_Random_Player<char>(symb);
            }
            GameManager<char> Word_TicTac_Board(B, players);
            Word_TicTac_Board.run();
            delete B;

        }
        else if (choice == "5") {
            Player<int>* players_[2];

            NumericalTicTacToe<int>*  B = new NumericalTicTacToe<int>();
            int symb1 = 1, symb2 = 2;

            if (player1Choice == "1") {
                players_[0] = new NumericalTicTacToe_Player<int>(Player1, symb1);
            }
            else {
                players_[0] = new NumericalTicTacToe_Random_Player<int>(symb1, B);
            }
            if (player2Choice == "1"){
                players_[1] = new NumericalTicTacToe_Player<int>(Player2, symb2);
            }
            else {
                players_[1] = new NumericalTicTacToe_Random_Player<int>(symb2, B);
            }
            GameManager<int> NumericalTicTacToe_Board(B, players_);
            NumericalTicTacToe_Board.run();
            delete B;
        }

        else if (choice == "6") {
            Misere_XO<char>*  B = new Misere_XO<char>();
            if (player1Choice == "1") {
                players[0] = new Misere_XO_Player<char>(Player1, 'X', B);
            }
            else {
                players[0] = new Misere_XO_Random_Player<char>('X');
            }
            if (player2Choice == "1"){
                players[1] = new Misere_XO_Player<char>(Player2, 'O', B);
            }
            else {
                players[1] = new Misere_XO_Random_Player<char>('O');
            }
            GameManager<char> Misere_XO_Board(B, players);
            Misere_XO_Board.run();
            delete B;

        }
        else if (choice == "7") {
            Ultimate_XO_Board<char>*  B = new Ultimate_XO_Board<char>();
            if (player1Choice == "1") {
                players[0] = new Ultimate_XO_Player<char>(Player1, 'X');
            }
            else {
                players[0] = new Ultimate_XO_Random_Player<char>( "Random", 'X', B);
            }
            if (player2Choice == "1"){
                players[1] = new Ultimate_XO_Player<char>(Player2, 'O');
            }
            else {
                players[1] = new Ultimate_XO_Random_Player<char>("Random", 'O', B);
            }
            GameManager<char> Ultimate_XO_Board(B, players);
            Ultimate_XO_Board.run();
            delete B;

        }
        else if (choice == "8") {
            FourByFour_XO_Board<char>*  B = new FourByFour_XO_Board<char>();

            if (player1Choice == "1") {
                players[0] = new FourByFour_XO_Player<char>(Player1, 'X', B);
            }
            else {
                players[0] = new FourByFour_XO_Random_Player<char>('X', B);
            }
            if (player2Choice == "1"){
                players[1] = new FourByFour_XO_Player<char>(Player2, 'O', B);
            }
            else {
                players[1] = new FourByFour_XO_Random_Player<char>('O', B);
            }
            GameManager<char> FourByFour_XO_Board(B, players);
            FourByFour_XO_Board.run();
            delete B;

        }
        else if (choice == "9") {
            // Clean up
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }
            return 0;
        }
        cin.ignore();
    }
}



