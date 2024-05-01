#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

#define SIZE 3
#define EMPTY '.'
#define PLAYER_X 'X'
#define PLAYER_O 'O'

using namespace std;

// arrays, get "decayed" into a pointer to its first element, therefore, no copy is
// created here, despite the array not explicitly being passed by pointer or reference
void initBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = EMPTY;
        }
    }
}

void printBoard(const char board[SIZE][SIZE]) {
    cout << endl;
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (j == SIZE - 1) cout << board[i][j] << endl;
            else cout << board[i][j] << ' ';
        }
    }
    cout << endl;
}

void promptInput(char board[SIZE][SIZE], const bool turnX) {
    string input;
    int vals[2];
    int inputCount = 0;
    
    cout << "Enter the row and column separated by a space: ";
    getline(cin, input);
    stringstream inputStream(input);
    
    while (!inputStream.eof()) {
        if (inputCount < 2) {
            // an alternative to using fail() function to check for stringstream failbit
            if (!(inputStream >> vals[inputCount++])) {
                cerr << "Input must be positive numbers only!" << endl;
                return promptInput(board, turnX);
            }
        } else {
            cerr << "Invalid input format!" << endl;
            return promptInput(board, turnX);
        }
    }
    if (inputCount < 2) {
        cerr << "Invalid input format!" << endl;
        return promptInput(board, turnX);
    }
    if (vals[0] < 1 || vals[0] > SIZE || vals[1] < 1 || vals[1] > SIZE) {
        cerr << "Numbers must be between 1 and " << SIZE << " only!" << endl;
        return promptInput(board, turnX);
    }
    vals[0] -= 1;
    vals[1] -= 1;
    
    if (board[vals[0]][vals[1]] != EMPTY) {
        cerr << "That cell is already filled!" << endl;
        return promptInput(board, turnX);
    }
    board[vals[0]][vals[1]] = turnX ? PLAYER_X : PLAYER_O;
}

bool getWinHorizontal(const char board[SIZE][SIZE], char charToCheck) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] != charToCheck) break; // skip row if cell doesn't contain proper letter
            if (j == SIZE - 1) return true;        // win condition is met
        }
    }
    return false;
}

bool getWinVertical(const char board[SIZE][SIZE], char charToCheck) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[j][i] != charToCheck) break;
            if (j == SIZE - 1) return true;
        }
    }
    return false;
}

// diagonal (top-left to bottom-right)
bool getWinDescending(const char board[SIZE][SIZE], char charToCheck) {
    for (int i = 0; i < SIZE; i++) {
        if (board[i][i] != charToCheck) return false;
    }
    return true;
}

// diagonal (bottom-left to top-right)
bool getWinAscending(const char board[SIZE][SIZE], char charToCheck) {
    for (int i = 0; i < SIZE; i++) {
        if (board[SIZE - 1 - i][i] != charToCheck) return false;
    }
    return true;
}

bool getWin(const char board[SIZE][SIZE], bool turnX) {
    char c = turnX ? PLAYER_X : PLAYER_O;
    
    return getWinHorizontal(board, c) || getWinVertical(board, c) ||
           getWinDescending(board, c) || getWinAscending(board, c);
}

int main() {
    char board[SIZE][SIZE];
    bool turnX = true;
    int numMovesMade = 0;
    
    initBoard(board);
    
    while (true) {
        char player = turnX ? PLAYER_X : PLAYER_O;
        
        cout << player << "'s turn:" << endl;
        printBoard(board);
        promptInput(board, turnX);
        numMovesMade++;
        
        if (getWin(board, turnX)) {
            printBoard(board);
            cout << player << " wins!" << endl;
            break;
        }
        if (numMovesMade == SIZE * SIZE) {
            printBoard(board);
            cout << "Stalemate!" << endl;
            break;
        }
        turnX = !turnX;
    }
    return 0;
}