#ifndef DRAWING_H
#define DRAWING_H

#include "drawing/drawing_primitives.h"

// DrawNumber draws the given number at the row/col position in the board
// Any number provided other than 1-9 is represented as `x`
void DrawNumber(int number, int row, int col) {
  int x = col * 7;
  int y = (8 - row) * 7;

  switch (number) {
  case 1:
    draw1(x, y);
    break;
  case 2:
    draw2(x, y);
    break;
  case 3:
    draw3(x, y);
    break;
  case 4:
    draw4(x, y);
    break;
  case 5:
    draw5(x, y);
    break;
  case 6:
    draw6(x, y);
    break;
  case 7:
    draw7(x, y);
    break;
  case 8:
    draw8(x, y);
    break;
  case 9:
    draw9(x, y);
    break;
  default:
    drawX(x, y);
    break;
  }
}

// DrawBoard draws the given sudoku board along the left side of the screen
// -1 means no number is present, any number other than 1-9 means unknown number
void DrawBoard(int &board[][]) {
  ClearScreen();

  // Draw the grid
  for (int i = 0; i < 10; i++) {
    int offset = 7*i;
    LineOut(0, offset, 63, offset);
    LineOut(offset, 0, offset, 63);

    if (i == 3 || i == 6) {
      LineOut(0, offset-1, 63, offset-1);
      LineOut(offset-1, 0, offset-1, 63);
    }
  }

  // Draw the numbers
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      int number = board[i][j];
      if (number == -1) {
        continue;
      }
      DrawNumber(number, i, j);
    }
  }
}

#endif
