#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const int BOARD_SIZE = 3;
const char EMPTY = ' ';
const char USER_MARKER = 'X';
const char COMPUTER_MARKER = 'O';

// Function to print the Tic-Tac-Toe board
void printBoard(const vector<vector<char>>& board) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            cout << board[i][j];
            if (j < BOARD_SIZE - 1) cout << " | ";
        }
        cout << endl;
        if (i < BOARD_SIZE - 1) cout << "---------" << endl;
    }
    cout << endl;
}

// Function to check if a player has won the game
bool isWinner(const vector<vector<char>>& board, char player) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;
    return false;
}

// Function to check if the game is a draw
bool isDraw(const vector<vector<char>>& board) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == EMPTY) return false;
        }
    }
    return true;
}

// Minimax with Alpha-Beta Pruning
int minimax(vector<vector<char>>& board, int depth, bool isMax, int alpha, int beta) {
    if (isWinner(board, USER_MARKER)) return -1; // User wins
    if (isWinner(board, COMPUTER_MARKER)) return 1; // Computer wins
    if (isDraw(board)) return 0; // It's a draw

    if (isMax) {
        int bestScore = numeric_limits<int>::min();
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = COMPUTER_MARKER;
                    int score = minimax(board, depth + 1, false, alpha, beta);
                    board[i][j] = EMPTY;
                    bestScore = max(bestScore, score);
                    alpha = max(alpha, bestScore);
                    if (beta <= alpha) break; // Pruning
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = numeric_limits<int>::max();
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = USER_MARKER;
                    int score = minimax(board, depth + 1, true, alpha, beta);
                    board[i][j] = EMPTY;
                    bestScore = min(bestScore, score);
                    beta = min(beta, bestScore);
                    if (beta <= alpha) break; // Pruning
                }
            }
        }
        return bestScore;
    }
}

// Function to make the computer's move
void makeComputerMove(vector<vector<char>>& board) {
    int bestScore = numeric_limits<int>::min();
    pair<int, int> move = {-1, -1};

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == EMPTY) {
                board[i][j] = COMPUTER_MARKER;
                int score = minimax(board, 0, false, numeric_limits<int>::min(), numeric_limits<int>::max());
                board[i][j] = EMPTY;
                if (score > bestScore) {
                    bestScore = score;
                    move = {i, j};
                }
            }
        }
    }

    board[move.first][move.second] = COMPUTER_MARKER;
}

int main() {
    vector<vector<char>> board(BOARD_SIZE, vector<char>(BOARD_SIZE, EMPTY));
    
    cout << "Tic-Tac-Toe - You are X, and the computer is O." << endl;
    
    while (true) {
        printBoard(board);
        
        // User's move
        int row, col;
        cout << "Enter row (0, 1, 2) and column (0, 1, 2) for your move: ";
        cin >> row >> col;
        
        if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE || board[row][col] != EMPTY) {
            cout << "Invalid move. Try again." << endl;
            continue;
        }
        
        board[row][col] = USER_MARKER;
        
        if (isWinner(board, USER_MARKER)) {
            printBoard(board);
            cout << "You win!" << endl;
            break;
        }
        
        if (isDraw(board)) {
            printBoard(board);
            cout << "It's a draw!" << endl;
            break;
        }
        
        // Computer's move
        makeComputerMove(board);
        
        if (isWinner(board, COMPUTER_MARKER)) {
            printBoard(board);
            cout << "Computer wins!" << endl;
            break;
        }
        
        if (isDraw(board)) {
            printBoard(board);
            cout << "It's a draw!" << endl;
            break;
        }
    }
    
    return 0;
}
