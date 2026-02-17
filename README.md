# 🎮 Tic-Tac-Toe Games Collection

A comprehensive collection of 8 different Tic-Tac-Toe game variants implemented in C++. This project features multiple game modes with support for both human players and computer AI opponents.

## 📋 Table of Contents
- [Game Variants](#game-variants)
- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [How to Play](#how-to-play)
- [Project Structure](#project-structure)
- [Technologies Used](#technologies-used)

## 🎯 Game Variants

This collection includes 8 unique Tic-Tac-Toe game variations:

1. **Pyramid Tic-Tac-Toe** - A pyramid-shaped board variant
2. **4 in a Row** - Connect four in a row to win
3. **5x5 Tic-Tac-Toe** - Extended 5x5 grid with modified win conditions
4. **Word Tic-Tac-Toe** - Form valid words to score points
5. **Numerical Tic-Tac-Toe** - Use numbers instead of X and O
6. **Misere Tic-Tac-Toe** - Reverse rules: avoid three in a row
7. **Ultimate Tic-Tac-Toe** - Meta game with 9 nested boards
8. **4x4 Tic-Tac-Toe** - 4x4 grid variant

## ✨ Features

- 🤖 **AI Opponent**: Play against a random computer player
- 👥 **Two Player Mode**: Play with a friend locally
- 🎨 **Colorful CLI Interface**: Enhanced terminal display with color coding
- 🔄 **Multiple Game Modes**: Choose from 8 different variants
- 📝 **Input Validation**: Robust error handling and input checking
- 🎲 **Flexible Player Options**: Human vs Human or Human vs Computer

## 🔧 Requirements

- C++ compiler (supporting C++11 or later)
- CMake (optional, for building)
- Terminal with ANSI color support (for colored output)

## 📥 Installation

### Using CMake:
```bash
# Clone the repository
git clone https://github.com/yassinelsawy/Tic_Tac_Toe_Games.git
cd Tic_Tac_Toe_Games

# Build the project
mkdir build
cd build
cmake ..
make

# Run the executable
./Tic_Tac_Toe_Games
```

### Using g++ directly:
```bash
# Clone the repository
git clone https://github.com/yassinelsawy/Tic_Tac_Toe_Games.git
cd Tic_Tac_Toe_Games

# Compile
g++ -std=c++11 main.cpp -o main

# Run
./main
```

### Windows:
```bash
# If you're on Windows, you can run the pre-compiled executable
main.exe
```

## 🎮 How to Play

1. Run the program
2. Choose your preferred game variant from the menu (1-8)
3. Select player types (Human or Random Computer) for both players
4. Enter player names
5. Follow the on-screen instructions to make moves
6. Enjoy the game!

### Controls
- Enter numbers/coordinates as prompted for your moves
- Follow game-specific rules displayed during gameplay
- Type your choice when prompted

## 📁 Project Structure

```
Tic_Tac_Toe_Games/
├── main.cpp                 # Main program entry point
├── BoardGame_Classes.h      # Base classes for board games
├── 3x3X_O.h                # Classic 3x3 Tic-Tac-Toe
├── 4x4_XO.h                # 4x4 variant
├── 5x5_XO.h                # 5x5 variant
├── pyramid_X_O.h           # Pyramid variant
├── FourInRow.h             # Four in a row game
├── Numerical_Tic.h         # Numerical variant
├── Misere_XO.h             # Misere variant
├── Word_TicTac.h           # Word-based variant
├── Ultimate_XO.h           # Ultimate Tic-Tac-Toe
├── dic.txt                 # Dictionary file for Word Tic-Tac-Toe
└── CMakeLists.txt          # CMake configuration file
```

## 🛠️ Technologies Used

- **Language**: C++
- **Build System**: CMake
- **Design Pattern**: Object-Oriented Programming with template classes
- **Features**: 
  - Inheritance and polymorphism
  - Template classes for flexibility
  - ANSI color codes for terminal styling

## 🎨 Terminal Colors

The program uses ANSI escape codes for colored output:
- 🔵 **Blue**: Menu options and headers
- 🔴 **Red**: Error messages
- 🟢 **Green**: Success messages
- 🔵 **Cyan**: User input prompts

> **Note**: If colors don't display properly in your terminal, uncomment the color reset section in `main.cpp`.

## 👥 Authors

Project developed as part of an academic assignment (A2_S7_T235)
- Student IDs: 20230416, 20230465, 20230220

## 📄 License

This project is available for educational purposes.

## 🤝 Contributing

Contributions, issues, and feature requests are welcome!

---

**Enjoy playing! 🎉**