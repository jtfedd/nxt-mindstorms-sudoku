#ifndef SOLVE_H
#define SOLVE_H

#include "src/solve/utils.h"
#include "src/solve/solve_context.h"

bool SolveSudoku(int &board[][], int &iterations, int &guesses) {
  iterations = 0;
  guesses = 0;

  bool foundNewSolution = true;

  solve_context ctx;
  init_solve_context(ctx, board);

  while (foundNewSolution && ctx.solved_count < 81) {
    iterations++;
    foundNewSolution = false;
    for (int r = 0; r < 9; r++) {
      for (int c = 0; c < 9; c++) {
        if (ctx.board[r][c] != 0) {
          continue;
        }

        if (singleBitSet(ctx.position_possibilities[r][c])) {
            int value = bitToNum(ctx.position_possibilities[r][c]);
            set_value(ctx, r, c, value);
            foundNewSolution = true;
        }
      }
    }
  }

  return is_valid_solution(ctx);
}

#endif
