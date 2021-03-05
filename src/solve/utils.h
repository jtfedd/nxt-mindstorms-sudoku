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

#endif
