#ifndef SOLVE_UTILS_H
#define SOLVE_UTILS_H

#define BOX 0
#define ROW 1
#define COL 2
#define POS 3

bool singleBitSet(int x) {
  return (x && !(x & x-1));
}

int numToBit(int x) {
  return 1 << x;
}

int bitToNum(int x) {
  for (int i = 0; i <= 9; i++) {
    if (1 << i == x) {
      return i;
    }
  }
  return -1;
}

int boxIndex(int row, int col) {
  return ((row / 3) * 3) + (col / 3);
}

int boxInternalIndex(int row, int col) {
  return ((row % 3) * 3) + (col % 3);
}

int getBoxRow(int boxIndex, int internalIndex) {
  return ((boxIndex / 3) * 3) + (internalIndex / 3);
}

int getBoxCol(int boxIndex, int internalIndex) {
  return ((boxIndex % 3) * 3) + (internalIndex % 3);
}

// Returns whether or not a board is a valid, solved sudoku
bool validate(int &board[][]) {
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
      int value = board[r][c];
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
    // Since the smallest number in the grid is 1, the expected bit
    // pattern for all numbers found would be this:
    // 0011 1111 1110
    int all_found = 0x3FE;

    if (rows[i] != all_found || cols[i] != all_found || boxes[i] != all_found) {
      return false;
    }
  }

  return true;
}

bool isPossibility(int &board[][], int num, int row, int col) {
  // Check if it exists in the row, column, and box
  int box_index = boxIndex(row, col);
  for (int i = 0; i < 9; i++) {
    if (board[row][i] == num) {
      return false;
    }
    if (board[i][col] == num) {
      return false;
    }
    if (board[getBoxRow(box_index, i)][getBoxCol(box_index, i)] == num) {
      return false;
    }
  }
  return true;
}

bool SolveSudoku(int &board[][], int &iterations, int &guesses) {
  iterations = 0;
  guesses = 0;

  bool foundNewSolution = true;

  while (foundNewSolution) {
    iterations++;
    foundNewSolution = false;
    for (int r = 0; r < 9; r++) {
      for (int c = 0; c < 9; c++) {
        if (board[r][c] != 0) {
          continue;
        }

        int possibility = 0;
        for (int i = 1; i <= 9; i++) {
          if (isPossibility(board, i, r, c)) {
            if (possibility > 0) {
              possibility = -1;
              break;
            } else {
              possibility = i;
            }
          }
        }
        if (possibility > 0) {
          board[r][c] = possibility;
          foundNewSolution = true;
        }
      }
    }
  }

  return validate(board);
}

#endif
