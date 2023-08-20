/**
 * @file reversi.c
 * @author Arrad Mostafa
 * @brief This file is used for APS105 Lab 8. 2023W version
 * @date 2023-03-14
 * 
 */

// DO NOT REMOVE THE FOLLOWING LINE
#if !defined(TESTER_P1) && !defined(TESTER_P2)
// DO NOT REMOVE THE ABOVE LINE
//#include "reversi.h"                                      // remember to uncomment this
// DO NOT REMOVE THE FOLLOWING LINE
#endif
// DO NOT REMOVE THE ABOVE LINE

#include <stdio.h>                              // idk if i should remove this when submitting or not
#include <stdbool.h>
#include <stdlib.h>

void printBoard(char board[][26], int dimension) {
  printf("  ");
      for (int i = 97; i < 97 + dimension; i++) {
          printf("%c", i);
      }
      printf("\n");
      for (int i = 0; i < dimension;) {
          for (int x = 0; x < dimension; x++){
              printf("%c ", x + 97);
              for (int j = 0; j < dimension; j++) {
                  printf("%c", board[i][j]);
              }
              printf("\n");
              i++;
          }
      }
}

bool positionInBounds(int dimension, int row, int col) {
  if ((row < dimension && col < dimension) && (row >= 0 && col >= 0)) {
        return true;
    }
    return false;
}

bool checkLegalInDirection(char board[][26], int dimension, int row, int col, char colour, int deltaRow, int deltaCol) {
  char otherPlayer;
    if (colour == 'W') {
        otherPlayer = 'B';
    }
    else {
        otherPlayer = 'W';
    }

    if ((deltaCol == 0 && deltaRow == 0) || (!positionInBounds(dimension, row + deltaRow, col + deltaCol) || board[row + deltaRow][col + deltaCol] != otherPlayer)) {
        return false;
    }

    while (positionInBounds(dimension, row, col)) {
        row += deltaRow;
        col += deltaCol;
        if (!positionInBounds(dimension, row, col)) {
            return false;
        }

        if (board[row][col] == 'U') {
            return false;
        }
        
        else if (board[row][col] == colour) {
            return true;
        }
        
    } 

    return false;
}

bool valid_move_possible(int dimension, char board[][26], char color){
    int count = 0, variable = 0; 
    int moves = 0;
        for (int x = 0; x < dimension; x++) {
            for (int y = 0; y < dimension; y++) {
                if (board[x][y] == 'U') {
                    for (int dirRow = -1; dirRow <= 1; dirRow++) {
                        for (int dirCol = -1; dirCol <= 1; dirCol++) {
                            if (checkLegalInDirection(board, dimension, x, y, color, dirRow, dirCol)) {
                                if (count == count + variable){
                                count += 1;
                                }
                                variable += 1;
                                moves++;
                            }
                        }
                    }
                }
                count = 0;
                variable = 0;
            }
        }
    if (moves > 0) {
        return true;
    }
    else if (moves == 0) {
        return false;
    }
}

int makeMove(char board[26][26], int dimension, char color, int *row, int *col) {
    int count = 0, variable = 0; 
    int score = 0, temp_score;
    temp_score = score;
    for (int x = 0; x < dimension; x++) {
            for (int y = 0; y < dimension; y++) {
                if (board[x][y] == 'U') {
                    for (int dirRow = -1; dirRow <= 1; dirRow++) {
                        for (int dirCol = -1; dirCol <= 1; dirCol++) {
                            if (checkLegalInDirection(board, dimension, x, y, color, dirRow, dirCol)) {
                                if (count == count + variable){
                                count += 1;
                                }
                                variable += 1;
                                temp_score += 1;
                                if (temp_score > score) {
                                    score = temp_score;
                                    *row = x;
                                    *col = y;
                                }
                                
                            }
                        }
                    }
                }
                count = 0;
                variable = 0;
                temp_score = 0;
            }
        }
    return score;
}

//*******************************************************
// Note: Please only put your main function below
// DO NOT REMOVE THE FOLLOWING LINE
#ifndef TESTER_P2
// DO NOT REMOVE THE ABOVE LINE

int main(void) {
    int dimension = 0;
    char player_1[4];
    char computer[4];
    char board [26][26];
    bool check = false;
    printf("Enter the board dimension: ");
    scanf("%d", &dimension);
    printf("Computer plays (B/W): ");
    scanf(" %c", &computer[0]);
    if (computer[0] == 'B') {
        player_1[0] = 'W';
    }
    else if (computer[0] == 'W') {
        player_1[0] = 'B';
    }
    
    printf("  ");
    for (int i = 97; i < 97 + dimension; i++) {
        printf("%c", i);
    }
    printf("\n");
    for (int x = 0; x < dimension; x++){
        printf("%c ", x + 97);
        for (int y = 0; y < dimension; y++){
            if ((x == (dimension/2 - 1) && y == (dimension/2 - 1)) || (x == (dimension/2) && y == (dimension/2))) {
                board[x][y] = 'W';
                printf("%c", board[x][y]);
            }
            else if ((x == (dimension/2 - 1) && y == (dimension/2)) || (x == (dimension/2) && y == (dimension/2 - 1))) {
                board[x][y] = 'B';
                printf("%c", board[x][y]);
            }
            else {
                board[x][y] = 'U';
                printf("%c", board[x][y]);
            }
        }
        printf("\n");
    }


    while (valid_move_possible(dimension, board, player_1[0]) || valid_move_possible(dimension, board, computer[0])){

        if (computer[0] == 'W') {
            printf("Enter move for color B (RowCol): ");
            scanf(" %c%c", &player_1[1], &player_1[2]);
            int row = player_1[1] - 'a';
            int col = player_1[2] - 'a';
            int row_temp = row;
            int col_temp = col;
            bool possible = false, possible_temp = false;
            if (valid_move_possible(dimension, board, player_1[0])) {
                for (int dirRow = -1; dirRow <= 1; dirRow++) {
                    for (int dirCol = -1; dirCol <= 1; dirCol++) {
                        possible = checkLegalInDirection(board, dimension, row, col, player_1[0], dirRow, dirCol);
                        if (possible == true){
                            possible_temp = true;
                        }
                    }
                }

                if(row >= dimension || row < 0 || col >= dimension || col < 0 || !possible_temp){
                    printf("\nInvalid move.\n");
                    printf("%c player wins", &computer[0]);
                    return 0;
                }
                else{
                    for (int dirRow = -1; dirRow <= 1; dirRow++) {
                        for (int dirCol = -1; dirCol <= 1; dirCol++) {
                            if (checkLegalInDirection(board, dimension, row, col, player_1[0], dirRow, dirCol)) {
                                check = true;
                                row = row + dirRow;
                                col = col + dirCol;
                                while (board[row][col] == computer[0]) {
                                    board[row][col] = player_1[0];
                                    row = row + dirRow;
                                    col = col + dirCol;
                                }
                            }
                            row = row_temp;
                            col = col_temp;
                        }
                    }
                }
                
                if (check && positionInBounds(dimension, row, col)) {
                    board[row][col] = player_1[0];
                    printBoard(board, dimension);
                }
            }

            else if (!valid_move_possible(dimension, board, player_1[0])) {
                printf("%c player has no valid moves.\n", player_1[0]);
            }
            
            if (valid_move_possible(dimension, board, computer[0])) {
                printf("Computer places %c at ", computer[0]);
                int score = 0;
                int row_highest, col_highest;
                score = makeMove(board, dimension, computer[0], &row_highest, &col_highest);
                char letter_row[3];                         // tried for a long time and this still doesnt work. 
                itoa(*row_highest, letter_row, 10);
                char letter_col[3];
                itoa(*col_highest, letter_col, 10);
                printf("%c%c\n", letter_row[0], letter_col[0]);
                computer[1] = letter_row[0];
                computer[2] = letter_col[0];
                int row_temp_computer = row_highest;
                int col_temp_computer = col_highest;

                for (int dirRow = -1; dirRow <= 1; dirRow++) {
                    for (int dirCol = -1; dirCol <= 1; dirCol++) {
                        if (checkLegalInDirection(board, dimension, row_highest, col_highest, computer[0], dirRow, dirCol)) {
                            check = true;
                            row_highest = row_highest + dirRow;
                            col_highest = col_highest + dirCol;
                            while (board[row_highest][col_highest] == player_1[0]) {
                                board[row_highest][col_highest] = computer[0];
                                row_highest = row_highest + dirRow;
                                col_highest = col_highest + dirCol;
                            }
                        }
                        row_highest = row_temp_computer;
                        col_highest = col_temp_computer;
                    }
                }

                if (check && positionInBounds(dimension, row_highest, col_highest)) {
                    board[row_highest][col_highest] = computer[0];
                    printBoard(board, dimension);
                }
            }

            else if (!valid_move_possible(dimension, board, computer[0])) {
                printf("%c player has no valid moves.\n", computer[0]);
            }
        }

        else if (computer[0] == 'B') {
            if (valid_move_possible(dimension, board, computer[0])) {
                printf("Computer places %c at ", computer[0]);
                int score = 0;
                int row_highest, col_highest;
                score = makeMove(board, dimension, computer[0], &row_highest, &col_highest);
                char letter_row = row_highest;
                char letter_col = col_highest;
                printf("%c%c\n", &letter_row, &letter_col);
                computer[1] = letter_row;
                computer[2] = letter_col;
                int row_temp_computer = row_highest;
                int col_temp_computer = col_highest;

                for (int dirRow = -1; dirRow <= 1; dirRow++) {
                    for (int dirCol = -1; dirCol <= 1; dirCol++) {
                        if (checkLegalInDirection(board, dimension, row_highest, col_highest, computer[0], dirRow, dirCol)) {
                            check = true;
                            row_highest = row_highest + dirRow;
                            col_highest = col_highest + dirCol;
                            while (board[row_highest][col_highest] == player_1[0]) {
                                board[row_highest][col_highest] = computer[0];
                                row_highest = row_highest + dirRow;
                                col_highest = col_highest + dirCol;
                            }
                        }
                        row_highest = row_temp_computer;
                        col_highest = col_temp_computer;
                    }
                }

                if (check && positionInBounds(dimension, row_highest, col_highest)) {
                    board[row_highest][col_highest] = computer[0];
                    printBoard(board, dimension);
                }
            }

            else if (!valid_move_possible(dimension, board, computer[0])) {
                printf("%c player has no valid moves.\n", computer[0]);
            }


            printf("Enter move for color W (RowCol): ");
            scanf(" %c%c", &player_1[1], &player_1[2]);
            int row = player_1[1] - 'a';
            int col = player_1[2] - 'a';
            int row_temp = row;
            int col_temp = col;
            bool possible = false, possible_temp = false;
            if (valid_move_possible(dimension, board, player_1[0])) {
                for (int dirRow = -1; dirRow <= 1; dirRow++) {
                    for (int dirCol = -1; dirCol <= 1; dirCol++) {
                        possible = checkLegalInDirection(board, dimension, row, col, player_1[0], dirRow, dirCol);
                        if (possible == true){
                            possible_temp = true;
                        }
                    }
                }

                if(row >= dimension || row < 0 || col >= dimension || col < 0 || !possible_temp){
                    printf("\nInvalid move.\n");
                    printf("%c player wins", &computer[0]);
                    return 0;
                }
                else{
                    for (int dirRow = -1; dirRow <= 1; dirRow++) {
                        for (int dirCol = -1; dirCol <= 1; dirCol++) {
                            if (checkLegalInDirection(board, dimension, row, col, player_1[0], dirRow, dirCol)) {
                                check = true;
                                row = row + dirRow;
                                col = col + dirCol;
                                while (board[row][col] == computer[0]) {
                                    board[row][col] = player_1[0];
                                    row = row + dirRow;
                                    col = col + dirCol;
                                }
                            }
                            row = row_temp;
                            col = col_temp;
                        }
                    }
                }
                
                if (check && positionInBounds(dimension, row, col)) {
                    board[row][col] = player_1[0];
                    printBoard(board, dimension);
                }
            }

            else if (!valid_move_possible(dimension, board, player_1[0])) {
                printf("%c player has no valid moves.\n", player_1[0]);
            }
        }
    }


    int score_total_W = 0, score_total_B = 0, empty_tile = 0;
    for (int x = 0; x < dimension; x++){
        for (int y = 0; y < dimension; y++){
            if (board[x][y] == 'W') {
                score_total_W++;
            }
            else if (board[x][y] == 'B') {
                score_total_B++;
            }
            else {
                empty_tile++;
            }
        }
    }

    if (score_total_B > score_total_W) {
        printf("B player wins.");
        return 0;
    }
    else if (score_total_W > score_total_B) {
        printf("W player wins.");
        return 0;
    }
    
}

// The current problem is that it still says that the player has no moves before it
// says that the player that won.


// DO NOT REMOVE THE FOLLOWING LINE
#endif
// DO NOT REMOVE THE ABOVE LINE
//*******************************************************