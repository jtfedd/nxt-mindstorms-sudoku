#ifndef DRAWING_PRIMITIVES_H
#define DRAWING_PRIMITIVES_H

// This file provides custom drawing functions to show characters on the screen

void drawX(int x, int y) {
  LineOut(x + 2, y + 5, x + 5, y + 2);
  LineOut(x + 2, y + 2, x + 5, y + 5);
}

void draw1(int x, int y) {
  LineOut(x + 4, y + 5, x + 4, y + 1);
  PointOut(x + 3, y + 4);
}

void draw2(int x, int y) {
  PointOut(x + 2, y + 4);
  LineOut(x + 3, y + 5, x + 4, y + 5);
  LineOut(x + 5, y + 4, x + 2, y + 1);
  LineOut(x + 2, y + 1, x + 5, y + 1);
}

void draw3(int x, int y) {
  LineOut(x + 2, y + 5, x + 5, y + 5);
  LineOut(x + 3, y + 3, x + 5, y + 3);
  LineOut(x + 2, y + 1, x + 5, y + 1);
  LineOut(x + 5, y + 5, x + 5, y + 1);
}

void draw4(int x, int y) {
  LineOut(x + 2, y + 5, x + 2, y + 3);
  LineOut(x + 2, y + 3, x + 5, y + 3);
  LineOut(x + 5, y + 5, x + 5, y + 1);
}

void draw5(int x, int y) {
  LineOut(x + 2, y + 5, x + 5, y + 5);
  LineOut(x + 2, y + 5, x + 2, y + 3);
  LineOut(x + 2, y + 3, x + 4, y + 3);
  PointOut(x + 5, y + 2);
  LineOut(x + 2, y + 1, x + 4, y + 1);
}

void draw6(int x, int y) {
  LineOut(x + 3, y + 5, x + 4, y + 5);
  LineOut(x + 2, y + 4, x + 2, y + 2);
  LineOut(x + 3, y + 3, x + 4, y + 3);
  LineOut(x + 3, y + 1, x + 4, y + 1);
  PointOut(x + 5, y + 2);
}

void draw7(int x, int y) {
  LineOut(x + 2, y + 5, x + 5, y + 5);
  LineOut(x + 5, y + 5, x + 4, y + 1);
}

void draw8(int x, int y) {
  LineOut(x + 3, y + 5, x + 4, y + 5);
  LineOut(x + 3, y + 3, x + 4, y + 3);
  LineOut(x + 3, y + 1, x + 4, y + 1);
  PointOut(x + 2, y + 4);
  PointOut(x + 2, y + 2);
  PointOut(x + 5, y + 4);
  PointOut(x + 5, y + 2);
}

void draw9(int x, int y) {
  LineOut(x + 3, y + 5, x + 4, y + 5);
  LineOut(x + 5, y + 4, x + 5, y + 2);
  LineOut(x + 3, y + 3, x + 4, y + 3);
  LineOut(x + 3, y + 1, x + 4, y + 1);
  PointOut(x + 2, y + 4);
}

#endif
