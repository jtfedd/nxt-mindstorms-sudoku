#ifndef GUESS_STACK_H
#define GUESS_STACK_H

// This can be tuned to save memory but limit the backtracking depth
// 81 is the maxium possible guesses we could have, but in reality the max
// is much less, because we will not have to guess all the way to the end
// of the sudoku because once we get near the end of the puzzle the answers
// have to be able to be deduced without guessing
#define MAX_GUESSES 81

struct saved_state {
  int board[9][9];
};

struct guess_stack {
  size int;
  saved_state stack[MAX_GUESSES];
};

void push(guess_stack &s, saved_state )

#endif