#ifndef SOLVE_CONTEXT_H
#define SOLVE_CONTEXT_H

#define ALL_POSSIBILITIES 0x3FE

#include "src/solve/utils.h"

int solved_count;
int guess_depth;
int solve_board[9][9];
int guess_depths[9][9];
bool guesses[9][9];

int rows[9];
int cols[9];
int boxes[9];

void set_value(int row, int col, int value, bool is_guess) {
  solve_board[row][col] = value;
  guesses[row][col] = is_guess;
  guess_depths[row][col] = guess_depth;
  solved_count++;

  int bI = boxIndex(row, col);

  rows[row] |= numToBit(value);
  cols[col] |= numToBit(value);
  boxes[bI] |= numToBit(value);
}

void init_solve_context(int &src_board[][]) {
  solved_count = 0;
  guess_depth = 0;

  for (int i = 0; i < 9; i++) {
    rows[i] = 0;
    cols[i] = 0;
    boxes[i] = 0;

    for (int j = 0; j < 9; j++) {
      solve_board[i][j] = 0;
      guess_depths[i][j] = 0;
      guesses[i][j] = false;
    }
  }

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (src_board[i][j] != 0) {
        set_value(i, j, src_board[i][j], false);
      }
    }
  }
}

void reset_guess(int &guess_row, int &guess_col, int &guessed_value) {
  for (int r = 0; r < 9; r++) {
    for (int c = 0; c < 9; c++) {
      if (guess_depths[r][c] == guess_depth) {
        int value = solve_board[r][c];

        if (guesses[r][c]) {
          guess_row = r;
          guess_col = c;
          guessed_value = value;
        }

        solved_count--;
        solve_board[r][c] = 0;
        guesses[r][c] = false;
        guess_depths[r][c] = 0;

        int bI = boxIndex(r, c);

        rows[r] &= ~numToBit(value);
        cols[c] &= ~numToBit(value);
        boxes[bI] &= ~numToBit(value);
      }
    }
  }
}

bool isPossibility(int r, int c, int x) {
  int bI = boxIndex(r, c);
  int valueBit = numToBit(x);

  bool notInRow = (rows[r] & valueBit) == 0;;
  bool notInCol = (cols[c] & valueBit) == 0;
  bool notInBox = (boxes[bI] & valueBit) == 0;

  return notInRow && notInCol && notInBox;
}

int countPossibilities(int r, int c) {
  int count = 0;
  for (int i = 1; i <= 9; i++) {
    if (isPossibility(r, c, i)) {
      count++;
    }
  }
  return count;
}

int getSinglePossibility(int r, int c) {

  int bI = boxIndex(r, c);
  
  int singlePossibility = -1;

  for (int i = 1; i <= 9; i++) {
    if (isPossibility(r, c, i)) {
      if (singlePossibility > 0) {
        return 0;
      }
      singlePossibility = i;
    }
  }

  return singlePossibility;
}

int nextPossibility(int r, int c, int last_guess) {
  for (int i = last_guess + 1; i < 10; i++) {
    if (isPossibility(r, c, i)) {
      return i;
    }
  }
  return -1;
}

// Returns whether or not a board is a valid, solved sudoku
bool is_valid_solution() {
  // Check if the sudoku is solved and valid
  int rows[9];
  int cols[9];
  int boxes[9];

  for (int i = 0; i < 9; i++) {
    rows[i] = 0;
    cols[i] = 0;
    boxes[i] = 0;
  }

  for (int r = 0; r < 9; r++) {
    for (int c = 0; c < 9; c++) {
      int value = solve_board[r][c];
      if (value == 0) {
        // There's an empty space, so it isn't solved
        return false;
      }

      int bit = numToBit(value);

      rows[r] |= bit;
      cols[c] |= bit;
      boxes[boxIndex(r, c)] |= bit;
    }
  }

  for (int i = 0; i < 9; i++) {
    int all_found = ALL_POSSIBILITIES;

    if (rows[i] != all_found || cols[i] != all_found || boxes[i] != all_found) {
      return false;
    }
  }

  return true;
}

#endif
