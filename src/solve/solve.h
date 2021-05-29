#ifndef SOLVE_H
#define SOLVE_H

#include "src/solve/utils.h"
#include "src/solve/solve_context.h"

bool SolveSudoku(int &board[][], int &iterations, int &guesses) {
  iterations = 0;
  guesses = 0;

  int guess_depth = 0;

  bool foundNewSolution = true;
  bool invalid = false;

  solve_context ctx;
  init_solve_context(ctx, board);

  while (foundNewSolution && ctx.solved_count < 81) {
    iterations++;
    foundNewSolution = false;
    invalid = false;
    for (int r = 0; r < 9 && !invalid; r++) {
      for (int c = 0; c < 9 && !invalid; c++) {
        if (ctx.board[r][c] != 0) {
          continue;
        }

        if (singleBitSet(ctx.position_possibilities[r][c])) {
            int value = bitToNum(ctx.position_possibilities[r][c]);
            set_value(ctx, r, c, value, guess_depth, false);
            foundNewSolution = true;
        } else if (ctx.position_possibilities[r][c] == 0) {
          // If no number can go here, well...
          invalid = true;
        }
      }
    }

    if (!foundNewSolution && !invalid) {
      // We weren't able to deduce any solutions; we have to guess
      // Look for the square with the lowest number of possibilities
      int minR = 0;
      int minC = 0;
      int minPossibilities = 10;

      for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
          if (ctx.board[r][c] != 0) {
            continue;
          }

          int numBitsSet = countBits(ctx.position_possibilities[r][c]);
          if (numBitsSet < minPossibilities) {
            minPossibilities = numBitsSet;
            minR = r;
            minC = c;
          }
        }
      }

      if (minPossibilities == 0 || minPossibilities == 10) {
        // We couldn't find any valid places to guess. We have to backtrack.
        invalid = true;
      } else {
        foundNewSolution = true;
        return false;

        int numToGuess = nextPossibility(ctx.position_possibilities[minR][minC], 0);
        guess_depth++;
        set_value(ctx, minR, minC, numToGuess, guess_depth, true);

        guesses++;
      }
    }

    if (invalid && guess_depth > 0) {
      while (invalid && guess_depth > 0) {
        // Restore to the last guess and guess the next number.
        // If there's no guess to restore to, then we are out of luck and the board is unsolveable.
        int guess_row = 0;
        int guess_col = 0;
        int guess = 0;

        reset_guess(ctx, guess_depth, guess_row, guess_col, guess);
        guess_depth--;

        int next_guess = nextPossibility(ctx.position_possibilities[guess_row][guess_col], guess);
        
        if (next_guess > 0) {
          guess_depth++;
          set_value(ctx, guess_row, guess_col, next_guess, guess_depth, true);

          guesses++;
          foundNewSolution = true;
          invalid = false;
        }
      }
    }
  }

  copy_board(board, ctx.board);

  return is_valid_solution(ctx);
}

#endif
