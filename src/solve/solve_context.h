#ifndef SOLVE_CONTEXT_H
#define SOLVE_CONTEXT_H

#include "src/solve/utils.h"
#include "src/bluetooth/bt_print.h"

struct solve_context {
    int solved_count;
    int board[][];
    int position_possibilities[][];
    int guess_depths[][];
    bool guesses[][];
};

int nextPossibility(int x, int last_guess) {
  for (int i = last_guess + 1; i < 10; i++) {
    if (x & (1 << i)) {
      return i;
    }
  }
  return -1;
}

void init_board(solve_context &ctx) {
    int initArray[];
    ArrayInit(initArray, 0, 9);
    ArrayInit(ctx.board, initArray, 9);
}

void init_possibilities(solve_context &ctx) {
    int initArray[];
    ArrayInit(initArray, 0x3FE, 9);
    ArrayInit(ctx.position_possibilities, initArray, 9);
}

void init_depths(solve_context &ctx) {
    int initArray[];
    ArrayInit(initArray, 0, 9);
    ArrayInit(ctx.guess_depths, initArray, 9);
}

void init_guesses(solve_context &ctx) {
    bool initArray[];
    ArrayInit(initArray, false, 9);
    ArrayInit(ctx.guesses, initArray, 9);
}

void set_value(solve_context &ctx, int row, int col, int value, int guess_depth, bool is_guess) {
    bt_print(FormatNum("Set Value: %d", value));
    bt_print(FormatNum(" (%d", row));
    bt_print(FormatNum(", %d)\n", col));

    ctx.board[row][col] = value;
    ctx.guesses[row][col] = is_guess;
    ctx.guess_depths[row][col] = guess_depth;
    ctx.solved_count++;

    int bI = boxIndex(row, col);

    for (int i = 0; i < 9; i++) {
        ctx.position_possibilities[row][i] &= ~numToBit(value);
        ctx.position_possibilities[i][col] &= ~numToBit(value);
        ctx.position_possibilities[getBoxRow(bI, i)][getBoxCol(bI, i)] &= ~numToBit(value);
    }
}

void reset_guess(solve_context &ctx, int depth, int &guess_row, int &guess_col, int &guessed_value) {
  for (int r = 0; r < 9; r++) {
    for (int c = 0; c < 9; c++) {
      if (ctx.guess_depths[r][c] == depth) {
        int value = ctx.board[r][c];

        if (ctx.guesses[r][c]) {
          guess_row = r;
          guess_col = c;
          guessed_value = value;
        }

        ctx.solved_count--;
        ctx.board[r][c] = 0;
        ctx.guesses[r][c] = false;
        ctx.guess_depths[r][c] = 0;

        int bI = boxIndex(r, c);
        for (int i = 0; i < 9; i++) {
          ctx.position_possibilities[r][i] |= numToBit(value);
          ctx.position_possibilities[i][c] |= numToBit(value);
          ctx.position_possibilities[getBoxRow(bI, i)][getBoxCol(bI, i)] |= numToBit(value);
        }
      }
    }
  }
}

void init_solve_context(solve_context &ctx, int &board[][]) {
    init_board(ctx);
    init_possibilities(ctx);
    init_depths(ctx);
    init_guesses(ctx);
    ctx.solved_count = 0;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] != 0) {
                set_value(ctx, i, j, board[i][j], 0, false);
            }
        }
    }
}

void copy_solve_context(solve_context &src, solve_context &dest) {
  init_board(dest);
  init_possibilities(dest);
  dest.solved_count = src.solved_count;

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      dest.board[i][j] = src.board[i][j];
      dest.position_possibilities[i][j] = src.position_possibilities[i][j];
    }
  }
}

// Returns whether or not a board is a valid, solved sudoku
bool is_valid_solution(solve_context &ctx) {
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
      int value = ctx.board[r][c];
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

#endif
