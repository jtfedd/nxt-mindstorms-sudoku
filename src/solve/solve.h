#ifndef SOLVE_H
#define SOLVE_H

#include "src/solve/utils.h"
#include "src/solve/solve_context.h"

bool SolveSudoku(int &src_board[][], int &iterations, int &guesses) {
  iterations = 0;
  guesses = 0;

  bool foundNewSolution = true;
  bool invalid = false;

  init_solve_context(src_board);

  while (foundNewSolution && solved_count < 81) {
    iterations++;
    foundNewSolution = false;
    invalid = false;

    for (int r = 0; r < 9 && !invalid; r++) {
      for (int c = 0; c < 9 && !invalid; c++) {
        // Skip if there's already a value here
        if (solve_board[r][c] != 0) {
          continue;
        }

        int possibility = getSinglePossibility(r, c);

        if (possibility > 0) {
          // If there's only one number that can go here, then place it
          set_value(r, c, possibility, false);
          foundNewSolution = true;
        } else if (possibility == -1) {
          // If there are no possibilities at this position, then this board is invalid
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
          if (solve_board[r][c] != 0) {
            continue;
          }

          int numPossibilities = countPossibilities(r, c);
          if (numPossibilities < minPossibilities) {
            minPossibilities = numPossibilities;
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

        int numToGuess = nextPossibility(minR, minC, 0);
        guess_depth++;
        set_value(minR, minC, numToGuess, true);

        guesses++;
      }
    }

    while (invalid && guess_depth > 0) {
      // Restore to the last guess and guess the next number.
      // If there's no guess to restore to, then we are out of luck and the board is unsolveable.
      int guess_row = 0;
      int guess_col = 0;
      int guess = 0;

      reset_guess(guess_row, guess_col, guess);
      guess_depth--;

      int next_guess = nextPossibility(guess_row, guess_col, guess);
      
      if (next_guess > 0) {
        guess_depth++;
        set_value(guess_row, guess_col, next_guess, true);

        guesses++;
        foundNewSolution = true;
        invalid = false;
      }
    }
  }

  copy_board(src_board, solve_board);

  return is_valid_solution();
}

#endif
