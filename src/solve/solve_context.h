#ifndef SOLVE_CONTEXT_H
#define SOLVE_CONTEXT_H

#include "src/solve/utils.h"

struct solve_context {
    int solved_count;
    int board[][];
    int position_possibilities[][];
};

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

void set_value(solve_context &ctx, int row, int col, int value) {
    ctx.board[row][col] = value;
    ctx.solved_count++;

    int bI = boxIndex(row, col);

    for (int i = 0; i < 9; i++) {
        ctx.position_possibilities[row][i] &= ~numToBit(value);
        ctx.position_possibilities[i][col] &= ~numToBit(value);
        ctx.position_possibilities[getBoxRow(bI, i)][getBoxCol(bI, i)] &= ~numToBit(value);
    }
}

void init_solve_context(solve_context &ctx, int &board[][]) {
    init_board(ctx);
    init_possibilities(ctx);
    ctx.solved_count = 0;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] != 0) {
                set_value(ctx, i, j, board[i][j]);
            }
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
