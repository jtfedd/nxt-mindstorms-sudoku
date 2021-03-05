#ifndef TEST_SOLVE_UTILS
#define TEST_SOLVE_UTILS

#include "test/testing.h"

#include "src/solve/utils.h"

void Test_SingleBitSet(test_case &tc) {
  assertTrue(tc, singleBitSet(0x0010));
  assertTrue(tc, singleBitSet(0x0400));
  assertFalse(tc, singleBitSet(0x0300));
  assertFalse(tc, singleBitSet(0x0101));
}

void Test_NumToBit(test_case &tc) {
  assertEqual(tc, 0x00200, numToBit(9));
  assertEqual(tc, 0x08000, numToBit(15));
  assertEqual(tc, 0x1, numToBit(0));
  assertEqual(tc, 0x4, numToBit(2));
}

void Test_BitToNum(test_case &tc) {
  assertEqual(tc, 4, bitToNum(0x10));
  assertEqual(tc, 7, bitToNum(0x80));
  assertEqual(tc, 9, bitToNum(0x200));
  assertEqual(tc, 0, bitToNum(0x1));
}

void Test_BoxIndex(test_case &tc) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      assertEqual(tc, 0, boxIndex(i, j));
    }
    for (int j = 3; j < 6; j++) {
      assertEqual(tc, 1, boxIndex(i, j));
    }
    for (int j = 6; j < 9; j++) {
      assertEqual(tc, 2, boxIndex(i, j));
    }
  }
  
  for (int i = 3; i < 6; i++) {
    for (int j = 0; j < 3; j++) {
      assertEqual(tc, 3, boxIndex(i, j));
    }
    for (int j = 3; j < 6; j++) {
      assertEqual(tc, 4, boxIndex(i, j));
    }
    for (int j = 6; j < 9; j++) {
      assertEqual(tc, 5, boxIndex(i, j));
    }
  }
  
  for (int i = 6; i < 9; i++) {
    for (int j = 0; j < 3; j++) {
      assertEqual(tc, 6, boxIndex(i, j));
    }
    for (int j = 3; j < 6; j++) {
      assertEqual(tc, 7, boxIndex(i, j));
    }
    for (int j = 6; j < 9; j++) {
      assertEqual(tc, 8, boxIndex(i, j));
    }
  }
}

void Test_BoxIntIndex(test_case &tc) {
  for (int i = 0; i < 9; i+=3) {
    for (int j = 0; j < 9; j+=3) {
      assertEqual(tc, 0, boxInternalIndex(i, j));
    }
    for (int j = 1; j < 9; j+=3) {
      assertEqual(tc, 1, boxInternalIndex(i, j));
    }
    for (int j = 2; j < 9; j+=3) {
      assertEqual(tc, 2, boxInternalIndex(i, j));
    }
  }
  
  for (int i = 1; i < 9; i+=3) {
    for (int j = 0; j < 9; j+=3) {
      assertEqual(tc, 3, boxInternalIndex(i, j));
    }
    for (int j = 1; j < 9; j+=3) {
      assertEqual(tc, 4, boxInternalIndex(i, j));
    }
    for (int j = 2; j < 9; j+=3) {
      assertEqual(tc, 5, boxInternalIndex(i, j));
    }
  }
  
  for (int i = 2; i < 9; i+=3) {
    for (int j = 0; j < 9; j+=3) {
      assertEqual(tc, 6, boxInternalIndex(i, j));
    }
    for (int j = 1; j < 9; j+=3) {
      assertEqual(tc, 7, boxInternalIndex(i, j));
    }
    for (int j = 2; j < 9; j+=3) {
      assertEqual(tc, 8, boxInternalIndex(i, j));
    }
  }
}

void Test_GetBoxRow(test_case &tc) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      assertEqual(tc, 0, getBoxRow(i, j));
    }
    for (int j = 3; j < 6; j++) {
      assertEqual(tc, 1, getBoxRow(i, j));
    }
    for (int j = 6; j < 9; j++) {
      assertEqual(tc, 2, getBoxRow(i, j));
    }
  }
  
  for (int i = 3; i < 6; i++) {
    for (int j = 0; j < 3; j++) {
      assertEqual(tc, 3, getBoxRow(i, j));
    }
    for (int j = 3; j < 6; j++) {
      assertEqual(tc, 4, getBoxRow(i, j));
    }
    for (int j = 6; j < 9; j++) {
      assertEqual(tc, 5, getBoxRow(i, j));
    }
  }
  
  for (int i = 6; i < 9; i++) {
    for (int j = 0; j < 3; j++) {
      assertEqual(tc, 6, getBoxRow(i, j));
    }
    for (int j = 3; j < 6; j++) {
      assertEqual(tc, 7, getBoxRow(i, j));
    }
    for (int j = 6; j < 9; j++) {
      assertEqual(tc, 8, getBoxRow(i, j));
    }
  }
}

void Test_GetBoxCol(test_case &tc) {
  for (int i = 0; i < 9; i+=3) {
    for (int j = 0; j < 9; j+=3) {
      assertEqual(tc, 0, getBoxCol(i, j));
    }
    for (int j = 1; j < 9; j+=3) {
      assertEqual(tc, 1, getBoxCol(i, j));
    }
    for (int j = 2; j < 9; j+=3) {
      assertEqual(tc, 2, getBoxCol(i, j));
    }
  }
  
  for (int i = 1; i < 9; i+=3) {
    for (int j = 0; j < 9; j+=3) {
      assertEqual(tc, 3, getBoxCol(i, j));
    }
    for (int j = 1; j < 9; j+=3) {
      assertEqual(tc, 4, getBoxCol(i, j));
    }
    for (int j = 2; j < 9; j+=3) {
      assertEqual(tc, 5, getBoxCol(i, j));
    }
  }

  for (int i = 2; i < 9; i+=3) {
    for (int j = 0; j < 9; j+=3) {
      assertEqual(tc, 6, getBoxCol(i, j));
    }
    for (int j = 1; j < 9; j+=3) {
      assertEqual(tc, 7, getBoxCol(i, j));
    }
    for (int j = 2; j < 9; j+=3) {
      assertEqual(tc, 8, getBoxCol(i, j));
    }
  }
}

#endif
