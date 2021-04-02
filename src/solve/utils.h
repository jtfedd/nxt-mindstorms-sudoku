#ifndef SOLVE_UTILS_H
#define SOLVE_UTILS_H

void copy_board(int &dest[][], int &src[][]) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      dest[i][j] = src[i][j];
    }
  }
}

bool singleBitSet(int x) {
  return (x && !(x & x-1));
}

int countBits(int x) {
  int count = 0;
  for (int i = 1; i <= 9; i++) {
    if ((1<<i) & x) {
      count++;
    }
  }
  return count;
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
