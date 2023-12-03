/**
 * @file reversi.c
 * @author <-- Your name here-->
 * @brief This file is used for APS105 Lab 8. 2023W version
 * @date 2023-03-14
 * 
 */

// DO NOT REMOVE THE FOLLOWING LINE
#if !defined(TESTER_P1) && !defined(TESTER_P2)
// DO NOT REMOVE THE ABOVE LINE
#include "reversi.h"
// DO NOT REMOVE THE FOLLOWING LINE
#endif
// DO NOT REMOVE THE ABOVE LINE

void printBoard(char board[][26], int n) {
}

bool positionInBounds(int n, int row, int col) {
}

bool checkLegalInDirection(char board[][26], int n, int row, int col,
                           char colour, int deltaRow, int deltaCol) {

}



bool displayValidMoves(char board[][26], int n, char colour) {
    for (int unoccupiedRow = 0; unoccupiedRow < n; unoccupiedRow++) {
        for (int unoccupiedCol = 0; unoccupiedCol < n; unoccupiedCol++) {
            if (board[unoccupiedRow][unoccupiedCol] == 'U') {
                for (int deltaRow = -1; deltaRow <= 1; deltaRow++) {
                    for (int deltaCol = -1; deltaCol <= 1; deltaCol++) {
                        if (deltaRow != 0 || deltaCol != 0) {
                            if (checkLegalInDirection(board, n, unoccupiedRow, unoccupiedCol, colour, deltaRow, deltaCol)) {
                                // Counts the number of legal moves
                                return true;
                                // Prevents checking the same space when legal direction is already found (+= 2 or greater is valid)
                                deltaRow += 69;
                                deltaCol += 69;
                            }
                        }
                    }
                }
            }
        }
    }
    // If no legal move found return false
    return false;
}

void flip(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) {
    // These place down the new token
    board[row][col] = colour;
    row += deltaRow;
    col += deltaCol;
    // While loop flips the existing tokens
    while (board[row][col] != colour) {
        board[row][col] = colour;
        row += deltaRow;
        col += deltaCol;
    }
}

int flipCounting(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) {
    int flipCounter = 0;
    row += deltaRow;
    col += deltaCol;
    // While loop counts the number of token that can be flipped in this direction
    while (board[row][col] != colour) {
        flipCounter++;
        row += deltaRow;
        col += deltaCol;
    }
    return flipCounter;
}

int checkingValidMoves(char board[][26], int n, int row, int col, char colour) {
    int counter = 0;
    if (positionInBounds(n, row, col)) {
        if (board[row][col] == 'U') {
            for (int deltaRow = -1; deltaRow <= 1; deltaRow++) {
                for (int deltaCol = -1; deltaCol <= 1; deltaCol++) {
                    if (deltaRow != 0 || deltaCol != 0) {
                        if (checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol)) {
                            flip(board, n, row, col, colour, deltaRow, deltaCol);
                            counter++;
                        }
                    }
                }
            }
        }
    }
    if (counter == 0) {
        printf("Invalid move.\n");
    }
    return counter;
}

int movePriority(char board[][26], int n, int row, int col, char colour) {
    int moveRank;
    if (board[row][col] == 'U') {
        if ((row == 0 && col == 0) || (row == 0 && col == n - 1) || (row == n - 1 && col == 0) || (row == n - 1 && col == n - 1 )) {
            moveRank = 1;
            return moveRank;
        } else if ((row >= 0 && row < 2 && col >= 0 && col < 2) || (row >= 0 && row < 2 && col >= n - 2 && col < n) || (row >= n - 2 && row < n && col >= 0 && col < 2) || (row >= n - 2 && row < n && col >= n - 2 && col < n)) {
            moveRank = 5;
            return moveRank;
        } else if ((row == 0) || (row == n - 1) || (col == 0) || (col == n - 1)) {
            moveRank = 3;
            return moveRank;
        } else if ((n >= 8 && row >= n/2 - 2 && row <= n/2 + 1 && col >= n/2 - 2 && col <= n/2 + 1)) {
            moveRank = 2;
            return moveRank;
        } else {
            moveRank = 4;
            return moveRank;
        }
    }
}

int executeComputerMove(char board[][26], int n, int row, int col, char colour) {
    int counter = 6;
    if (positionInBounds(n, row, col)) {
        if (board[row][col] == 'U') {
            for (int deltaRow = -1; deltaRow <= 1; deltaRow++) {
                for (int deltaCol = -1; deltaCol <= 1; deltaCol++) {
                    if (deltaRow != 0 || deltaCol != 0) {
                        if (checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol)) {
                            return movePriority(board, n, row, col, colour);
                        }
                    }
                }
            }
        }
    }
    return counter;
}

int makeMove(const char board[26][26], int n, char turn, int *row, int *col) {
    int moveRank = 6;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (executeComputerMove(board, n, i, j, turn) < moveRank && board[i][j] == 'U') {
                moveRank = executeComputerMove(board, n, i, j, turn);
                *row = i;
                *col = j;
            }
        }
    }
    return 0;
}

//*******************************************************
// Note: Please only put your main function below
// DO NOT REMOVE THE FOLLOWING LINE
#ifndef TESTER_P2
// DO NOT REMOVE THE ABOVE LINE

int main(void) {
char board[26][26]; // Declaring a static 2D-Array; MAX assumed board dimensions
    int n; // User board input
    char userInput[3]; // For two inputs (row, col)
    char colourComputer;
    char colourPlayer;
    int counterB = 0; // Number of black tokens at end of game
    int counterW = 0; // Number of white tokens at end of game
    int row;
    int col;
    int turns = 0; // Counts every time someone places a token
    int invalidInput = 0; // Becomes 1 if user has invalid input
    printf("Enter the board dimension: ");
    scanf("%d",&n);
    printf("Computer plays (B/W) : ");
    scanf(" %c", &colourComputer);
    fillBoard(board, n);
    printBoard(board, n);
    // Ensures that the player colour is opposite the computers
    if (colourComputer == 'B') {
        colourPlayer = 'W';
    } else {
        colourPlayer = 'B';
    }
    // While loop continues as long as there is a valid move for EITHER colour; breaks once no valid move found
    while (displayValidMoves(board, n, 'B') || displayValidMoves(board, n, 'W')) {
        if (displayValidMoves(board, n, 'B')) {
            if (colourComputer == 'B') {
                makeMove(board, n, colourComputer, &row, &col);
                checkingValidMoves(board, n, row, col, colourComputer);
                // Prints the computer's move
                printf("Computer places %c at %c%c.\n", colourComputer, row + 97, col + 97);
            } else if (colourPlayer == 'B') {
                printf("Enter move for colour %c (RowCol): ", colourPlayer);
                scanf("%s", userInput); // The input is for the row and column (as a string)
                // Calling this function would execute the player's move, if it returns as 0 (no valid move) then computer wins
                if (checkingValidMoves(board, n, userInput[0] - 97, userInput[1] - 97, colourPlayer) == 0) {
                    printf("%c player wins.\n", colourComputer);
                    invalidInput++;
                    break;
                }
            }
            turns++;
            printBoard(board, n);
            if (turns == n*n - 4) {
                break;
            }
        } else {
            printf("B player has no valid move.\n");
        }
        if (displayValidMoves(board, n, 'W')) {
            if (colourComputer == 'W') {
                makeMove(board, n, colourComputer, &row, &col);
                checkingValidMoves(board, n, row, col, colourComputer);
                // Prints the computer's move
                printf("Computer places %c at %c%c.\n", colourComputer, row + 97, col + 97);
            } else if (colourPlayer == 'W') {
                printf("Enter move for colour %c (RowCol): ", colourPlayer);
                scanf("%s", userInput); // The input is for the row and column (as a string)
                // Calling this function would execute the player's move, if it returns as 0 (no valid move) then computer wins
                if (checkingValidMoves(board, n, userInput[0] - 97, userInput[1] - 97, colourPlayer) == 0) {
                    printf("%c player wins.\n", colourComputer);
                    invalidInput++;
                    break;
                }
            }
            turns++;
            printBoard(board, n);
            if (turns == n * n - 4) {
                break;
            }
        } else {
            printf("W player has no valid move.\n");
        }
    }
    if (invalidInput == 0) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 'W') {
                    counterW++;
                } else if (board[i][j] == 'B') {
                    counterB++;
                }
            }
        }
        // In case of tie (white and black tokens have equal amounts)
        if (counterW == counterB) {
            printf("Draw!\n");
        } else if (counterW > counterB) {
            printf("W player wins.\n");
        } else if (counterB > counterW) {
            printf("B player wins.\n");
        }
    }
  return 0;
}

// DO NOT REMOVE THE FOLLOWING LINE
#endif
// DO NOT REMOVE THE ABOVE LINE
//*******************************************************
