#ifndef TEST_TESTS
#define TEST_TESTS

#include "test/testing.h"

void Test_Test1(test_case &tc) {
  assertTrue(tc, true);
  assertTrue(tc, true);
}

void Test_Test2(test_case &tc) {
  assertFalse(tc, false);
  assertTrue(tc, false);
}

void Test_Test3(test_case &tc) {
  assertTrue(tc, true);
  assertFalse(tc, true);
}

void Test_Test4(test_case &tc) {
  assertFalse(tc, false);
  assertFalse(tc, false);
}

void Test_Test5(test_case &tc) {
  assertEqual(tc, -1, -1);
  assertEqual(tc, 15, 15);
  assertEqual(tc, 1551, 1551);
  assertEqual(tc, 1351, 1351);
}

void Test_Test6(test_case &tc) {
  assertEqual(tc, 1, 1);
  assertTrue(tc, true);
  assertFalse(tc, false);
  assertEqual(tc, 13531, 135);
  assertTrue(tc, true);
  assertFalse(tc, true);
  assertEqual(tc, 1, -1);
}

#endif
