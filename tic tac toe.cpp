#include <iostream>
#include <vector>

using namespace std;

// Function to print the Tic-Tac-Toe board
void printBoard(const vector<vector<char>>& board) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << endl;
        if (i < 2) cout << "---------" << endl;
    }
}

// Function to check if a player has won
bool checkWin(const vector<vector<char>>& board, char player) {
    // Check rows, columns, and diagonals
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return true;
    }  
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return true;
    
    return false;
}

int main() {
    vector<vector<char>> board(3, vector<char>(3, ' ')); // Initialize the empty board
    bool player1Turn = true; // Player 1 starts

    cout << "Welcome to Tic-Tac-Toe!" << endl;

    for (int turn = 0; turn < 9; ++turn) {
        // Print the current state of the board
        printBoard(board);

        // Determine the current player
        char currentPlayer = (player1Turn) ? 'X' : 'O';
        cout << "Player " << currentPlayer << ", enter row (0-2) and column (0-2): ";
        
        int row, col;
        cin >> row >> col;

        // Check if the chosen position is valid
        if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ') {
            cout << "Invalid move. Try again." << endl;
            turn--; // Repeat the current turn
            continue;
        }

        // Update the board with the player's move
        board[row][col] = currentPlayer;

        // Check if the current player has won
        if (checkWin(board, currentPlayer)) {
            printBoard(board);
            cout << "Player " << currentPlayer << " wins!" << endl;
            return 0;
        }

        player1Turn = !player1Turn; // Switch to the other player's turn
    }

    // If all turns are taken and no one wins, it's a draw
    printBoard(board);
    cout << "It's a draw!" << endl;

    return 0;
}
